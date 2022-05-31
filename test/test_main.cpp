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

constexpr auto da = locale_tuple{
    Languages::Danish,
    u8"“"sv,
    u8"”"sv};

constexpr std::array hello_translated = {
    u8"Hello"sv,      // English
    u8"¿Qué tal?"sv,  // Spanish
    u8"Halløj"sv,     // Danish
    u8"こんにちは"sv  // Japanese
};


int main(int ac, char* av[]) {
Translatable translatable(hello_translated, ja);
  std::array<char8_t, 256> str{};
  usf::format_to(str, translatable, u8"Translated: {:t}", u8"Hello"_tk);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  translatable.current_locale_ = da;
  usf::format_to(str, translatable, u8"Translated: {}", u8"Hello"_tk);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}