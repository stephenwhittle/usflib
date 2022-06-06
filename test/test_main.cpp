//
// Created by treys on 5/20/2022.
//

#include "eternalAdapted.hpp"
#include "gtest/gtest.h"
#include "include/unit_tests_config.hpp"

using namespace std::literals::string_view_literals;

// Translation arrays must be in alphabetical order by their 2 letter language identifier with en being first
static constexpr std::array<std::u8string_view, 4> hello_translated = {
    u8"Hello"sv,      // en
    u8"Halløj"sv,     // da
    u8"¿Qué tal?"sv,  // es
    u8"こんにちは"sv  // jp
};

constexpr std::array goodbye_translated = {
    u8"Goodbye"sv,    // en
    u8"Farvel"sv,     // da
    u8"Adiós"sv,      // es
    u8"さようなら"sv  // jp
};

constexpr auto ExampleData_map = eternal::translation_map({hello_translated, goodbye_translated});

/**
 * @brief Converts a eternal::translation_map into an array of translation strings.
 * @param str The string literal which is the key for the translation_map.
 * @param len The length of the string literal.
 * @returns The underlying array found using the map key preceding it.
 */
inline consteval std::span<const std::u8string_view> operator""_ta(const char8_t* str, size_t len) {
  return ExampleData_map.at(std::u8string_view{str, len});
}

usf::Locale en_US {
    .identity = {
        .revision = 41,
        .language = usf::Languages::en,
        .territory = usf::Territories::US
    },
    .numbers = {
        .symbols = {
            .decimal = u8"."sv,
            .group = u8","sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8"None"sv
        }
    }
};

usf::Locale es_ES {
    .identity = {
        .revision = 41,
        .language = usf::Languages::es,
        .territory = usf::Territories::ES
    },
    .numbers = {
        .symbols = {
            .decimal = u8","sv,
            .group = u8"."sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8":"sv
        }
    }
};

usf::Locale da_DK {
    .identity = {
        .revision = 41,
        .language = usf::Languages::da,
        .territory = usf::Territories::DK
    },
    .numbers = {
        .symbols = {
            .decimal = u8","sv,
            .group = u8"."sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8"."sv
        }
    }
};

usf::Locale ja_JP {
    .identity = {
        .revision = 41,
        .language = usf::Languages::ja,
        .territory = usf::Territories::JP
    },
    .numbers = {
        .symbols = {
            .decimal = u8"."sv,
            .group = u8","sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8":"sv
        }
    }
};

int main(int ac, char* av[]) {
  std::array<char8_t, 256> str{};
  usf::format_to(str, ja_JP, u8"Translated: {}, float: {}", u8"Hello"_ta, 3.1415F);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, da_DK, u8"Translated: {:t}, float: {}", u8"Hello"_ta, std::numeric_limits<float>::infinity());
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, en_US, u8"Translated: {}, float: {}", u8"Hello"_ta, 3.1415F);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, es_ES, u8"Translated: {:t}, float: {}", u8"Hello"_ta, std::numeric_limits<float>::quiet_NaN());
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}