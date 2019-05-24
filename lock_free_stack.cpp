#include <iostream>
#include <thread>
#include <atomic>

template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node *next;

        node(T const & _data) : data(std::make_shared<T>(_data))
        {}
    };

    std::atomic<node*> head;

public:
    void push(T const& _data)
    {
        node* const new_node = new node(_data);
        new_node->next = head.load();
        // head.compare_exchange_weak(new_node->next, new_node);
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }

    // void pop(T& result)
    // {
    //     node* old_head = head.load();
    //     while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
    //     result = old_head->data;
    // }
    std::shared_ptr<T> pop()
    {
        node *old_head = head.load();
        while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
};