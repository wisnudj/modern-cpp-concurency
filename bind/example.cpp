#include <memory>
#include <functional>
#include <iostream>

using namespace std::placeholders;

int add(int first, int second)
{
    return first + second;
}

int main()
{
    auto new_add_func = std::bind(&add, 12, _1);
    std::cout << new_add_func(20) << std::endl;

    std::function<int(int, int)> func_bind = std::bind(&add, _1, _2);
    std::cout << func_bind(20, 10) << std::endl;   
}