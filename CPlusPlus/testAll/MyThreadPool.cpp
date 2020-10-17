#include "MyThreadPool.h"

#include <iostream>


using std::cout;
using std::endl;

MyThreadPool::MyThreadPool(ThreadPoolConfig config):
    config_(config)
{
    this->total_function_num_.store(0);
    this->waiting_thread_num_.store(0);

    this->thread_id_.store(0);
    this->is_shutdown_.store(false);
    this->is_shutdown_now_.store(false);

    if(IsValidConfig(config_)) {
        is_available_.store(true);
    }
    else {
        is_available_.store(false);
    }

}

bool MyThreadPool::Reset(ThreadPoolConfig config)
{
    if(!IsValidConfig(config)) {
        return false;
    }
    if(config_.core_threads != config.core_threads) {
        return false;
    }
    config_ = config;
    return true;
}

bool MyThreadPool::Start()
{
    if(!IsAvailable()) {
        return false;
    }

    int core_thread_number = config_.core_threads;

    cout << "Init thread num "  << core_thread_number << endl;

    while(core_thread_number-- > 0) {
        AddThread();
    }

    cout << "Init thread end" << endl;

    return true;
}


inline bool MyThreadPool::IsValidConfig(const ThreadPoolConfig& config)
{
    if(config.core_threads < 1 || 
       config.max_threads < config.core_threads || 
       config.time_out.count() < 1) 
    {
        return false;
    }
    return true;
}

int MyThreadPool::GetNextThreadId()
{
    return thread_id_++;
}



// Ĭ�ϻᴴ��Core�̣߳�Ҳ����ѡ�񴴽�Cache�߳�,�߳��ڲ�����һ����ѭ������ͣ�ĵȴ�����
// ��������ʱ�ͻ�ִ�У�ͬʱ�ڲ����ж��Ƿ���Cache�̣߳������Cache�̣߳�time_outʱ����
// û������ִ�оͻ��Զ��˳�ѭ�����߳̽�����
// ���is_shutdown_��is_shutdown_now_��־������������־λ�Ƿ�Ϊtrue���ж��Ƿ�����̡߳�
void MyThreadPool::AddThread(ThreadFlag thread_flag)
{
    int id = GetNextThreadId();
    cout << "AddThread " << id << ", flag " << static_cast<int>(thread_flag) << endl;

    ThreadWrapperPtr thread_ptr = std::make_shared<ThreadWrapper>();
    thread_ptr->id.store(id);
    thread_ptr->flag.store(thread_flag);
    //thread_ptr->state.store(ThreadState::kInit);   // Ĭ�ϳ�ʼ״̬

    auto func = [this, thread_ptr] {
        for(;;) {
            std::function<void()> task;
            {
                ThreadPoolLock lock(this->task_mutex_);
                if(thread_ptr->state.load() == ThreadState::kStop) {
                    break;
                }
                cout << "thread id " << thread_ptr->id.load() << " running start" << endl;
                thread_ptr->state.store(ThreadState::kWaiting);

                ++this->waiting_thread_num_;
                
                bool is_timeout = false;

                if(thread_ptr->flag.load() == ThreadFlag::kCore) {
                    this->task_cv_.wait(lock, [this, thread_ptr] {
                        return (this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty() || 
                                thread_ptr->state.load() == ThreadState::kStop );
                    });
                }
                else {  // ThreadFlag::kCache
                    this->task_cv_.wait_for(lock, this->config_.time_out, [this, thread_ptr] {
                        return (this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty() ||
                                thread_ptr->state.load() == ThreadState::kStop);
                    });
                    is_timeout = !(this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty() ||
                                   thread_ptr->state.load() == ThreadState::kStop);
                }

                --this->waiting_thread_num_;
                cout << "thread id " << thread_ptr->id.load() << " running wait end" << endl;

                if(is_timeout) {
                    thread_ptr->state.store(ThreadState::kStop);
                }

                if(thread_ptr->state.load() == ThreadState::kStop) {
                    cout << "thread id " << thread_ptr->id.load() << " state stop" << endl;
                    break;
                }
                if(this->is_shutdown_ && this->tasks_.empty()) {
                    cout << "thread id " << thread_ptr->id.load() << " shutdown" << endl;
                    break;
                }
                if(this->is_shutdown_now_) {
                    cout << "thread id " << thread_ptr->id.load() << " shutdown now" << endl;
                    break;
                }

                thread_ptr->state.store(ThreadState::kRunning);
                task = std::move(this->tasks_.front());   // front Ϊ��
                this->tasks_.pop();
            }
            task();
        }
        cout << "thread id " << thread_ptr->id.load() << " running end" << endl;
    };

    thread_ptr->ptr = std::make_shared<std::thread>(std::move(func));

    if(thread_ptr->ptr->joinable()) {
        thread_ptr->ptr->detach();
    }
    this->worker_threads_.emplace_back(std::move(thread_ptr));
}


void MyThreadPool::ShutDown(bool is_now)
{
    if(IsAvailable()) {
        if(is_now) {
            cout << "Shutdown now" << endl;
            this->is_shutdown_now_.store(true);
        }
        else {
            cout << "Shutdown" << endl;
            this->is_shutdown_.store(true);
        }

        this->task_cv_.notify_all();
        is_available_.store(false);


    }
}
