#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock_guard
#include <stdexcept>      // std::logic_error

std::mutex mtx;

void print_even(int x) {
	if (x % 2 == 0) std::cout << x << " is even\n";
	else throw (std::logic_error("not even"));
}

void print_thread_id(int id) {
	try {
		// using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
		std::lock_guard<std::mutex> lck(mtx);
		print_even(id);  // 避免打印被中断
	}
	catch (std::logic_error&) {
		std::cout << "[exception caught]\n";
	}
}

void print_block(int n, char c) {
	// critical section (exclusive access to std::cout signaled by lifetime of lck):
	std::unique_lock<std::mutex> lck(mtx);  //这里效果和locklock_guard相同
	for (int i = 0; i < n; ++i) { std::cout << c; }
	std::cout << '\n';
}

std::mutex uniMtx;


#include <chrono>
struct FaceData
{
	int	id;
	int	xpos;
	double arr[1024];
	int num;

	//FaceData& operator=(FaceData&& rhs) {};
};

int main()
{
 	{
 		FaceData a = { 1,2,{3.f},4 };
 		FaceData b ;
 
 		using namespace std::chrono;
 		time_point<system_clock> start = system_clock::now();
 
 		//a = b;
 		//b = std::move(a);
 
 		std::swap(a, b);  // 小数据会慢。。。。
 
 		//FaceData t(std::move(a));
 		//a = std::move(b);
 		//b = std::move(t);
 
 		time_point<system_clock> end = system_clock::now();
 
 		std::cout << duration_cast<nanoseconds>(end-start).count() << " ns"<< std::endl;

		std::cout << duration<double>(end - start).count() << " s" << std::endl;
 	}

	{
		std::thread threads[10];
		// spawn 10 threads:
		for (int i = 0; i < 10; ++i)
			threads[i] = std::thread(print_thread_id, i + 1);
		for (auto& th : threads) th.join();
	}

	{
		std::thread th1(print_block, 50, '*');
		std::thread th2(print_block, 50, '$');

		th1.join();
		th2.join();

	}

	{
		std::thread th1([](){
			while (1)
			{
#if 1	//线程1、2平等
				if (-1 == std::try_lock(uniMtx))   //对传入的mutexs全部加锁成功，返回 -1
				{
					std::cout << "Thread 1 Locked ..." << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					uniMtx.unlock();
					std::cout << "Thread 1 unlock" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
				else
				{
					std::cout << "Thread 1 Locked failed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
#else  // 线程1优先
				uniMtx.lock();
				std::cout << "Thread 1 Locked ..." << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				uniMtx.unlock();
				std::cout << "Thread 1 unlock" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif
			}
		});
		std::thread th2([](){
			while (1)
			{
				if (-1 == std::try_lock(uniMtx))
				{
					std::cout << "Thread 2 Locked ..." << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					uniMtx.unlock();
					std::cout << "Thread 2 unlock" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
				else
				{
					std::cout << "Thread 2 Locked failed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}
		});

		th1.join();
		th2.join();
	}

	return 0;
}