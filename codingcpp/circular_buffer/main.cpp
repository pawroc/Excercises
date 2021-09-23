#include <iostream>
#include <array>
//#include <boost/circular_buffer.hpp>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <thread>
#include <vector>

template<typename T, size_t N>
class CircularBuffer
{
public:
    CircularBuffer() : begin_{buffer_.data()}, end_{begin_ + N}, last_{begin_}, first_{begin_}, sz_{0}, capacity_{N} {}

    void push_back(const T& val)
    {
        std::unique_lock ul{mutex_};

        std::cout << "dodaje " << val << " " << std::this_thread::get_id() << '\n';

        if (full())
        {
            if (empty())
            {
                return;
            }
            *last_ = val;
            increment(last_);
            first_ = last_;
        }
        else
        {
            *last_ = val;
            increment(last_);
            ++sz_;
        }
    }

    const T& back() const
    {
        std::unique_lock ul{mutex_};
        return *((last_ == begin_ ? end_ : last_) - 1);
    }

    const T& front() const
    {
        std::unique_lock ul{mutex_};
        return *first_;
    }

    bool full()
    {
        std::unique_lock ul{mutex_};
        return sz_ == capacity_;
    }

    bool empty()
    {
        std::unique_lock ul{mutex_};
        return sz_ == 0;
    }

    void increment(T*& ptr)
    {
        if (++ptr == end_)
        {
            ptr = begin_;
        }
    }

private:
    std::array<T, N> buffer_;
    T* begin_;
    T* end_;
    T* last_;
    T* first_;
    size_t sz_;
    size_t capacity_;
    mutable std::recursive_mutex mutex_;
};

template<typename T, size_t N>
void push(CircularBuffer<T, N>& b, int val, std::chrono::seconds t)
{
    using namespace std::chrono_literals;

    b.push_back(val);

    std::this_thread::sleep_for(t);
}

int main()
{
    using namespace std::chrono_literals;

    // boost::circular_buffer<int> bcb(3);
    // CircularBuffer<int, 3> cb;

    // bcb.push_back(1);
    // cb.push_back(1);

    // std::cout << "[1, _, _]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(2);
    // cb.push_back(2);

    // std::cout << "[1, 2, _]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(3);
    // cb.push_back(3);

    // std::cout << "[1, 2, 3]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(4);
    // cb.push_back(4);

    // std::cout << "[4, 2, 3]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(5);
    // cb.push_back(5);

    // std::cout << "[4, 5, 3]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(6);
    // cb.push_back(6);

    // std::cout << "[4, 5, 6]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    // bcb.push_back(7);
    // cb.push_back(7);

    // std::cout << "[7, 5, 6]\n";
    // std::cout << "\tback: " << bcb.back() << " : " << cb.back() << '\n';
    // std::cout << "\tfront: " << bcb.front() << " : " << cb.front() << '\n';

    CircularBuffer<int, 3> cb2;
    std::thread t1(push<int, 3>, std::ref(cb2), 1, 2s);
    std::thread t2(push<int, 3>, std::ref(cb2), 2, 1s);
    std::thread t3(push<int, 3>, std::ref(cb2), 3, 3s);

    t1.join();
    t2.join();
    t3.join();


    std::vector<int> v;
    using i = std::vector<int>::iterator;

    return 0;
}
