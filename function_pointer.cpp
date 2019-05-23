#include<iostream>
#include <string>

int add(int left, int right)
{
    return left + right;
}

int multiply(int left, int right)
{
    return left * right;
}

int binary_operation(int left, int right, int(*f)(int, int))
{
    return (*f)(left, right);
}

int main()
{
    int x = 20;
    int y = 50;

    std::cout << binary_operation(x, y, add) << std::endl;
    std::cout << binary_operation(x, y, multiply) << std::endl;
}