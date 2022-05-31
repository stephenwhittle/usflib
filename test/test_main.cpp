//
// Created by treys on 5/20/2022.
//

#include "gtest/gtest.h"

#include "include/unit_tests_config.hpp"

enum class Languages : uint16_t {
  English = 0,
  Spanish,
  Danish,
  Japanese};

constexpr auto ja = locale_tuple{
    Languages::Japanese,
    u8"「"sv,
    u8"」"sv};

constexpr std::array hello_translated = {
    u8"Hello"sv,      // English
    u8"¿Qué tal?"sv,  // Spanish
    u8"Halløj"sv,     // Danish
    u8"こんにちは"sv  // Japanese
};

Translatable translatable(hello_translated, ja);

int main(int ac, char* av[]) {
  std::array<char8_t, 64> str{};
  usf::format_to(str, ja, u8"Translated: {}", u8"Hello"_tk);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}