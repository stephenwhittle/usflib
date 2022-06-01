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

namespace usf {
  using locale_t = std::tuple<Languages, std::u8string_view, std::u8string_view>;

  constexpr auto c_locale = locale_t{
      static_cast<Languages>(0),
      u8"“"sv,
      u8"”"sv};

  inline locale_t std_locale = c_locale;
}

#endif
#endif  // USF_LOCALE_HPP
