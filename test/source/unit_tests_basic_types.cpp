
#include "unit_tests_config.hpp"

#include "gtest/gtest.h"

#if defined(USF_TEST_BASIC_TYPES)

// ----------------------------------------------------------------------------
// BASIC TYPES
// ----------------------------------------------------------------------------
TEST(usf, format_to_basic_types)
{
    std::array<char, 128> str{};

    // Boolean type
    {
        usf::format_to(str, "{}",   false); EXPECT_STREQ(str.data(), "false");
        usf::format_to(str, "{}",   true ); EXPECT_STREQ(str.data(), "true");

        usf::format_to(str, "{:d}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:d}", true ); EXPECT_STREQ(str.data(), "1");

        usf::format_to(str, "{:x}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:x}", true ); EXPECT_STREQ(str.data(), "1");

        usf::format_to(str, "{:X}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:X}", true ); EXPECT_STREQ(str.data(), "1");

        usf::format_to(str, "{:o}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:o}", true ); EXPECT_STREQ(str.data(), "1");

        usf::format_to(str, "{:b}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:b}", true ); EXPECT_STREQ(str.data(), "1");

        usf::format_to(str, "{:B}", false); EXPECT_STREQ(str.data(), "0");
        usf::format_to(str, "{:B}", true ); EXPECT_STREQ(str.data(), "1");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", true), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", true), std::runtime_error);
    }

    // Character (char) type
    {
        usf::format_to(str, "{}",   'N'); EXPECT_STREQ(str.data(), "N");
        usf::format_to(str, "{:c}", 'N'); EXPECT_STREQ(str.data(), "N");
        usf::format_to(str, "{:d}", 'N'); EXPECT_STREQ(str.data(), "78");
        usf::format_to(str, "{:x}", 'N'); EXPECT_STREQ(str.data(), "4e");
        usf::format_to(str, "{:X}", 'N'); EXPECT_STREQ(str.data(), "4E");
        usf::format_to(str, "{:o}", 'N'); EXPECT_STREQ(str.data(), "116");
        usf::format_to(str, "{:b}", 'N'); EXPECT_STREQ(str.data(), "1001110");
        usf::format_to(str, "{:B}", 'N'); EXPECT_STREQ(str.data(), "1001110");
//
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", 'N'), std::runtime_error);
    }

    // Integer (int) type
    {
        int value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = -123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "-7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "-7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "-173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "-1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "-1111011");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (unsigned int) type
    {
        unsigned int value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = static_cast<unsigned int>(-123);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "4294967173");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "4294967173");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "ffffff85");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "FFFFFF85");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "37777777605");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "11111111111111111111111110000101");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "11111111111111111111111110000101");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (int8_t) type
    {
        int8_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = -123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "-7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "-7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "-173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "-1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "-1111011");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (uint8_t) type
    {
        uint8_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = static_cast<uint8_t>(-123);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "133");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "133");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "85");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "85");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "205");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "10000101");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "10000101");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (int16_t) type
    {
        int16_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = -123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "-7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "-7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "-173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "-1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "-1111011");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (uint16_t) type
    {
        uint16_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = static_cast<uint16_t>(-123);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "65413");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "65413");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "ff85");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "FF85");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "177605");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111111110000101");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111111110000101");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (int32_t) type
    {
        int32_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = -123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "-7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "-7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "-173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "-1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "-1111011");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (uint32_t) type
    {
        uint32_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = static_cast<uint32_t>(-123);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "4294967173");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "4294967173");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "ffffff85");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "FFFFFF85");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "37777777605");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "11111111111111111111111110000101");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "11111111111111111111111110000101");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (int64_t) type
    {
        int64_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = -123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "-123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "-7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "-7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "-173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "-1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "-1111011");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Integer (uint64_t) type
    {
        uint64_t value = 123;

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "123");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "7b");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "7B");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "173");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111011");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111011");

        value = static_cast<uint64_t>(-123);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "18446744073709551493");
        usf::format_to(str, "{:d}", value); EXPECT_STREQ(str.data(), "18446744073709551493");
        usf::format_to(str, "{:x}", value); EXPECT_STREQ(str.data(), "ffffffffffffff85");
        usf::format_to(str, "{:X}", value); EXPECT_STREQ(str.data(), "FFFFFFFFFFFFFF85");
        usf::format_to(str, "{:o}", value); EXPECT_STREQ(str.data(), "1777777777777777777605");
        usf::format_to(str, "{:b}", value); EXPECT_STREQ(str.data(), "1111111111111111111111111111111111111111111111111111111110000101");
        usf::format_to(str, "{:B}", value); EXPECT_STREQ(str.data(), "1111111111111111111111111111111111111111111111111111111110000101");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Floating point (float) type
    {
        float value = 123.456789f;

        char std_str[32]{};

        usf::format_to(str, "{}",   value); sprintf(std_str, "%g", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:f}", value); sprintf(std_str, "%f", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:F}", value); sprintf(std_str, "%F", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:e}", value); sprintf(std_str, "%e", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:E}", value); sprintf(std_str, "%E", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:g}", value); sprintf(std_str, "%g", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:G}", value); sprintf(std_str, "%G", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);

        value = -123.456789f;

        usf::format_to(str, "{}",   value); sprintf(std_str, "%g", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:f}", value); sprintf(std_str, "%f", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:F}", value); sprintf(std_str, "%F", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:e}", value); sprintf(std_str, "%e", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:E}", value); sprintf(std_str, "%E", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:g}", value); sprintf(std_str, "%g", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:G}", value); sprintf(std_str, "%G", static_cast<double>(value)); EXPECT_STREQ(str.data(), std_str);

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:d}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:x}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:X}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:o}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:b}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:B}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Floating point (double) type
    {
        double value = 123.456789;

        char std_str[32]{};

        usf::format_to(str, "{}",   value); sprintf(std_str, "%g", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:f}", value); sprintf(std_str, "%f", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:F}", value); sprintf(std_str, "%F", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:e}", value); sprintf(std_str, "%e", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:E}", value); sprintf(std_str, "%E", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:g}", value); sprintf(std_str, "%g", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:G}", value); sprintf(std_str, "%G", value); EXPECT_STREQ(str.data(), std_str);

        value = -123.456789;

        usf::format_to(str, "{}",   value); sprintf(std_str, "%g", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:f}", value); sprintf(std_str, "%f", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:F}", value); sprintf(std_str, "%F", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:e}", value); sprintf(std_str, "%e", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:E}", value); sprintf(std_str, "%E", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:g}", value); sprintf(std_str, "%g", value); EXPECT_STREQ(str.data(), std_str);
        usf::format_to(str, "{:G}", value); sprintf(std_str, "%G", value); EXPECT_STREQ(str.data(), std_str);

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:d}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:x}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:X}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:o}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:b}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:B}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:p}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:P}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Pointer (void*) type
    {
        void* value = reinterpret_cast<void*>(1000);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "3e8");
        usf::format_to(str, "{:p}", value); EXPECT_STREQ(str.data(), "3e8");
        usf::format_to(str, "{:P}", value); EXPECT_STREQ(str.data(), "3E8");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:d}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:x}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:X}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:o}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:b}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:B}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // Constant pointer (const void*) type
    {
        const void* value = reinterpret_cast<void*>(1000);

        usf::format_to(str, "{}",   value); EXPECT_STREQ(str.data(), "3e8");
        usf::format_to(str, "{:p}", value); EXPECT_STREQ(str.data(), "3e8");
        usf::format_to(str, "{:P}", value); EXPECT_STREQ(str.data(), "3E8");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:d}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:x}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:X}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:o}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:b}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:B}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", value), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:s}", value), std::runtime_error);
    }

    // String (convertible to usf::StringView) type
    {
        char s1[]{"str"};
        usf::format_to(str, "{}",   s1); EXPECT_STREQ(str.data(), "str");
        usf::format_to(str, "{:s}", s1); EXPECT_STREQ(str.data(), "str");

        const char s2[]{"str"};
        usf::format_to(str, "{}",   s2); EXPECT_STREQ(str.data(), "str");
        usf::format_to(str, "{:s}", s2); EXPECT_STREQ(str.data(), "str");

        char* s3 = s1;
        usf::format_to(str, "{}",   s3); EXPECT_STREQ(str.data(), "str");
        usf::format_to(str, "{:s}", s3); EXPECT_STREQ(str.data(), "str");

        const char* s4 = s2;
        usf::format_to(str, "{}",   s4); EXPECT_STREQ(str.data(), "str");
        usf::format_to(str, "{:s}", s4); EXPECT_STREQ(str.data(), "str");

        std::string_view sv(s1);
        usf::format_to(str, "{}",   sv); EXPECT_STREQ(str.data(), "str");
        usf::format_to(str, "{:s}", sv); EXPECT_STREQ(str.data(), "str");

//        CHECK_THROWS_AS(usf::format_to(str, "{:c}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:d}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:x}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:X}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:o}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:b}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:B}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:f}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:F}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:e}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:E}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:g}", sv), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:G}", sv), std::runtime_error);
    }
}

#endif // #if defined(USF_TEST_BASIC_TYPES)
