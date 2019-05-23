#include <iostream>
#include <string>
#include <chrono>
#include <thread>
 
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

int main()
{
    auto start = std::chrono::system_clock::now();

    std::string db_data = fetch_data_from_db("Data");
    std::string file_data = fetch_data_from_file("Data");

    auto end = std::chrono::system_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::seconds> (end - start).count();
    std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

    std::string data = db_data + " :: " + file_data;

    std::cout << "Data = " << data << std::endl;

}