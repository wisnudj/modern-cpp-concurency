#include <iostream>
#include <thread>
#include <mutex>
#include <list>

class list_erapper 
{
    std::list<int> my_list;
    std::mutex m;

public:
    void add_to_list(int const &x)
    {
        std::lock_guard<std::mutex> lg(m);
        my_list.push_back(x);
    }

    void size()
    {
        std::lock_guard<std::mutex> lg(m);
        int size = my_list.size();
        std::cout << "Size of the list: " << size << std::endl;
    }

    std::list<int>* get_data()
    {
        return &my_list;
    }
};