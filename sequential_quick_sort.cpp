#include <iostream>
#include <algorithm>
#include <list>
#include <chrono>
#include <future>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    if(input.size() < 2)
    {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(), [&](T const & t){
        return t < pivot;
    });

    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    std::cout << "asa" << lower_list << std::endl;

    auto new_lower(sequential_quick_sort(std::move(lower_list)));
    auto new_upper(sequential_quick_sort(std::move(input)));

    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper);

    return result;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.size() < 2)
    {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {
        return t < pivot;
    });

    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    auto new_lower(parallel_quick_sort(std::move(lower_list)));
    std::future<std::list<T>> new_upper_future(std::async(&parallel_quick_sort<T>, std::move(input)));

    result.splice(result.begin(), new_lower);
    result.splice(result.begin(), new_upper_future.get());

    return result;
}

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for(auto &i : list)
    {
        ostr << " " << i;
    }

    return ostr;
}

int main()
{
    std::list<int> list1 = { 9, 1, 11, 3, 4, 8 };

    std::chrono::system_clock::time_point start =  std::chrono::system_clock::now();

    std::list<int> data = parallel_quick_sort<int>(list1);

    auto end = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Total Time Taken = " << diff << " microseconds" << std::endl;

    // std::list<int> list2 = { 9, 1, 11, 3, 4, 8 };

    // start =  std::chrono::system_clock::now();

    // std::list<int> data2 = parallel_quick_sort<int>(list2);

    // end = std::chrono::system_clock::now();
    // diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // std::cout << "Total Time Taken = " << diff << " microseconds" << std::endl;
}