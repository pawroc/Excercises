#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

class IteratorBoost : public boost::iterator_facade<IteratorBoost, std::string, boost::forward_traversal_tag>
{
public:
    IteratorBoost() : _p{nullptr} {}
    IteratorBoost(std::string* s) : _p{s} {}

private:
    friend class boost::iterator_core_access;

    void increment() { ++_p; }

    bool equal(IteratorBoost const& other) const
    {
        return _p == other._p;
    }

    std::string& dereference() const { return *_p; }

    std::string* _p;
};

class IteratorBoost2 : public boost::iterator_adaptor<IteratorBoost2, std::string*, boost::use_default, boost::forward_traversal_tag>
{
public:
    IteratorBoost2() : IteratorBoost2::iterator_adaptor_(nullptr) {}
    IteratorBoost2(std::string* s) : IteratorBoost2::iterator_adaptor_(s) {}

private:
    friend class boost::iterator_core_access;
};


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

    // Iterator begin() { return Iterator(&_data[0]); }
    // IteratorBoost begin() { return IteratorBoost(&_data[0]); }
    IteratorBoost2 begin() { return IteratorBoost2(&_data[0]); }
    // Iterator end() { return Iterator(&_data[5]); }
    // IteratorBoost end() { return IteratorBoost(&_data[5]); }
    IteratorBoost2 end() { return IteratorBoost2(&_data[5]); }

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
