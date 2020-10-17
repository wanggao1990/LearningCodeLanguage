#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <list>
#include <queue>
#include <future>

class MyThreadPool
{
public:
    using PoolSeconds =  std::chrono::seconds;

    /** �̳߳ص�����
    * core_threads: �����̸߳������̳߳�������ӵ�е��̸߳�������ʼ���ͻᴴ���õ��̣߳���פ���̳߳�
    *
    * max_threads: >=core_threads��������ĸ���̫���̳߳�ִ�в�����ʱ��
    * �ڲ��ͻᴴ��������߳�����ִ�и���������ڲ��߳������ᳬ��max_threads
    *
    * max_task_size: �ڲ�����洢����������������ʱû��ʹ��
    *
    * time_out: Cache�̵߳ĳ�ʱʱ�䣬Cache�߳�ָ����max_threads-core_threads���߳�,
    * ��time_outʱ����û��ִ�����񣬴��߳̾ͻᱻ�Զ�����
    */
    struct ThreadPoolConfig {
        int core_threads;
        int max_threads;
        int max_task_size;
        PoolSeconds time_out;
    };

    /**
    * �̵߳�״̬���еȴ������С�ֹͣ
    */
    enum class ThreadState { kInit = 0, kWaiting = 1, kRunning = 2, kStop = 3 };

    /**
    * �̵߳������ʶ����־���߳��Ǻ����̻߳���Cache�̣߳�Cache���ڲ�Ϊ��ִ�и���������ʱ����������
    */
    enum class ThreadFlag { kInit = 0, kCore = 1, kCache = 2 };


private:

    using ThreadPtr = std::shared_ptr<std::thread>;
    using ThreadId = std::atomic<int>;
    using ThreadStateAtomic = std::atomic<ThreadState>;
    using ThreadFlagAtomic = std::atomic<ThreadFlag>;


    /**
     * �̳߳����̴߳��ڵĻ�����λ��ÿ���̶߳��и��Զ����ID�����߳������ʶ��״̬
     */
    struct ThreadWrapper {
        ThreadPtr ptr;
        ThreadId id;
        ThreadFlagAtomic flag;
        ThreadStateAtomic state;

        ThreadWrapper()
        {
            ptr = nullptr;
            id = 0;
            state.store(ThreadState::kInit);
        }
    };
    using ThreadWrapperPtr = std::shared_ptr<ThreadWrapper>;
    using ThreadPoolLock = std::unique_lock<std::mutex>;


public:

    MyThreadPool(ThreadPoolConfig config);
    ~MyThreadPool() { ShutDown();}

    bool Reset(ThreadPoolConfig config);

    bool IsAvailable()  { return is_available_;}


    bool Start();


    void ShutDown()     { return ShutDown(false); }
    void ShutDownNow()  { return ShutDown(true); }

    // Ĭ�ϻᴴ��Core�̣߳�Ҳ����ѡ�񴴽�Cache�߳�,�߳��ڲ�����һ����ѭ������ͣ�ĵȴ�����
    // ��������ʱ�ͻ�ִ�У�ͬʱ�ڲ����ж��Ƿ���Cache�̣߳������Cache�̣߳�time_outʱ����
    // û������ִ�оͻ��Զ��˳�ѭ�����߳̽�����
    // ���is_shutdown_��is_shutdown_now_��־������������־λ�Ƿ�Ϊtrue���ж��Ƿ�����̡߳�
    void AddThread(ThreadFlag thread_flag = ThreadFlag::kCore);


    int GetTotalThreadSize() { return this->worker_threads_.size(); }

    int GetWaitingThreadSize() { return this->waiting_thread_num_.load(); }


    template <typename F, typename... Args>
    auto Run(F &&f, Args &&... args)->std::shared_ptr<std::future<std::result_of_t<F(Args...)>>>;

private:

    bool IsValidConfig(const ThreadPoolConfig& config);

    int GetNextThreadId();



    void ShutDown(bool is_now);


private:
    ThreadPoolConfig config_;

    std::list<ThreadWrapperPtr> worker_threads_;

    std::queue<std::function<void()>> tasks_;
    std::mutex task_mutex_;
    std::condition_variable task_cv_;

    std::atomic<int> total_function_num_;
    std::atomic<int> waiting_thread_num_;
    std::atomic<int> thread_id_; // ����Ϊ�´������̷߳���ID

    std::atomic<bool> is_shutdown_now_;   // �����ر��̳߳أ���������񲻻ᱻִ��
    std::atomic<bool> is_shutdown_;
    std::atomic<bool> is_available_;
};




template<typename F, typename ...Args>
auto MyThreadPool::Run(F && f, Args && ...args) -> std::shared_ptr<std::future<std::result_of_t<F(Args ...)>>>
{
    if(this->is_shutdown_.load() || this->is_shutdown_now_.load() || !IsAvailable()) {
        return nullptr;
    }

    if(GetWaitingThreadSize() == 0 && GetTotalThreadSize() < config_.max_threads) {
        AddThread(ThreadFlag::kCache);
    }

    using return_type = std::result_of_t<F(Args...)>;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    total_function_num_++;

    std::future<return_type> res = task->get_future();
    {
        ThreadPoolLock lock(this->task_mutex_);
        this->tasks_.emplace([task]() { (*task)(); });
    }
    this->task_cv_.notify_one();

    return std::make_shared<std::future<std::result_of_t<F(Args...)>>>(std::move(res));
}
