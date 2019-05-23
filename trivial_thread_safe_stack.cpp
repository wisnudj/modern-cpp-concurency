#include <iostream>
#include <mutex>
#include <stack>
#include <thread>

template<typename T>
class trivial_thread_safe_stack
{
    std::stack<T> stk;
    std::mutex m;

public:
    void push(T element)
    {
        stk.push(element);
    }

    void pop()
    {
        stk.pop();
    }

    T& top()
    {
        return stk.top();
    }
};

int main()
{
    trivial_thread_safe_stack<int> st;
    
    std::thread thr_1(&trivial_thread_safe_stack<int>::push, &st, 20);
    std::thread thr_2(&trivial_thread_safe_stack<int>::pop, &st);

    thr_1.join();
    thr_2.join();
}