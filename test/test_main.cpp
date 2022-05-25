//
// Created by treys on 5/20/2022.
//

#include "gtest/gtest.h"

#include "usf/usf.hpp"

inline constexpr std::basic_string_view<char8_t>
operator""_sv8(const char8_t* str, size_t len) noexcept {
  return std::basic_string_view<char8_t>{str, len};
}

int main(int ac, char* av[]) {
  std::array<char8_t, 64> str{};
  usf::format_to(str, u8"English: {} Japanese: {}", u8"Hello"_sv8, u8"こんにちは"_sv8);
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}