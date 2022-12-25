#include <iostream>
#include <ranges>
#include <string>
#include <vector>

namespace rng = std::ranges;
namespace view = rng::views;

class Person
{
public:
    std::string name;
    std::string sername;
};

template < typename InputIter >
auto sum(InputIter begin, InputIter end)
{
    if (begin == end) {
        return 0;
    }
    auto sum{ *begin };
    for (auto iter{ ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}

template < typename InputIter >
int len(InputIter begin, InputIter end)
{
    int len = 0;
    for (auto iter{ begin }; iter != end; ++iter) {
        ++len;
    }
    return len;
}

int main()
{
    
    std::vector<std::pair<Person, int>> age_information;
    for (int age : view::iota(1, 11)) {
        age_information.emplace_back(std::make_pair(Person(), age*age));
    }

    auto take_age = [](std::pair<Person, int> inf) {return inf.second; };
    auto age_filter = [](int age) {return age >= 12 && age <= 65; };
    auto ages = age_information | view::transform(take_age) |
        view::filter(age_filter);
    for (auto number : ages) {
        std::cout << number << std::endl;
    }
    int ages_len = len(ages.begin(), ages.end());
    std::cout << (ages_len > 0 ? sum(ages.begin(), ages.end()) / ages_len: 0);
}
