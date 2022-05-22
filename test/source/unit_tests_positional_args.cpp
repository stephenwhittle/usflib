
#include "unit_tests_config.hpp"

#if defined(USF_TEST_POSITIONAL_ARGS)

// ----------------------------------------------------------------------------
// POSITIONAL ARGUMENTS
// ----------------------------------------------------------------------------
TEST(usf, usf_format_to_positional_indices) {
  std::array<char, 32> str{};

  usf::format_to(str, "{0}{1}{0}", "abra", "cad");
  EXPECT_STREQ(str.data(), "abracadabra");

  // The following test shows both the positional and
  // sequencial arguments working seamlessly together.

  usf::format_to(str, "{}{}{0}", "abra", "cad");
  EXPECT_STREQ(str.data(), "abracadabra");

  usf::format_to(str, "{0}{1}{}", "abra", "cad");
  EXPECT_STREQ(str.data(), "abracadabra");

  usf::format_to(str, "{}{1}{0}", "abra", "cad");
  EXPECT_STREQ(str.data(), "abracadabra");
}

#endif // #if defined(USF_TEST_POSITIONAL_ARGS)
