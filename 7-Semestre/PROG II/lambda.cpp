#include <iostream>

int main(int argc, char const *argv[])
{
    auto add = [](int a, int b)
    {
        return a + b;
    };

    std::cout << add(2, 2);
    return 0;
}
