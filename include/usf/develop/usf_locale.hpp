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

using namespace std::string_view_literals;

enum class Languages : uint16_t;

namespace usf {
  struct LocaleData {
    const Languages language;
    const std::u8string_view start_quote;
    const std::u8string_view end_quote;
  };

  constexpr LocaleData c_locale {
      .language = static_cast<Languages>(0),
      .start_quote = u8"“"sv,
      .end_quote = u8"”"sv};

  using locale_t = LocaleData;

  inline locale_t std_locale = c_locale;
}  // namespace usf

#endif
#endif  // USF_LOCALE_HPP
