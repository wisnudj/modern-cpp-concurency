#include <memory>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <mutex>

template<typename T>
class sequential_queue
{
    struct node
    {
        T data;
        std::unique_ptr<node> next;
        node(T _data) : data(std::move(_data))
        {
        }
    };
    std::unique_ptr<node> head;
    node* tail;
    std::mutex head_mutex;
    std::mutex tail_mutex;

public:
    sequential_queue() : head(new node), tail(head.get()) 
    {}
    
    void push(T value)
    {
        std::unique_ptr<node> new_node(new node(std::move(value)));
        node* const new_tail = new_node.get();

        std::lock_guard<std::mutex> tlg(tail_mutex);
        if(tail)
        {
            std::cout << "Tail ditemukan" << std::endl;
            tail->next = std::move(new_node);
        }
        else
        {
            std::lock_guard<std::mutex> hlg(head_mutex);
            std::cout << "Tail tidak ditemukan" << std::endl;
            head = std::move(new_node);
        }

        tail = new_tail;
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> hlg(head_mutex);
        if(head.get() == tail)
        {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }

    void lihat()
    {
        std::cout << tail << std::endl;
        std::cout << head.get() << std::endl;
    }
};

int main()
{

}