#include <iostream>
#include <ranges>
#include <string>

namespace rng = std::ranges;
namespace view = rng::views;

int main() {
    int cicle_begin = 10;
    int cicle_end = 100;
    auto even = [](int i) { return i % 5 != 0; };
    auto square_and_to_str = [](int i) { return std::to_string(i * i); };
    auto generated_numbers = view::iota(cicle_begin, cicle_end + 1) | view::filter(even) |
        view::transform(square_and_to_str);
    for (auto number : generated_numbers) {
        std::cout << number << std::endl;
    }
}
