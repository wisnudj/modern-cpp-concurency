#include <iostream>
#include <algorithm>

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int mul = 40;

    // All outer scope elements has been passed by reference
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x) {
        std::cout << x << std::endl;
        mul = 100;
    });

    std::cout << mul << std::endl;

     // All outer scope elements has been passed by value
     std::for_each(arr, arr + sizeof(arr) / sizeof(int), [=](int x) {
         std::cout << x << std::endl;
         x = mul + 900;
     });
}