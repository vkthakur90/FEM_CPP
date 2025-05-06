#pragma once 

#include <algorithm>
#include <concepts>
#include <fstream>
#include <iterator>
#include <map>
#include <ranges>
#include <regex>
#include <string>
#include <stdexcept>
#include <string_view>

template<std::floating_point T>
auto parse_params_from_file(const std::string& filename) {
    // 1) Slurp file
    std::ifstream file{filename, std::ios::binary};
    if (!file) {
        throw std::runtime_error{"Could not open file: " + filename};
    }
    std::string content{
        std::istreambuf_iterator<char>{file},
        std::istreambuf_iterator<char>{}
    };

    // 2) Our regex for "set key = value;"
    static const std::regex pat{
        R"(\bset\s+(\w+)\s*=\s*([+-]?[0-9]+(?:\.[0-9]*)?)\s*;)"
    };

    // 3) Create a range of lines (each as a string_view)
    auto lines = content 
        | std::views::split('\n')
        | std::views::transform([](auto&& subrange) {
            // build a string_view pointing at the characters in content
            auto* begin = &*subrange.begin();
            return std::string_view{ begin,
                static_cast<size_t>(std::ranges::distance(subrange)) };
        });

    // 4) Filter only matching lines
    auto matching = lines
        | std::views::filter([&](std::string_view line) {
            return std::regex_search(
                line.begin(), line.end(), pat);
        });

    // 5) Transform each matching line into a pair<key,value>
    auto kv_pairs = matching
        | std::views::transform([&](std::string_view line) {
            std::cmatch m;
            std::regex_search(line.begin(), line.end(), m, pat);
            std::string key   = m[1].str();
            T           value = static_cast<T>(
                                std::stod(m[2].str()));
            return std::pair{std::move(key), value};
        });

    // 6) Collect into a map
    std::map<std::string,T> params;
    for (auto&& [k,v] : kv_pairs) {
        params.emplace(std::move(k), v);
    }
    return params;
}
