//
// Created by treys on 5/25/2022.
//

#ifndef USF_LOCALE_HPP
#define USF_LOCALE_HPP
#ifndef USF_DISABLE_LOCALE_SUPPORT

#include <array>
#include <span>
#include <string_view>
#include <tuple>

#include "usf_locales_territories.hpp"

///**
// * @brief Converts an eternal::translation_map into an array of translation strings.
// * @param str The string literal which is the key for the translation_map.
// * @param len The length of the string literal.
// * @returns The underlying array found using the map key preceding it.
// */
//// Make this local to the translation unit using maybe an anonymous namespace? Not sure if it should be in macro
//// Shouldn't need to wrap in inline namespaces since it will be in the anonymous namespace local to the TU by default
//#define USF_TRANSLATION_ARRAY_FUNCTION(MAP_NAME) \
//  namespace {                                               \
//  inline consteval std::span<const std::u8string_view> operator""_ta(const char8_t* str, size_t len) { \
//    return MAP_NAME.at(std::u8string_view{str, len});                                                \
//  }}

using namespace std::string_view_literals;

namespace usf {
  using cldr_t = std::u8string_view;

  // REQUIRED
  struct Symbols {
    cldr_t decimal;
    cldr_t group;
    cldr_t list;
    cldr_t percent_sign;
    cldr_t plus_sign;
    cldr_t minus_sign;
    cldr_t exponential;
    cldr_t superscripting_exponent;
    cldr_t per_mille;
    cldr_t infinity;
    cldr_t nan;
    cldr_t time_separator;
  };

  struct Numbers {
    Symbols symbols;
  };

  struct Identity {
    uint8_t revision;
    Languages language;
    Territories territory;
  };

  struct Locale {
    Identity identity;
    Numbers numbers;
  };

  constexpr Locale c_locale{
      .identity = {
          .revision = 41,
          .language = Languages::en,
          .territory = Territories::US},
      .numbers = {.symbols = {.decimal = u8"."sv, .group = u8","sv, .list = u8";"sv, .percent_sign = u8"%"sv, .plus_sign = u8"+"sv, .minus_sign = u8"-"sv, .exponential = u8"E"sv, .superscripting_exponent = u8"×"sv, .per_mille = u8"‰"sv, .infinity = u8"∞"sv, .nan = u8"NaN"sv, .time_separator = u8":"sv}}};

  using locale_t = Locale;
}  // namespace usf

#endif
#endif  // USF_LOCALE_HPP
