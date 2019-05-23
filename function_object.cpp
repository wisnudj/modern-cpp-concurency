#include <iostream>
#include <memory>

class binary_function
{
public:
    binary_function() {};
    virtual int operator()(int left, int right) = 0;
};

class add : public binary_function
{
public:
    add() {};
    virtual int operator()(int left, int right) { return left + right; };
};

class multiply : public binary_function
{
public:
    multiply() {};
    virtual int operator()(int left, int right) { return left * right; };
};

int binary_op(int left, int right, binary_function *bin_func)
{
    return (*bin_func)(left, right);
}

int main()
{
    int x = 20;
    int y = 50;

    binary_function* bin_ptr = new add();

    std::cout << binary_op(20, 10, bin_ptr) << std::endl;
}