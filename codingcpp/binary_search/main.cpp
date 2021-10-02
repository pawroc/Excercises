#include <iostream>
#include <array>
#include <cmath>
#include <optional>

int recursiveBinarySearch(const std::vector<int> &vec, int left, int right, int lookup){
    if (right >= left) {
        int mid = left + (right - left) / 2;
  
        if (vec[mid] == lookup)
            return true;
  
        if (vec[mid] > lookup)
            return ownBinarySearch(vec, left, mid - 1, lookup);
  
        return ownBinarySearch(vec, mid + 1, right, lookup);
    }
  
    return false;
}

template<size_t N>
std::optional<size_t> find(std::array<int, N> arr, int val)
{
    // if (arr[0] > val)
    // {
    //     // tablica nieposortowana
    //     return std::nullopt;
    // }

    size_t b = 0;
    size_t e = arr.size() - 1;
    size_t step{0};
    size_t idx{0};

    do
    {
        if (arr[idx] < val)
        {
            if (idx != b)
            {
                b = idx + 1;
            }
            step = std::ceil(static_cast<double>(e - idx) / 2);
            idx += step;
        }
        else if (arr[idx] > val)
        {
            e = idx - 1;
            step = std::ceil(static_cast<double>(idx - b) / 2);
            idx -= step;
        }
    } while (step != 0 and arr[idx] != val);
    

    return arr[idx] == val ? std::make_optional(idx) : std::nullopt;
}

template<size_t N>
std::optional<size_t> find2(std::array<int, N> arr, int val)
{
    size_t b = 0;
    size_t e = arr.size() - 1;

    std::optional<size_t> result{std::nullopt};

    while (e - b > 1 and not result)
    {
        size_t idx = (e + b) / 2;

        if (arr[idx] == val)
        {
            result = idx;
        }
        else if (arr[idx] > val)
        {
            e = idx - 1;
        }
        else
        {
            b = idx + 1;
        }
    }

    if (not result and arr[b] == val)
    {
        result = b;
    }
    else if (not result and arr[e] == val)
    {
        result = e;
    }

    return result;
}

int main()
{
    std::array<int, 9> a1{0, 1, 2, 4, 5, 6, 7, 8, 9};

    for (int val = 0; val <= 10; ++val)
    {
        auto i = find(a1, val);

        if (i)
        {
            std::cout << "found: " << a1[*i] << '\n';
        }
        else
        {
            std::cout << "not found value " << val << '\n';
        }

        auto i2 = find2(a1, val);

        if (i2)
        {
            std::cout << "found2: " << a1[*i2] << '\n';
        }
        else
        {
            std::cout << "not found2 value " << val << '\n';
        }
    }
    return 0;
}
