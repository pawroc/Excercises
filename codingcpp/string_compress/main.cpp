#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

std::string compress(const std::string& str)
{
    if (str.size() <= 1) return str;

    std::stringstream result;
    auto it = std::cbegin(str);

    while (it != std::cend(str))
    {
        char c = *it;
        auto it2 = std::find_if_not(it, std::cend(str), [&c](const auto& cc) { return cc == c; });
        auto d = std::distance(it, it2);

        if (d > 1)
        {
            result << c << d;
        }
        else
        {
            result << std::string(d, c);
        }
        it = it2;
    }

    return result.str();
}

int main()
{
    std::string s1{"aabbbccccdddd"}, s2{""}, s3{"abcd"}, s4{"a"}, s5{"abcdddddd"}, s6{"aaaaaaaaabcd"}, s7{"abcccccd"};

    std::cout << std::quoted(s1) << " skompresowany: " << std::quoted(compress(s1)) << '\n';
    std::cout << std::quoted(s2) << " skompresowany: " << std::quoted(compress(s2)) << '\n';
    std::cout << std::quoted(s3) << " skompresowany: " << std::quoted(compress(s3)) << '\n';
    std::cout << std::quoted(s4) << " skompresowany: " << std::quoted(compress(s4)) << '\n';
    std::cout << std::quoted(s5) << " skompresowany: " << std::quoted(compress(s5)) << '\n';
    std::cout << std::quoted(s6) << " skompresowany: " << std::quoted(compress(s6)) << '\n';
    std::cout << std::quoted(s7) << " skompresowany: " << std::quoted(compress(s7)) << '\n';
    return 0;
}
