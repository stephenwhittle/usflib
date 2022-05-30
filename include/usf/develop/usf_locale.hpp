//
// Created by treys on 5/25/2022.
//

#ifndef USF_LOCALE_HPP
#define USF_LOCALE_HPP
#ifndef USF_DISABLE_LOCALE_SUPPORT

#include <array>
#include <string_view>

struct Locale {
};

struct en_US : Locale {
  static constexpr std::u8string_view decimal;
  static constexpr std::u8string_view group;
};

#endif
#endif  // USF_LOCALE_HPP
