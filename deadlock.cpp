#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>

class Bank_Account 
{
    double balance;
    std::string name;
    std::mutex m;

public:
    Bank_Account() {};

    Bank_Account(double _balance, std::string _name) : balance(_balance), name(_name) {};

    void withdraw(double amount) 
    {
        balance -= amount;
    }

    void deposite(double amount)
    {
        balance += amount;
    }

    void transfer(Bank_Account& from, Bank_Account& to, double amount)
    {
        std::lock_guard<std::mutex> lg_1(from.m);
        std::cout << "lock for " << from.name << " account acquire by " << std::this_thread::get_id << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "Waiting to acquire lock for " << to.name << " account by " << std::endl;

        std::lock_guard<std::mutex> lg_2(to.m);
        from.balance -= amount;
        to.balance += amount;

        std::cout << "transfer to - " << to.name << " from - " << from.name << std::endl;
    }

};

int main()
{
    Bank_Account account;

    Bank_Account account_1(1000, "wisnu");
    Bank_Account account_2(2000, "ijah");

    std::thread thr_1(&Bank_Account::transfer, &account, std::ref(account_1), std::ref(account_2), 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread thr_2(&Bank_Account::transfer, &account, std::ref(account_2), std::ref(account_1), 1000);

    thr_1.join();
    thr_2.join();

    int a;
    std::cin >> a;
}