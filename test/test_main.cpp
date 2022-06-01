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

inline consteval std::span<const std::basic_string_view<char8_t>> operator""_ta(const char8_t* str, size_t len) {
  return ExampleData_map.at(std::u8string_view{str, len});
}

enum class Languages : uint16_t {
  English = 0,
  Spanish,
  Danish,
  Japanese};

constexpr usf::locale_t ja {
    .language = Languages::Japanese,
    .start_quote = u8"「"sv,
    .end_quote = u8"」"sv};

constexpr usf::locale_t da {
    .language = Languages::Danish,
    .start_quote = u8"“"sv,
    .end_quote = u8"”"sv};

int main(int ac, char* av[]) {
  static_assert(u8"Hello"_ta[3] ==  u8"こんにちは"sv);

  std::array<char8_t, 256> str{};
  usf::format_to(str, ja, u8"Translated: {}", u8"Hello"_ta);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, da, u8"Translated: {:t}", u8"Hello"_ta);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}