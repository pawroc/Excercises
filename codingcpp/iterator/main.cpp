#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

class Iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::string;
    using pointer           = value_type*;
    using reference         = value_type&;

    Iterator(std::string* data) : _data{data} {}

    Iterator& operator++() { ++_data; return *this; }

    Iterator operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    std::string& operator*() { return *_data; }
    std::string* operator->() { return _data; }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs);
    friend bool operator==(const Iterator& lhs, const Iterator& rhs);

private:
    std::string* _data;
};

// Needed for algorithms
namespace std
{
template <>
struct iterator_traits<Iterator>
{
    using iterator_category = Iterator::iterator_category;
    using value_type        = Iterator::value_type;
    using pointer           = Iterator::pointer;
    using reference         = Iterator::reference;
};
}

bool operator==(const Iterator& lhs, const Iterator& rhs)
{
    return lhs._data == rhs._data;
}

bool operator!=(const Iterator& lhs, const Iterator& rhs)
{
    return lhs._data != rhs._data;
}

class CustomContainer
{
public:
    CustomContainer()
    {
        _data[0] = "hello1";
        _data[1] = "hello2";
        _data[2] = "hello3";
        _data[3] = "hello4";
        _data[4] = "hello5";
    }

    Iterator begin() { return Iterator(&_data[0]); }
    Iterator end() { return Iterator(&_data[5]); }

private:
    std::string _data[5];
};

int main()
{
    CustomContainer c;

    for (auto it = c.begin(); it != c.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << '\n';

    for (auto v : c)
    {
        std::cout << v << ", ";
    }
    std::cout << '\n';

    for (auto it = std::begin(c); it != std::end(c); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << '\n';

    auto it = std::find(std::begin(c), std::end(c), std::string("hello3"));
    if (it == std::end(c))
    {
        std::cout << "find_if failure\n";
    }
    else
    {
        std::cout << *it << '\n';
    }

    it = std::find(std::begin(c), std::end(c), std::string("hello9"));
    if (it == std::end(c))
    {
        std::cout << "find_if failure\n";
    }
    else
    {
        std::cout << *it << '\n';
    }

    return 0;
}
