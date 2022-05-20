
#include "unit_tests_config.hpp"

#if defined(USF_TEST_FORMAT_SPEC)

// ----------------------------------------------------------------------------
// FORMAT SPEC
// ----------------------------------------------------------------------------
TEST(usf, usf_format_to_format_spec)
{
    std::array<char, 128> str{};

    const void* ptr = reinterpret_cast<void*>(1000);

    {
        // WIDTH WITHOUT TYPE
        usf::format_to(str, "{:14}", false); EXPECT_STREQ(str.data(), "         false");
        usf::format_to(str, "{:14}", 'N'  ); EXPECT_STREQ(str.data(), "N             ");
        usf::format_to(str, "{:14}", 123  ); EXPECT_STREQ(str.data(), "           123");
        usf::format_to(str, "{:14}", 1.234); EXPECT_STREQ(str.data(), "         1.234");
        usf::format_to(str, "{:14}", ptr  ); EXPECT_STREQ(str.data(), "           3e8");
        usf::format_to(str, "{:14}", "str"); EXPECT_STREQ(str.data(), "str           ");
    }
    {
        // WIDTH + TYPE
        usf::format_to(str, "{:14c}", 'N'  ); EXPECT_STREQ(str.data(), "N             ");
        usf::format_to(str, "{:14d}", 123  ); EXPECT_STREQ(str.data(), "           123");
        usf::format_to(str, "{:14x}", 123  ); EXPECT_STREQ(str.data(), "            7b");
        usf::format_to(str, "{:14o}", 123  ); EXPECT_STREQ(str.data(), "           173");
        usf::format_to(str, "{:14b}", 123  ); EXPECT_STREQ(str.data(), "       1111011");
        usf::format_to(str, "{:14f}", 1.234); EXPECT_STREQ(str.data(), "      1.234000");
        usf::format_to(str, "{:14e}", 1.234); EXPECT_STREQ(str.data(), "  1.234000e+00");
        usf::format_to(str, "{:14g}", 1.234); EXPECT_STREQ(str.data(), "         1.234");
        usf::format_to(str, "{:14p}", ptr  ); EXPECT_STREQ(str.data(), "           3e8");
        usf::format_to(str, "{:14s}", "str"); EXPECT_STREQ(str.data(), "str           ");
    }
    {
        // PRECISION + TYPE
        usf::format_to(str, "{:.1f}", 1.234); EXPECT_STREQ(str.data(), "1.2");
        usf::format_to(str, "{:.1e}", 1.234); EXPECT_STREQ(str.data(), "1.2e+00");
        usf::format_to(str, "{:.1g}", 1.234); EXPECT_STREQ(str.data(), "1");
        usf::format_to(str, "{:.1s}", "str"); EXPECT_STREQ(str.data(), "s");

//        // PRECISION + INVALID TYPE
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1c}", 'N'), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1d}", 123), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1x}", 123), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1o}", 123), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1b}", 123), std::runtime_error);
//
//        // PRECISION WITHOUT TYPE
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", false), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 'N'  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 123  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 123  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 123  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 123  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 1.234), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 1.234), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", 1.234), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", ptr  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:.1}", "str"), std::runtime_error);
    }
    {
        // LEFT ALIGNMENT + WIDTH
        usf::format_to(str, "{:<14c}", 'N'  ); EXPECT_STREQ(str.data(), "N             ");
        usf::format_to(str, "{:<14d}", 123  ); EXPECT_STREQ(str.data(), "123           ");
        usf::format_to(str, "{:<14x}", 123  ); EXPECT_STREQ(str.data(), "7b            ");
        usf::format_to(str, "{:<14o}", 123  ); EXPECT_STREQ(str.data(), "173           ");
        usf::format_to(str, "{:<14b}", 123  ); EXPECT_STREQ(str.data(), "1111011       ");
        usf::format_to(str, "{:<14f}", 1.234); EXPECT_STREQ(str.data(), "1.234000      ");
        usf::format_to(str, "{:<14e}", 1.234); EXPECT_STREQ(str.data(), "1.234000e+00  ");
        usf::format_to(str, "{:<14g}", 1.234); EXPECT_STREQ(str.data(), "1.234         ");
        usf::format_to(str, "{:<14p}", ptr  ); EXPECT_STREQ(str.data(), "3e8           ");
        usf::format_to(str, "{:<14s}", "str"); EXPECT_STREQ(str.data(), "str           ");
    }
    {
        // RIGHT ALIGNMENT + WIDTH
        usf::format_to(str, "{:>14c}", 'N'  ); EXPECT_STREQ(str.data(), "             N");
        usf::format_to(str, "{:>14d}", 123  ); EXPECT_STREQ(str.data(), "           123");
        usf::format_to(str, "{:>14x}", 123  ); EXPECT_STREQ(str.data(), "            7b");
        usf::format_to(str, "{:>14o}", 123  ); EXPECT_STREQ(str.data(), "           173");
        usf::format_to(str, "{:>14b}", 123  ); EXPECT_STREQ(str.data(), "       1111011");
        usf::format_to(str, "{:>14f}", 1.234); EXPECT_STREQ(str.data(), "      1.234000");
        usf::format_to(str, "{:>14e}", 1.234); EXPECT_STREQ(str.data(), "  1.234000e+00");
        usf::format_to(str, "{:>14g}", 1.234); EXPECT_STREQ(str.data(), "         1.234");
        usf::format_to(str, "{:>14p}", ptr  ); EXPECT_STREQ(str.data(), "           3e8");
        usf::format_to(str, "{:>14s}", "str"); EXPECT_STREQ(str.data(), "           str");
    }
    {
        // CENTER ALIGNMENT + WIDTH
        usf::format_to(str, "{:^14c}", 'N'  ); EXPECT_STREQ(str.data(), "      N       ");
        usf::format_to(str, "{:^14d}", 123  ); EXPECT_STREQ(str.data(), "     123      ");
        usf::format_to(str, "{:^14x}", 123  ); EXPECT_STREQ(str.data(), "      7b      ");
        usf::format_to(str, "{:^14o}", 123  ); EXPECT_STREQ(str.data(), "     173      ");
        usf::format_to(str, "{:^14b}", 123  ); EXPECT_STREQ(str.data(), "   1111011    ");
        usf::format_to(str, "{:^14f}", 1.234); EXPECT_STREQ(str.data(), "   1.234000   ");
        usf::format_to(str, "{:^14e}", 1.234); EXPECT_STREQ(str.data(), " 1.234000e+00 ");
        usf::format_to(str, "{:^14g}", 1.234); EXPECT_STREQ(str.data(), "    1.234     ");
        usf::format_to(str, "{:^14p}", ptr  ); EXPECT_STREQ(str.data(), "     3e8      ");
        usf::format_to(str, "{:^14s}", "str"); EXPECT_STREQ(str.data(), "     str      ");
    }
    {
        // NUMERIC ALIGNMENT + WIDTH
        usf::format_to(str, "{:=14d}", 123  ); EXPECT_STREQ(str.data(), "           123");
        usf::format_to(str, "{:=14x}", 123  ); EXPECT_STREQ(str.data(), "            7b");
        usf::format_to(str, "{:=14o}", 123  ); EXPECT_STREQ(str.data(), "           173");
        usf::format_to(str, "{:=14b}", 123  ); EXPECT_STREQ(str.data(), "       1111011");
        usf::format_to(str, "{:=14f}", 1.234); EXPECT_STREQ(str.data(), "      1.234000");
        usf::format_to(str, "{:=14e}", 1.234); EXPECT_STREQ(str.data(), "  1.234000e+00");
        usf::format_to(str, "{:=14g}", 1.234); EXPECT_STREQ(str.data(), "         1.234");
        usf::format_to(str, "{:=14p}", ptr  ); EXPECT_STREQ(str.data(), "           3e8");

//        // NUMERIC ALIGNMENT + WIDTH + INVALID TYPE
//        CHECK_THROWS_AS(usf::format_to(str, "{:=14c}", 'N'  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:=14s}", "str"), std::runtime_error);
    }
    {
        // FILL CHAR + NUMERIC ALIGNMENT + WIDTH
        usf::format_to(str, "{:0=14d}", 123  ); EXPECT_STREQ(str.data(), "00000000000123");
        usf::format_to(str, "{:0=14x}", 123  ); EXPECT_STREQ(str.data(), "0000000000007b");
        usf::format_to(str, "{:0=14o}", 123  ); EXPECT_STREQ(str.data(), "00000000000173");
        usf::format_to(str, "{:0=14b}", 123  ); EXPECT_STREQ(str.data(), "00000001111011");
        usf::format_to(str, "{:0=14f}", 1.234); EXPECT_STREQ(str.data(), "0000001.234000");
        usf::format_to(str, "{:0=14e}", 1.234); EXPECT_STREQ(str.data(), "001.234000e+00");
        usf::format_to(str, "{:0=14g}", 1.234); EXPECT_STREQ(str.data(), "0000000001.234");
        usf::format_to(str, "{:0=14p}", ptr  ); EXPECT_STREQ(str.data(), "000000000003e8");

        usf::format_to(str, "{:0=14d}", -123  ); EXPECT_STREQ(str.data(), "-0000000000123");
        usf::format_to(str, "{:0=14x}", -123  ); EXPECT_STREQ(str.data(), "-000000000007b");
        usf::format_to(str, "{:0=14o}", -123  ); EXPECT_STREQ(str.data(), "-0000000000173");
        usf::format_to(str, "{:0=14b}", -123  ); EXPECT_STREQ(str.data(), "-0000001111011");
        usf::format_to(str, "{:0=14f}", -1.234); EXPECT_STREQ(str.data(), "-000001.234000");
        usf::format_to(str, "{:0=14e}", -1.234); EXPECT_STREQ(str.data(), "-01.234000e+00");
        usf::format_to(str, "{:0=14g}", -1.234); EXPECT_STREQ(str.data(), "-000000001.234");
    }
    {
        // ZERO FILL + WIDTH
        usf::format_to(str, "{:014d}", 123  ); EXPECT_STREQ(str.data(), "00000000000123");
        usf::format_to(str, "{:014x}", 123  ); EXPECT_STREQ(str.data(), "0000000000007b");
        usf::format_to(str, "{:014o}", 123  ); EXPECT_STREQ(str.data(), "00000000000173");
        usf::format_to(str, "{:014b}", 123  ); EXPECT_STREQ(str.data(), "00000001111011");
        usf::format_to(str, "{:014f}", 1.234); EXPECT_STREQ(str.data(), "0000001.234000");
        usf::format_to(str, "{:014e}", 1.234); EXPECT_STREQ(str.data(), "001.234000e+00");
        usf::format_to(str, "{:014g}", 1.234); EXPECT_STREQ(str.data(), "0000000001.234");
        usf::format_to(str, "{:014p}", ptr  ); EXPECT_STREQ(str.data(), "000000000003e8");

        usf::format_to(str, "{:014d}", -123  ); EXPECT_STREQ(str.data(), "-0000000000123");
        usf::format_to(str, "{:014x}", -123  ); EXPECT_STREQ(str.data(), "-000000000007b");
        usf::format_to(str, "{:014o}", -123  ); EXPECT_STREQ(str.data(), "-0000000000173");
        usf::format_to(str, "{:014b}", -123  ); EXPECT_STREQ(str.data(), "-0000001111011");
        usf::format_to(str, "{:014f}", -1.234); EXPECT_STREQ(str.data(), "-000001.234000");
        usf::format_to(str, "{:014e}", -1.234); EXPECT_STREQ(str.data(), "-01.234000e+00");
        usf::format_to(str, "{:014g}", -1.234); EXPECT_STREQ(str.data(), "-000000001.234");
    }
    {
        // HASH (integers)
        usf::format_to(str, "{:#x}", 123); EXPECT_STREQ(str.data(), "0x7b");
        usf::format_to(str, "{:#X}", 123); EXPECT_STREQ(str.data(), "0X7B");
        usf::format_to(str, "{:#o}", 123); EXPECT_STREQ(str.data(), "0173");
        usf::format_to(str, "{:#b}", 123); EXPECT_STREQ(str.data(), "0b1111011");
        usf::format_to(str, "{:#B}", 123); EXPECT_STREQ(str.data(), "0B1111011");
        usf::format_to(str, "{:#p}", ptr); EXPECT_STREQ(str.data(), "0x3e8");
        usf::format_to(str, "{:#P}", ptr); EXPECT_STREQ(str.data(), "0X3E8");

        // HASH (floating point)
        usf::format_to(str, "{:#f}", 1.234); EXPECT_STREQ(str.data(), "1.234000");
        usf::format_to(str, "{:#.0f}", 1.0); EXPECT_STREQ(str.data(), "1.");
        usf::format_to(str, "{:#e}", 1.234); EXPECT_STREQ(str.data(), "1.234000e+00");
        usf::format_to(str, "{:#.0e}", 1.0); EXPECT_STREQ(str.data(), "1.e+00");
        usf::format_to(str, "{:#g}", 1.234); EXPECT_STREQ(str.data(), "1.23400");
        usf::format_to(str, "{:#.2g}", 1.0); EXPECT_STREQ(str.data(), "1.0");
        usf::format_to(str, "{:#.0g}", 1.0); EXPECT_STREQ(str.data(), "1.");

        // HASH (negative floating point)
        usf::format_to(str, "{:#f}", -1.234); EXPECT_STREQ(str.data(), "-1.234000");
        usf::format_to(str, "{:#.0f}", -1.0); EXPECT_STREQ(str.data(), "-1.");
        usf::format_to(str, "{:#e}", -1.234); EXPECT_STREQ(str.data(), "-1.234000e+00");
        usf::format_to(str, "{:#.0e}", -1.0); EXPECT_STREQ(str.data(), "-1.e+00");
        usf::format_to(str, "{:#g}", -1.234); EXPECT_STREQ(str.data(), "-1.23400");
        usf::format_to(str, "{:#.2g}", -1.0); EXPECT_STREQ(str.data(), "-1.0");
        usf::format_to(str, "{:#.0g}", -1.0); EXPECT_STREQ(str.data(), "-1.");

//        // HASH + INVALID TYPES
//        CHECK_THROWS_AS(usf::format_to(str, "{:#c}", 'N'  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:#d}", 123  ), std::runtime_error);
//        CHECK_THROWS_AS(usf::format_to(str, "{:#s}", "str"), std::runtime_error);
    }
    {
        // FILL CHAR + ALIGNMENT + HASH (integers)
        usf::format_to(str, "{:*>#14x}", 123); EXPECT_STREQ(str.data(), "**********0x7b");
        usf::format_to(str, "{:*>#14X}", 123); EXPECT_STREQ(str.data(), "**********0X7B");
        usf::format_to(str, "{:*>#14o}", 123); EXPECT_STREQ(str.data(), "**********0173");
        usf::format_to(str, "{:*>#14b}", 123); EXPECT_STREQ(str.data(), "*****0b1111011");
        usf::format_to(str, "{:*>#14B}", 123); EXPECT_STREQ(str.data(), "*****0B1111011");
        usf::format_to(str, "{:*>#14p}", ptr); EXPECT_STREQ(str.data(), "*********0x3e8");
        usf::format_to(str, "{:*>#14P}", ptr); EXPECT_STREQ(str.data(), "*********0X3E8");

        // FILL CHAR + ALIGNMENT + HASH (negative floating point)
        usf::format_to(str, "{:*>#14f}", -1.234); EXPECT_STREQ(str.data(), "*****-1.234000");
        usf::format_to(str, "{:*>#14.0f}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
        usf::format_to(str, "{:*>#14e}", -1.234); EXPECT_STREQ(str.data(), "*-1.234000e+00");
        usf::format_to(str, "{:*>#14.0e}", -1.0); EXPECT_STREQ(str.data(), "*******-1.e+00");
        usf::format_to(str, "{:*>#14g}", -1.234); EXPECT_STREQ(str.data(), "******-1.23400");
        usf::format_to(str, "{:*>#14.2g}", -1.0); EXPECT_STREQ(str.data(), "**********-1.0");
        usf::format_to(str, "{:*>#14.0g}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*>#014x}", 123); EXPECT_STREQ(str.data(), "0x00000000007b");
        usf::format_to(str, "{:*>#014X}", 123); EXPECT_STREQ(str.data(), "0X00000000007B");
        usf::format_to(str, "{:*>#014o}", 123); EXPECT_STREQ(str.data(), "00000000000173");
        usf::format_to(str, "{:*>#014b}", 123); EXPECT_STREQ(str.data(), "0b000001111011");
        usf::format_to(str, "{:*>#014B}", 123); EXPECT_STREQ(str.data(), "0B000001111011");
        usf::format_to(str, "{:*>#014p}", ptr); EXPECT_STREQ(str.data(), "0x0000000003e8");
        usf::format_to(str, "{:*>#014P}", ptr); EXPECT_STREQ(str.data(), "0X0000000003E8");

        // FILL CHAR + ALIGNMENT + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*>#014f}", -1.234); EXPECT_STREQ(str.data(), "-000001.234000");
        usf::format_to(str, "{:*>#014.0f}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
        usf::format_to(str, "{:*>#014e}", -1.234); EXPECT_STREQ(str.data(), "-01.234000e+00");
        usf::format_to(str, "{:*>#014.0e}", -1.0); EXPECT_STREQ(str.data(), "-00000001.e+00");
        usf::format_to(str, "{:*>#014g}", -1.234); EXPECT_STREQ(str.data(), "-0000001.23400");
        usf::format_to(str, "{:*>#014.2g}", -1.0); EXPECT_STREQ(str.data(), "-00000000001.0");
        usf::format_to(str, "{:*>#014.0g}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (integers)
        usf::format_to(str, "{:*>+#14x}", 123); EXPECT_STREQ(str.data(), "*********+0x7b");
        usf::format_to(str, "{:*>+#14X}", 123); EXPECT_STREQ(str.data(), "*********+0X7B");
        usf::format_to(str, "{:*>+#14o}", 123); EXPECT_STREQ(str.data(), "*********+0173");
        usf::format_to(str, "{:*>+#14b}", 123); EXPECT_STREQ(str.data(), "****+0b1111011");
        usf::format_to(str, "{:*>+#14B}", 123); EXPECT_STREQ(str.data(), "****+0B1111011");

        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (negative floating point)
        usf::format_to(str, "{:*>+#14f}", -1.234); EXPECT_STREQ(str.data(), "*****-1.234000");
        usf::format_to(str, "{:*>+#14.0f}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
        usf::format_to(str, "{:*>+#14e}", -1.234); EXPECT_STREQ(str.data(), "*-1.234000e+00");
        usf::format_to(str, "{:*>+#14.0e}", -1.0); EXPECT_STREQ(str.data(), "*******-1.e+00");
        usf::format_to(str, "{:*>+#14g}", -1.234); EXPECT_STREQ(str.data(), "******-1.23400");
        usf::format_to(str, "{:*>+#14.2g}", -1.0); EXPECT_STREQ(str.data(), "**********-1.0");
        usf::format_to(str, "{:*>+#14.0g}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*>+#014x}", 123); EXPECT_STREQ(str.data(), "+0x0000000007b");
        usf::format_to(str, "{:*>+#014X}", 123); EXPECT_STREQ(str.data(), "+0X0000000007B");
        usf::format_to(str, "{:*>+#014o}", 123); EXPECT_STREQ(str.data(), "+0000000000173");
        usf::format_to(str, "{:*>+#014b}", 123); EXPECT_STREQ(str.data(), "+0b00001111011");
        usf::format_to(str, "{:*>+#014B}", 123); EXPECT_STREQ(str.data(), "+0B00001111011");

        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*>+#014f}", -1.234); EXPECT_STREQ(str.data(), "-000001.234000");
        usf::format_to(str, "{:*>+#014.0f}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
        usf::format_to(str, "{:*>+#014e}", -1.234); EXPECT_STREQ(str.data(), "-01.234000e+00");
        usf::format_to(str, "{:*>+#014.0e}", -1.0); EXPECT_STREQ(str.data(), "-00000001.e+00");
        usf::format_to(str, "{:*>+#014g}", -1.234); EXPECT_STREQ(str.data(), "-0000001.23400");
        usf::format_to(str, "{:*>+#014.2g}", -1.0); EXPECT_STREQ(str.data(), "-00000000001.0");
        usf::format_to(str, "{:*>+#014.0g}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (integers)
        usf::format_to(str, "{:*> #14x}", 123); EXPECT_STREQ(str.data(), "********* 0x7b");
        usf::format_to(str, "{:*> #14X}", 123); EXPECT_STREQ(str.data(), "********* 0X7B");
        usf::format_to(str, "{:*> #14o}", 123); EXPECT_STREQ(str.data(), "********* 0173");
        usf::format_to(str, "{:*> #14b}", 123); EXPECT_STREQ(str.data(), "**** 0b1111011");
        usf::format_to(str, "{:*> #14B}", 123); EXPECT_STREQ(str.data(), "**** 0B1111011");

        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (negative floating point)
        usf::format_to(str, "{:*> #14f}", -1.234); EXPECT_STREQ(str.data(), "*****-1.234000");
        usf::format_to(str, "{:*> #14.0f}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
        usf::format_to(str, "{:*> #14e}", -1.234); EXPECT_STREQ(str.data(), "*-1.234000e+00");
        usf::format_to(str, "{:*> #14.0e}", -1.0); EXPECT_STREQ(str.data(), "*******-1.e+00");
        usf::format_to(str, "{:*> #14g}", -1.234); EXPECT_STREQ(str.data(), "******-1.23400");
        usf::format_to(str, "{:*> #14.2g}", -1.0); EXPECT_STREQ(str.data(), "**********-1.0");
        usf::format_to(str, "{:*> #14.0g}", -1.0); EXPECT_STREQ(str.data(), "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*> #014x}", 123); EXPECT_STREQ(str.data(), " 0x0000000007b");
        usf::format_to(str, "{:*> #014X}", 123); EXPECT_STREQ(str.data(), " 0X0000000007B");
        usf::format_to(str, "{:*> #014o}", 123); EXPECT_STREQ(str.data(), " 0000000000173");
        usf::format_to(str, "{:*> #014b}", 123); EXPECT_STREQ(str.data(), " 0b00001111011");
        usf::format_to(str, "{:*> #014B}", 123); EXPECT_STREQ(str.data(), " 0B00001111011");

        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, "{:*> #014f}", -1.234); EXPECT_STREQ(str.data(), "-000001.234000");
        usf::format_to(str, "{:*> #014.0f}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
        usf::format_to(str, "{:*> #014e}", -1.234); EXPECT_STREQ(str.data(), "-01.234000e+00");
        usf::format_to(str, "{:*> #014.0e}", -1.0); EXPECT_STREQ(str.data(), "-00000001.e+00");
        usf::format_to(str, "{:*> #014g}", -1.234); EXPECT_STREQ(str.data(), "-0000001.23400");
        usf::format_to(str, "{:*> #014.2g}", -1.0); EXPECT_STREQ(str.data(), "-00000000001.0");
        usf::format_to(str, "{:*> #014.0g}", -1.0); EXPECT_STREQ(str.data(), "-000000000001.");
    }
}

#endif // #if defined(USF_TEST_FORMAT_SPEC)
