#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Run loop to test if a promise can be used to set a future value repeatedly. 
void run(std::promise<int>& p)
{
	for(int i=0; i<5; ++i) {
//		std::cout << "	Thread sleeping" << std::endl;
//	        std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "	Thread setting value: " << i << std::endl;
		p.set_value(i);	        
	    }
}

int main()
{
// Standard Example from cppreference,com
    // future from a packaged_task
    std::packaged_task<int()> task([](){ return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread(std::move(task)).detach(); // launch on a thread
 
    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
 
    // future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [](std::promise<int>& p){ p.set_value(9); }, 
                 std::ref(p) ).detach();
 
    std::cout << "Waiting...";
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';

// can a single promise be used in a loop and set_value called repeatedly?

	std::promise<int> myPromise;
	std::thread worker(run, std::ref(myPromise));
	std::future<int> myFuture = myPromise.get_future();
	int i = 0;
	while(i <=5) {
		std::cout << "Waiting on future..."<<std::endl;
		myFuture.wait();
		std::cout << "Future: "<< myFuture.get() << std::endl;
	}
	worker.join();
}
