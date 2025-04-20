// ----------------------------------------------------------------------------
// @file    usf_argument.hpp
// @brief   Argument format processor class.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARGUMENT_HPP
#define USF_ARGUMENT_HPP

namespace usf {
  namespace internal {

    template <typename CharT>
    class Argument {
     public:
      // --------------------------------------------------------------------
      // PUBLIC TYPE ALIASES
      // --------------------------------------------------------------------

      using iterator = CharT *;
      using const_iterator = const CharT *;

      using Format = ArgFormat<CharT>;

      // --------------------------------------------------------------------
      // PUBLIC MEMBER FUNCTIONS
      // --------------------------------------------------------------------

      constexpr Argument() = delete;

      constexpr Argument(const bool value) noexcept
          : m_bool(value), m_type_id(TypeId::kBool) {}

      constexpr Argument(const CharT value) noexcept
          : m_char(value), m_type_id(TypeId::kChar) {}

      constexpr Argument(const int32_t value) noexcept
          : m_int32(value), m_type_id(TypeId::kInt32) {}

      constexpr Argument(const uint32_t value) noexcept
          : m_uint32(value), m_type_id(TypeId::kUint32) {}

      constexpr Argument(const int64_t value) noexcept
          : m_int64(value), m_type_id(TypeId::kInt64) {}

      constexpr Argument(const uint64_t value) noexcept
          : m_uint64(value), m_type_id(TypeId::kUint64) {}

      constexpr Argument(const void *value) noexcept
          : m_pointer(reinterpret_cast<std::uintptr_t>(value)), m_type_id(TypeId::kPointer) {}

#if !defined(USF_DISABLE_FLOAT_SUPPORT)

      constexpr Argument(const double value) noexcept
          : m_float(value), m_type_id(TypeId::kFloat) {}

#endif

      constexpr Argument(const std::basic_string_view<CharT> value) noexcept
          : m_string(value), m_type_id(TypeId::kString) {}

      constexpr Argument(const std::span<const std::basic_string_view<CharT>> value) noexcept
          : m_translatable_string(value), m_type_id(TypeId::kTranslatableString) {}

      constexpr Argument(const ArgCustomType<CharT> value) noexcept
          : m_custom(value), m_type_id(TypeId::kCustom) {}

      /**
       * @brief Formats the string according the the format specifier variables.
       * @param dst The string where the formatted data will be written.
       * @param format The object which contains all the format data.
       */
#if defined(USF_DISABLE_LOCALE_SUPPORT)
      constexpr void format(std::span<CharT> &dst, Format &format) const {  // std_locale is a locale which defaults to then en_US locale style, this can be customized in the usf_locale file
#else
      constexpr void format(std::span<CharT> &dst, Format &format, locale_t locale = c_locale) const { // std_locale is a locale which defaults to then en_US locale style, this can be customized in the usf_locale file
#endif
        iterator it = dst.begin().base();

        switch (m_type_id) {  // Format it according to its type
          case TypeId::kBool:
            format_bool(it, dst.end().base(), format, m_bool);
            break;
          case TypeId::kChar:
            format_char(it, dst.end().base(), format, m_char);
            break;
          case TypeId::kInt32:
            format_integer(it, dst.end().base(), format, m_int32);
            break;
          case TypeId::kUint32:
            format_integer(it, dst.end().base(), format, m_uint32);
            break;
          case TypeId::kInt64:
            format_integer(it, dst.end().base(), format, m_int64);
            break;
          case TypeId::kUint64:
            format_integer(it, dst.end().base(), format, m_uint64);
            break;
          case TypeId::kPointer:
            format_pointer(it, dst.end().base(), format, m_pointer);
            break;
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
          case TypeId::kFloat:
            format_float(it, dst.end().base(), format, m_float, locale);
            break;
#endif
          case TypeId::kString:
            format_string(it, dst.end().base(), format, m_string);
            break;
#if !defined(USF_DISABLE_LOCALE_SUPPORT)
          case TypeId::kTranslatableString:
            format_string(it, dst.end().base(), format, *(m_translatable_string.begin() + static_cast<uint16_t>(locale.identity.language)));
            break;
#endif
          case TypeId::kCustom:
            USF_ENFORCE(format.is_empty(), std::runtime_error);
            it = m_custom(dst).end().base();
            break;
        }

        dst = dst.subspan(static_cast<uint32_t>(it - dst.begin().base()));  // TODO: Sign conversion (WHY)
      }

     private:
      // --------------------------------------------------------------------
      // PRIVATE STATIC FUNCTIONS
      // --------------------------------------------------------------------

      static constexpr void format_bool(iterator &it, iterator end,
                                        const Format &format, const bool value) {
        if (format.type_is_none()) {
          format_string(it, end, format, value ? "true" : "false", value ? 4 : 5);
        } else if (format.type_is_integer()) {
          format_integer(it, end, format, static_cast<uint32_t>(value));
        } else {
          // Argument type / format mismatch
          USF_CONTRACT_VIOLATION(std::runtime_error);
        }
      }

      static constexpr void format_char(iterator &it, iterator end,
                                        Format &format, const CharT value) {
        if (format.type_is_none() || format.type_is_char()) {
          // Characters and strings align to left by default.
          format.default_align_left();

          const int fill_after = format.write_alignment(it, end, 1, false);
          *it++ = value;
          CharTraits::assign(it, format.fill_char(), fill_after);
        } else if (format.type_is_integer()) {
          format_integer(it, end, format, static_cast<int32_t>(value));
        } else {
          // Argument type / format mismatch
          USF_CONTRACT_VIOLATION(std::runtime_error);
        }
      }

      template <typename T, typename std::enable_if<std::is_signed<T>::value, bool>::type = true>
      static constexpr void format_integer(iterator &it, iterator end,
                                           const Format &format, const T value) {
        using unsigned_type = typename std::make_unsigned<T>::type;

        const bool negative = (value < 0);                                          // TODO: This shouldn't be needed with to_chars
        const auto uvalue = static_cast<unsigned_type>(negative ? -value : value);  // Get the absolute value

        format_integer(it, end, format, uvalue, negative);
      }

      template <typename T, typename std::enable_if<std::is_unsigned<T>::value, bool>::type = true>
      static constexpr void format_integer(iterator &it, iterator end, const Format &format,
                                           const T value, const bool negative = false) {
        int fill_after = 0;  //

        if (format.type_is_none() || format.type_is_integer_dec()) {  // If there is no specified format or base 10
          const auto digits = Integer::count_digits_dec(value);       // Count how many digits value has
          fill_after = format.write_alignment(it, end, digits, negative);
          it += digits;                             // Offset the iterator by the numbe of digits
                                                    //          auto [ptr, err] = std::to_chars(it, it + digits, value);  // TODO: Is it + digits always correct?
                                                    //          it = ptr;
          Integer::convert_dec(it, value);          // This function writes the number from right to left, which is why the iterator was advanced by the number of digits
        } else if (format.type_is_integer_hex()) {  // If it is hex format
          const auto digits = Integer::count_digits_hex(value);
          fill_after = format.write_alignment(it, end, digits, negative);
          it += digits;
          Integer::convert_hex(it, value, format.uppercase());
        } else if (format.type_is_integer_oct()) {  // If it is octal
          const auto digits = Integer::count_digits_oct(value);
          fill_after = format.write_alignment(it, end, digits, negative);
          it += digits;
          Integer::convert_oct(it, value);
        } else if (format.type_is_integer_bin()) {
          const auto digits = Integer::count_digits_bin(value);
          fill_after = format.write_alignment(it, end, digits, negative);
          it += digits;
          Integer::convert_bin(it, value);
        } else {
          // Argument type / format mismatch
          USF_CONTRACT_VIOLATION(std::runtime_error);
        }

        CharTraits::assign(it, format.fill_char(), fill_after);
      }

      static constexpr void format_pointer(iterator &it, const_iterator end,
                                           const Format &format, const std::uintptr_t value) {
        if (format.type_is_none() || format.type_is_pointer()) {
#if defined(USF_TARGET_64_BITS)
          const auto ivalue = static_cast<uint64_t>(value);
#else
          const auto ivalue = static_cast<uint32_t>(value);
#endif
          const auto digits = Integer::count_digits_hex(ivalue);
          const auto fill_after = format.write_alignment(it, end, digits, false);
          it += digits;
          Integer::convert_hex(it, ivalue, format.uppercase());
          CharTraits::assign(it, format.fill_char(), fill_after);
        } else {
          // Argument type / format mismatch
          USF_CONTRACT_VIOLATION(std::runtime_error);
        }
      }

#if !defined(USF_DISABLE_FLOAT_SUPPORT)

      static constexpr void format_float(iterator &it, iterator end, const Format &format, double value, locale_t locale) {
        // Test for argument type / format match
        USF_ENFORCE(format.type_is_none() || format.type_is_float(), std::runtime_error);

        if (std::isnan(value)) {
//          format_string(it, end, format, format.uppercase() ? "NAN" : "nan", 3);
          format_string(it, end, format, locale.numbers.symbols.nan.data(), static_cast<int>(locale.numbers.symbols.nan.length()));
        } else {
          const bool negative = std::signbit(value);

          if (std::isinf(value)) {
//            format_string(it, end, format, format.uppercase() ? "INF" : "inf", 3, negative);
            format_string(it, end, format, locale.numbers.symbols.infinity.data(), static_cast<int>(locale.numbers.symbols.infinity.length()), negative);
          } else {
            if (negative) { value = -value; }

            struct fp_t {
              union {
                double d;
                uint64_t i;
              };
            };

            const fp_t fp_value{{value}};

            if (fp_value.i == 0) {
              format_float_zero(it, end, format, negative);
            } else if (value >= 1E-19 && value <= 1.8446744E19) {
              int precision = format.precision();

              if (precision < 0) { precision = 6; }

              bool format_fixed = format.type_is_float_fixed();
              bool significant_figures = false;

              if (format.type_is_none() || format.type_is_float_general()) {
                // General format
                significant_figures = true;

                if (precision > 0) { --precision; }
              }

              CharT significand[36]{};  // 34 characters should be the maximum size needed
              int exponent = 0;

              const auto significand_size = Float::convert(significand, exponent, value, format_fixed, precision);

              if (significant_figures) {
                if (exponent >= -4 && exponent <= precision) {
                  format_fixed = true;
                }

                if (!format.hash()) { precision = significand_size - 1; }

                if (format_fixed) {
                  precision -= exponent;
                }
              }

              int fill_after = 0;

              if (format_fixed) {
                // Fixed point format
                if (exponent < 0) {
                  // 0.<0>SIGNIFICAND[0:N]<0>

                  const int full_digits = precision + 2;
                  fill_after = format.write_alignment(it, end, full_digits, negative);

                  *it++ = '0';
                  *it++ = static_cast<char>(locale.numbers.symbols.decimal[0]); // TODO: A better way to do this

                  int zero_digits = -exponent - 1;
                  CharTraits::assign(it, '0', zero_digits);
                  CharTraits::copy(it, significand, significand_size);

                  // Padding is needed if conversion function removes trailing zeros.
                  zero_digits = precision - zero_digits - significand_size;
                  CharTraits::assign(it, '0', zero_digits);
                } else {
                  const int full_digits = exponent + 1 + precision + static_cast<int>(precision > 0 || format.hash());
                  fill_after = format.write_alignment(it, end, full_digits, negative);

                  const int ipart_digits = exponent + 1;

                  if (ipart_digits >= significand_size) {
                    // [SIGNIFICAND]<0><.><0>

                    CharTraits::copy(it, significand, significand_size);
                    CharTraits::assign(it, '0', ipart_digits - significand_size);

                    if (precision > 0 || format.hash()) {
                      *it++ = static_cast<char>(locale.numbers.symbols.decimal[0]);
                    }

                    if (precision > 0) {
                      CharTraits::assign(it, '0', precision);
                    }
                  } else {
                    // SIGNIFICAND[0:x].SIGNIFICAND[x:N]<0>

                    CharTraits::copy(it, significand, ipart_digits);
                    *it++ = static_cast<char>(locale.numbers.symbols.decimal[0]);

                    const int copy_size = significand_size - ipart_digits;
                    CharTraits::copy(it, significand + ipart_digits, copy_size);

                    // Padding is needed if conversion function removes trailing zeros.
                    CharTraits::assign(it, '0', precision - copy_size);
                  }
                }
              } else {
                // Exponent format
                // SIGNIFICAND[0:N]<.>eEXP
                // OR
                // SIGNIFICAND[0].SIGNIFICAND[1:N]<0>eEXP

                const int full_digits = 5 + precision + static_cast<int>(precision > 0 || format.hash());
                fill_after = format.write_alignment(it, end, full_digits, negative);

                *it++ = *significand;

                if (precision > 0 || format.hash()) {
                  *it++ = static_cast<char>(locale.numbers.symbols.decimal[0]);

                  const int copy_size = significand_size - 1;
                  CharTraits::copy(it, significand + 1, copy_size);
                  CharTraits::assign(it, '0', precision - copy_size);
                }

                write_float_exponent(it, exponent, format.uppercase());
              }

              CharTraits::assign(it, format.fill_char(), fill_after);

              //it += sprintf(it, "[%s] Size:%d Exponent:%d Precision:%d Fixed:%d->", significand, significand_size, exponent, precision, int(format_fixed));
            } else {
              format_string(it, end, format, format.uppercase() ? "OVF" : "ovf", 3, negative);
            }
          }
        }
      }

      static constexpr void
      write_float_exponent(iterator &it, int exponent, const bool uppercase) noexcept {
        *it++ = uppercase ? 'E' : 'e';

        if (exponent < 0) {
          exponent = -exponent;
          *it++ = '-';
        } else {
          *it++ = '+';
        }

        // No point in making a proper integer to string
        // conversion for exponent since we only support [e-19; e19].
        assert(exponent <= 19);

        if (exponent < 10) {
          *it++ = '0';
          *it++ = static_cast<CharT>('0' + exponent);
        } else {
          *it++ = '1';
          *it++ = static_cast<CharT>('0' + (exponent - 10));
        }
      }

      static constexpr void format_float_zero(iterator &it, const_iterator end, const Format &format, const bool negative) {
        int precision = 0;

        if (format.type_is_float_fixed() || format.type_is_float_scientific()) {
          precision = format.precision();
        }

        int digits = 1;

        if (precision > 0) { digits += precision + 1; }

        if (format.type_is_float_scientific()) { digits += 4; }

        const int fill_after = format.write_alignment(it, end, digits, negative);

        *it++ = '0';

        if (precision > 0) {
          *it++ = '.';
          CharTraits::assign(it, '0', precision);
        }

        if (format.type_is_float_scientific()) {
          *it++ = format.uppercase() ? 'E' : 'e';
          *it++ = '+';
          *it++ = '0';
          *it++ = '0';
        }

        CharTraits::assign(it, format.fill_char(), fill_after);
      }

#endif  // !defined(USF_DISABLE_FLOAT_SUPPORT)

      static constexpr void format_string(iterator &it, const_iterator end,
                                          Format &format, std::basic_string_view<CharT> str) {
        // Test for argument type / format match
        USF_ENFORCE(format.type_is_none() || format.type_is_string() || format.type_is_translatable_string(), std::runtime_error);

        // Characters and strings align to left by default.
        format.default_align_left();

        // If precision is specified use it up to string size.
        const int str_length = (format.precision() == -1)
                                   ? static_cast<int>(str.size())
                                   : std::min(static_cast<int>(format.precision()), static_cast<int>(str.size()));

        format_string(it, end, format, str.data(), str_length);
      }

//      static constexpr void format_translatable_string(iterator &it, const_iterator end, Format &format, const std::basic_string_view<CharT> &str) {
//        // Test for argument type / format match
//        USF_ENFORCE(format.type_is_none() || format.type_is_translatable_string(), std::runtime_error);
//
//        // Characters and strings align to left by default.
//        format.default_align_left();
//
//        // If precision is specified use it up to string size.
//        const int str_length = (format.precision() == -1) ? static_cast<int>(str.size()) : std::min(static_cast<int>(format.precision()), static_cast<int>(str.size()));
//
//        format_string(it, end, format, str.data(), str_length);
//      }


      template <typename CharSrc,
                typename std::enable_if<std::is_convertible<CharSrc, CharT>::value, bool>::type = true>
      static constexpr void format_string(iterator &it, const_iterator end,
                                          const Format &format, const CharSrc *str,
                                          const int str_length, const bool negative = false) {
        const int fill_after = format.write_alignment(it, end, str_length, negative);

        CharTraits::copy(it, str, str_length);
        CharTraits::assign(it, format.fill_char(), fill_after);
      }

      // --------------------------------------------------------------------
      // PRIVATE MEMBER VARIABLES
      // --------------------------------------------------------------------

      enum class TypeId {
        kBool = 0,
        kChar,
        kInt32,
        kUint32,
        kInt64,
        kUint64,
        kPointer,
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
        kFloat,
#endif
        kString,
        kTranslatableString,
        kCustom
      };

      union {
        bool m_bool;
        CharT m_char;
        int32_t m_int32;
        uint32_t m_uint32;
        int64_t m_int64;
        uint64_t m_uint64;
        std::uintptr_t m_pointer;
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
        double m_float;
#endif
        std::basic_string_view<CharT> m_string;
        std::span<const std::basic_string_view<CharT>> m_translatable_string;
        ArgCustomType<CharT> m_custom;
      };

      TypeId m_type_id;
    };

    // Boolean
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const bool arg) {
      return arg;
    }

    // Character (char)
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const char arg) {
      return static_cast<CharT>(arg);
    }

    // Character (CharT != char)
    template <typename CharT, typename std::enable_if<!std::is_same<CharT, char>::value, bool>::type = true>
    inline constexpr Argument<CharT>
    make_argument(const CharT arg) {
      return arg;
    }

    // 8 bit signed integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const int8_t arg) {
      return static_cast<int32_t>(arg);
    }

    // 8 bit unsigned integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const uint8_t arg) {
      return static_cast<uint32_t>(arg);
    }

    // 16 bit signed integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const int16_t arg) {
      return static_cast<int32_t>(arg);
    }

    // 16 bit unsigned integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const uint16_t arg) {
      return static_cast<uint32_t>(arg);
    }

    // 32 bit signed integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const int arg) {
      return static_cast<int32_t>(arg);
    }

    // 32 bit unsigned integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const unsigned int arg) {
      return static_cast<uint32_t>(arg);
    }

#if (__LONG_MAX__ != __LONG_LONG_MAX__)

    // 32 bit signed integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const long int arg) {
      return static_cast<int32_t>(arg);
    }

    // 32 bit unsigned integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const unsigned long int arg) {
      return static_cast<uint32_t>(arg);
    }

#endif  // (__LONG_MAX__ != __LONG_LONG_MAX__)

    // 64 bit signed integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const int64_t arg) {
      if (arg >= std::numeric_limits<int32_t>::min()
          && arg <= std::numeric_limits<int32_t>::max()) {
        return static_cast<int32_t>(arg);
      }

      return arg;
    }

    // 64 bit unsigned integer
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const uint64_t arg) {
      if (arg <= std::numeric_limits<uint32_t>::max()) {
        return static_cast<uint32_t>(arg);
      }

      return arg;
    }

    // Pointer (void*)
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(void *arg) {
      return arg;
    }

    // Pointer (const void*)
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(const void *arg) {
      return arg;
    }

#if !defined(USF_DISABLE_FLOAT_SUPPORT)

    // Floating point (float)
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(float arg) {
      return static_cast<double>(arg);
    }

    // Floating point (double)
    template <typename CharT>
    inline constexpr Argument<CharT>
    make_argument(double arg) {
      return arg;
    }

#endif  // !defined(USF_DISABLE_FLOAT_SUPPORT)

    // String (convertible to string view)
    template <typename CharT, typename T,
              typename std::enable_if<std::is_convertible<T, std::basic_string_view<CharT>>::value, bool>::type = true>
    inline constexpr Argument<CharT> make_argument(const T &arg) {
      return std::basic_string_view<CharT>(arg);
    }

    // Translation key
    template <typename CharT>
    inline constexpr Argument<CharT> make_argument(const std::span<const std::basic_string_view<CharT>>& arg) {
      return arg;
    }

  }  // namespace internal

  // User-defined custom type formatter forward declaration
  template <typename CharT, typename T>
  struct Formatter {
    static std::span<CharT> format_to(std::span<CharT>, const T &);
  };

  namespace internal {

    // User-defined custom type
    template <typename CharT, typename T, typename std::enable_if<!std::is_convertible<T, std::basic_string_view<CharT>>::value, bool>::type = true>
    inline constexpr Argument<CharT> make_argument(const T &arg) {
      using decay_T = typename std::decay<decltype(arg)>::type;

      return ArgCustomType<CharT>::template create<decay_T, &usf::Formatter<CharT, decay_T>::format_to>(&arg);
    }

  }  // namespace internal
}  // namespace usf

#endif  // USF_ARGUMENT_HPP
