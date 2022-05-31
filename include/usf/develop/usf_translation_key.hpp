//
// Created by treys on 5/31/2022.
//

#ifndef USF_TRANSLATION_KEY_HPP
#define USF_TRANSLATION_KEY_HPP

#include <string_view>

template <typename CharT>
struct TranslationKey {
//  explicit TranslationKey(std::basic_string_view<CharT> str) : internal_sv_(str) {}
  const std::basic_string_view<CharT> internal_sv_;
};

inline TranslationKey<char> operator""_tk (const char* str, size_t len) {
  return TranslationKey<char>{std::string_view{str, len}};
}

inline TranslationKey<char8_t> operator""_tk (const char8_t* str, size_t len) {
  return TranslationKey<char8_t>{std::basic_string_view<char8_t>{str, len}};
}

#endif  // USF_TRANSLATION_KEY_HPP
