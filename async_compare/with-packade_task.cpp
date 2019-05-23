#include <iostream>
#include <thread>
#include <future>
#include <string>

std::string get_data_from_db(std::string token)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::string data = "Data fetched from DB by Filter :: " + token;
    return data;
}

int main()
{
    std::packaged_task<std::string(std::string)> task(get_data_from_db);

    std::future<std::string> result = task.get_future();

    std::thread thr_1(std::move(task), "data");

    thr_1.join();

    std::string data = result.get();

    std::cout << data << std::endl;
}