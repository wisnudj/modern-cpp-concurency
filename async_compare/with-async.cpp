#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future> 

std::string fetch_data_from_db(std::string recv_data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return "DB_" + recv_data;
}

std::string fetch_data_from_file(std::string recv_data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return "File_" + recv_data;
}

struct data_fetcher
{
    std::string operator()(std::string recv_data)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        return "File_" + recv_data;
    }
};


int main()
{
    std::chrono::system_clock::time_point start =  std::chrono::system_clock::now();

    std::future<std::string> result_from_db = std::async(std::launch::async, fetch_data_from_db, "Data");
    std::future<std::string> result_from_api = std::async(std::launch::async, data_fetcher(), "Data");
    std::future<std::string> result_lambda = std::async([](std::string recv_data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        return "File_" + recv_data;
    }, "data");

    std::string file_data = fetch_data_from_file("Data");

    std::string db_data = result_from_db.get();
    std::string fetch_data = result_from_api.get();
    std::string lambda_data = result_lambda.get();

    auto end = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

    std::string data = db_data  + "::" + file_data;

    std::cout << "Data = " << data << std::endl;
}