#include <iostream>

#include "usf/develop/usf_config.hpp"
#include "usf/develop/usf_traits.hpp"
#include "usf/develop/usf_integer.hpp"
#include "usf/develop/usf_float.hpp"
#include "usf/develop/usf_arg_format.hpp"
#include "usf/develop/usf_arg_custom_type.hpp"
#include "usf/develop/usf_argument.hpp"
#include "usf/develop/usf_main.hpp"

using namespace std::literals::string_view_literals;

int main() {
  std::array<char, 64> str{};
  usf::format_to(str, "Hello, {}!"sv, "world");      // str == "Hello, world!"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, "dec:{0} hex:{0:x}", 16);    // str == "dec:16 hex:10"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, "{0}{1}{0}", "abra", "cad"); // str == "abracadabra"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  auto first_str = "{0}{1}{0}"sv;
  auto second_str = "{1}{0}{1}"sv;
  usf::format_to(str, first_str, "abra", "cad"); // str == "abracadabra"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  usf::format_to(str, second_str, "abra", "cad"); // str == "abracadabra"
  std::cout << reinterpret_cast<char*>(str.data()) << std::endl;
  return 0;
}
