#include <iostream>
#include <ranges>
#include <vector>
#include <string>

namespace rng = std::ranges;
namespace view = rng::views;

void reading_with_for() {
    std::vector<int> numbers;
    for (const auto& number : std::ranges::istream_view<int>(std::cin)) {
        if (number == -1) {
            break;
        }
        numbers.emplace_back(number);
    }
    for (const auto& x : numbers) {
        std::cout << x << '\n';
    }
}

void reading_without_for() {
    std::vector<int> numbers;

    auto generated_numbers = std::ranges::istream_view<int>(std::cin);
    auto number_pointer = generated_numbers.begin();
    while (*number_pointer != -1) {
        numbers.emplace_back(*number_pointer);
        ++number_pointer;
    }
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
}

int main()
{
    reading_without_for();
}