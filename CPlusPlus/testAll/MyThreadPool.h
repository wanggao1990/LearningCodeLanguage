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

    /** 线程池的配置
    * core_threads: 核心线程个数，线程池中最少拥有的线程个数，初始化就会创建好的线程，常驻于线程池
    *
    * max_threads: >=core_threads，当任务的个数太多线程池执行不过来时，
    * 内部就会创建更多的线程用于执行更多的任务，内部线程数不会超过max_threads
    *
    * max_task_size: 内部允许存储的最大任务个数，暂时没有使用
    *
    * time_out: Cache线程的超时时间，Cache线程指的是max_threads-core_threads的线程,
    * 当time_out时间内没有执行任务，此线程就会被自动回收
    */
    struct ThreadPoolConfig {
        int core_threads;
        int max_threads;
        int max_task_size;
        PoolSeconds time_out;
    };

    /**
    * 线程的状态：有等待、运行、停止
    */
    enum class ThreadState { kInit = 0, kWaiting = 1, kRunning = 2, kStop = 3 };

    /**
    * 线程的种类标识：标志该线程是核心线程还是Cache线程，Cache是内部为了执行更多任务临时创建出来的
    */
    enum class ThreadFlag { kInit = 0, kCore = 1, kCache = 2 };


private:

    using ThreadPtr = std::shared_ptr<std::thread>;
    using ThreadId = std::atomic<int>;
    using ThreadStateAtomic = std::atomic<ThreadState>;
    using ThreadFlagAtomic = std::atomic<ThreadFlag>;


    /**
     * 线程池中线程存在的基本单位，每个线程都有个自定义的ID，有线程种类标识和状态
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

    // 默认会创建Core线程，也可以选择创建Cache线程,线程内部会有一个死循环，不停的等待任务，
    // 有任务到来时就会执行，同时内部会判断是否是Cache线程，如果是Cache线程，time_out时间内
    // 没有任务执行就会自动退出循环，线程结束。
    // 检查is_shutdown_和is_shutdown_now_标志，根据两个标志位是否为true来判断是否结束线程。
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
    std::atomic<int> thread_id_; // 用于为新创建的线程分配ID

    std::atomic<bool> is_shutdown_now_;   // 立即关闭线程池，缓存的任务不会被执行
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
