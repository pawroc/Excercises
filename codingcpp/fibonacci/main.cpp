#include <iostream>

size_t fib(size_t n)
{
    if (n <= 1) return n;

    size_t first = 0;
    size_t second = 1;
    size_t result = 0;

    for (size_t i = 1; i < n; ++i)
    {
        result = first + second;
        first = second;
        second = result;
    }
    return result;
}

int main()
{
    for (size_t i = 0; i < 13; ++i)
    {
        std::cout << "fib(" << i << ") = " << fib(i) << '\n';
    }
    return 0;
}
