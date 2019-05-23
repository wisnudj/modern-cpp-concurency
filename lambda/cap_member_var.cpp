#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class oddCounter
{
    int m_counter = 0;

public:
    int get_counter()
    {
        return m_counter;
    }

    void update(std::vector<int> &vec)
    {
        std::for_each(vec.begin(), vec.end(), [this](int element) {
            if(element % 2 == 0)
                m_counter++;
        });
    }
};

int main()
{
    std::vector<int> vec = {12,3,2,1,8,9,0,2,3,9,7};

    oddCounter countObj;
    countObj.update(vec);

    std::cout << countObj.get_counter() << std::endl;
}