#include <memory>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

template<typename T>
class sequential_queue
{
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
        node()
        {
        }

        node(T _data) : data(std::move(_data))
        {
        }
    }

    std::unique_ptr<node> head;
    node *tail;
    std::mutex tail_mutex;
    std::mutex head_mutex;
    std::condition_variable cv;

    node* get_tail()
    {
        std::lock_guard<std::mutex> lg(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> wait_pop_head()
    {

    }

public:
    sequential_queue() : head(new node), tail(head.get()) {}

    void push(T value)
    {
        // change current dummy nodes data value
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(value)));
        std::unique_ptr<node> p(new node);
        node *const new_tail = p.get();

        {
            std::lock_guard<std::mutex> lgt(tail_mutex);
            tail->data = new_data;
            tail->next = std::move(p);
            tail = new_tail;
        }

        cv.notify_one();
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lg(head_mutex);
        if(head.get() == get_tail())
        {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(head->data);
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }
};