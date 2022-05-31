//
// Created by treys on 5/25/2022.
//

#ifndef USF_LOCALE_HPP
#define USF_LOCALE_HPP
#ifndef USF_DISABLE_LOCALE_SUPPORT

#include <array>
#include <string_view>
#include <tuple>
#include <span>

using namespace std::string_view_literals;

enum class Languages : uint16_t;

using locale_tuple = std::tuple<Languages, std::u8string_view, std::u8string_view>;

struct Translatable {
  explicit constexpr Translatable(auto translation, locale_tuple tup)
      : translations_(translation), current_locale_(tup) {}

  //  auto Locale(locale_tuple&& new_locale) -> void {
  //    locale = std::get<0>(new_locale);
  //  }

//  auto Translate() -> std::u8string_view {
//    return *(translations_.begin() + static_cast<uint16_t>(std::get<0>(current_locale_)));
//  }

  const std::span<std::u8string_view> translations_;
  locale_tuple current_locale_;
};

constexpr auto c_locale = locale_tuple{
    static_cast<Languages>(0),
    u8"「"sv,
    u8"」"sv};

constexpr std::array c_translated = {
    u8""sv
};

inline Translatable std_locale(c_translated, c_locale); // TODO: Move

#endif
#endif  // USF_LOCALE_HPP
