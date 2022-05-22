//
// Created by treys on 5/20/2022.
//

#include "gtest/gtest.h"

#include <charconv>
#include <numeric>

#include "usf/develop/usf_config.hpp"
#include "usf/develop/usf_traits.hpp"
#include "usf/develop/usf_integer.hpp"
#include "usf/develop/usf_float.hpp"
#include "usf/develop/usf_arg_format.hpp"
#include "usf/develop/usf_arg_custom_type.hpp"
#include "usf/develop/usf_argument.hpp"
#include "usf/develop/usf_main.hpp"

//void format_float(char*& it, char*& end, float value) {
//  std::to_chars(it, end, value);
//}

int main(int ac, char* av[]) {
////  float num = std::numeric_limits<float>::infinity();
////  float num = -std::numeric_limits<float>::infinity();
////  float num = std::numeric_limits<float>::quiet_NaN();
  std::array<char, 50> str{};
////  std::to_chars(str.data(), str.begin() + str.size(), num);
  usf::format_to(str, "{:.3f}", 31.4159F);
  std::cout << str.data() << std::endl;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}