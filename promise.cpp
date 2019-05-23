#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

void initiazer(std::promise<int> * promObj)
{
    std::cout<<"Inside Thread"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    promObj->set_value(35);
}


int main()
{
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread thr_1(initiazer, &promiseObj);

    std::cout<<futureObj.get()<<std::endl;

    thr_1.join();

    return 0;
}