#include <iostream>
#include <string>

int main()
{
    std::string msg = "Hello";

    // pass by value
    auto func = [msg]() mutable {
        msg = "good bye";
        std::cout << "bye bye " << msg << std::endl;
    };

    // pass by reference
    auto func_2 = [&msg]() {
        msg = "anjay";
        std::cout << "bye bye " << msg << std::endl;
    };


    func();
    std::cout << msg << std::endl;


    func_2();
    std::cout << msg << std::endl;
}