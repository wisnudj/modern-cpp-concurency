#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <assert.h>
#include <chrono>
#include <functional>

class thread_wrapper
{
    std::thread thread_handler;

public:
    // delete copy of constructor
    thread_wrapper(const thread_wrapper&) = delete;

    //Delete the Assignment opeartor
    thread_wrapper& operator=(const thread_wrapper&) = delete;

    thread_wrapper(std::function<void()> func) : thread_handler(func)
    {
    }

    thread_wrapper(thread_wrapper &&obj) : thread_handler(std::move(obj.thread_handler))
    {
    }

    thread_wrapper &operator=(thread_wrapper &&obj)
    {
        if(thread_handler.joinable())
            thread_handler.join();

        thread_handler = std::move(obj.thread_handler);
        return *this;
    }

    ~thread_wrapper()
    {
        if(thread_handler.joinable())
            thread_handler.join();
    }
};