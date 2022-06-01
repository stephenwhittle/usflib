//
// Created by treys on 5/20/2022.
//

#include "gtest/gtest.h"

#include "include/unit_tests_config.hpp"
#include "eternalAdapted.hpp"

using namespace std::literals::string_view_literals;

static constexpr std::array<std::u8string_view, 4> hello_translated = {
    u8"Hello"sv,      // English
    u8"¿Qué tal?"sv,  // Spanish
    u8"Halløj"sv,     // Danish
    u8"こんにちは"sv  // Japanese
};

constexpr std::array goodbye_translated = {
    u8"Goodbye"sv,    // English
    u8"Adiós"sv,      // Spanish
    u8"Farvel"sv,     // Danish
    u8"さようなら"sv  // Japanese
};

constexpr auto ExampleData_map = eternal::translation_map({hello_translated, goodbye_translated});

//struct TranslationArray {
//  std::span<std::u8string_view> translation_array;
//};

inline consteval std::span<const std::basic_string_view<char8_t>> operator""_ta(const char8_t* str, size_t len) {
  return ExampleData_map.at(std::u8string_view{str, len});
}

inline constexpr usf::internal::Argument<char8_t> make_argument(const std::span<const std::basic_string_view<char8_t>>& arg) {
  return arg;
}

enum class Languages : uint16_t {
  English = 0,
  Spanish,
  Danish,
  Japanese};

constexpr auto ja = locale_tuple{
    Languages::Japanese,
    u8"「"sv,
    u8"」"sv};

constexpr auto da = locale_tuple{
    Languages::Danish,
    u8"“"sv,
    u8"”"sv};

auto test_func(const std::span<const std::u8string_view> test_span) {
  return test_span;
}

int main(int ac, char* av[]) {
  static_assert(u8"Hello"_ta[3] ==  u8"こんにちは"sv);

  std::array<char8_t, 256> str{};
  usf::format_to(str, ja, u8"Translated: {}", u8"Hello"_ta);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, da, u8"Translated: {}", u8"Hello"_ta);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}