#include <iostream>

#include "usf/develop/usf_config.hpp"
#include "usf/develop/usf_traits.hpp"
//#include "usf/develop/usf_string_span.hpp"
//#include "usf/develop/usf_string_view.hpp"
#include "usf/develop/usf_integer.hpp"
#include "usf/develop/usf_float.hpp"
#include "usf/develop/usf_arg_format.hpp"
#include "usf/develop/usf_arg_custom_type.hpp"
#include "usf/develop/usf_argument.hpp"
#include "usf/develop/usf_main.hpp"

using namespace std::literals::string_view_literals;

int main() {
  std::array<char, 64> str{};
  std::span<char> str_span = str;
  char* data = str_span.end().base();
  usf::format_to(str.data(), str.size(), "Hello, {}!"sv, "world");      // str == "Hello, world!"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
//  usf::format_to(str, 64, "dec:{0} hex:{0:x}", 16);    // str == "dec:16 hex:10"
//  std::cout << str << std::endl;
//  usf::format_to(str, 64, "{0}{1}{0}", "abra", "cad"); // str == "abracadabra"
//  std::cout << str << std::endl;
//  usf::StringView first_str("{0}{1}{0}");
//  usf::StringView second_str("{1}{0}{1}");
//  usf::format_to(str, 64, first_str, "abra", "cad"); // str == "abracadabra"
//  std::cout << str << std::endl;
//  usf::format_to(str, 64, second_str, "abra", "cad"); // str == "abracadabra"
//  std::cout << str << std::endl;
//  std::cout << "Hello, World!" << std::endl;
  return 0;
}
