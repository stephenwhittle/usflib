// ----------------------------------------------------------------------------
// @file    usf_arg_format.hpp
// @brief   Argument format parser class.
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARG_FORMAT_HPP
#define USF_ARG_FORMAT_HPP

namespace usf::internal {

  template <typename CharT>
  class ArgFormat {
   public:
    // --------------------------------------------------------------------
    // PUBLIC TYPE ALIASES
    // --------------------------------------------------------------------

    using iterator = CharT *;
    using const_iterator = const CharT *;

    // --------------------------------------------------------------------
    // PUBLIC DEFINITIONS
    // --------------------------------------------------------------------

    enum class Align : uint8_t {
      kNone = (0U << 1U),
      kLeft = (1U << 1U),
      kRight = (2U << 1U),
      kCenter = (3U << 1U),
      kNumeric = (4U << 1U)
    };

    enum class Sign : uint8_t {
      kNone = (0U << 4U),
      kMinus = (1U << 4U),
      kPlus = (2U << 4U),
      kSpace = (3U << 4U)
    };

    enum class Type : uint8_t {
      kNone,
      kChar,
      kIntegerDec,
      kIntegerHex,
      kIntegerOct,
      kIntegerBin,
      kPointer,
      kFloatFixed,
      kFloatScientific,
      kFloatGeneral,
      kString,
      kInvalid
    };

    // --------------------------------------------------------------------
    // PUBLIC MEMBER FUNCTIONS
    // --------------------------------------------------------------------

    /**
     * @brief Parses format specifier strings into its respective variables.
     * @param fmt The string_view  to the format string.
     * @param arg_count The number of format specifiers in the entire string, used for checking positional argument index validity.
     */
    constexpr ArgFormat(std::basic_string_view<CharT> &fmt, const int arg_count) {  // TODO: Divide more
      // An fmt string of {:d} is used as an example, but the same principle applies to formats using other characters (eg {:f}, {:b})
      // At this point, the fmt string_view contains format instructions in the form of {:d}
      const_iterator it = fmt.cbegin();  // This iterator will iterate through the fmt string to figure out what the format is

      USF_ENFORCE(*it == '{', std::runtime_error);  // Make sure that the format starts with a { otherwise something has gone wrong in parsing the args

      ++it;  // Move the iterator past the '{' character

      if (*it >= '0' && *it <= '9') {  // This is entered when the format is a positional argument (eg {0}, {1})
        // Index limited to `arg_count` value.
        m_index = static_cast<int8_t>(parse_positive_small_int(it, arg_count));  // TODO: What this does
      }

      // At this point the  iterator string is ":d}"
      if (*it == ':' && *(it + 1) != '}') {  // This is entered when there is a character between the ':' and ending '}'
        // A format spec is expected next...
        m_flags = Flags::kNone;  // TODO: What do flags do

        ++it;  // Remove the empty format flag (which is ':')

        // Try to parse alignment flag at second character of format spec as a fill character is first
        m_flags = parse_align_flag(*(it + 1));  // This would, for example, apply for a {:_=14d}, where the '=' is numeric align and '_' is the fill char

        if (m_flags != Flags::kNone) {                                // If an alignment character was found at the second character, extract the fill character
          USF_ENFORCE(*it != '{' && *it != '}', std::runtime_error);  // The fill character can be any character except '{' or '}'

          m_fill_char = *it;                // The fill character should be at the current iterator since the alignment is in the next position
          it += 2;                          // Increment past both the fill and alignment characters
        } else {                            // Alignment flag not present at the second character of format spec, so try to parse the alignment flag at the first character instead
          m_flags = parse_align_flag(*it);  // Attempt a parse at single character, eg for {:=14d}

          if (m_flags != Flags::kNone) {  // If an alignment character was found, increment the iterator past it
            ++it;
          }
        }

        // Parse sign flag
        switch (*it) {
          case '-':
            m_flags |= Flags::kSignMinus;
            ++it;
            break;
          case '+':
            m_flags |= Flags::kSignPlus;
            ++it;
            break;
          case ' ':
            m_flags |= Flags::kSignSpace;
            ++it;
            break;
          default:
            break;
        }

        // Parse hash flag
        if (*it == '#') {
          m_flags |= Flags::kHash;
          ++it;
        }

        bool fill_zero = false;

        // Parse fill zero flag
        if (*it == '0') {    // Zero pading looks like "{:014d}" where 14 is the total width
          fill_zero = true;  // If the iterator is 0, then there is 0 fill
          ++it;              // Proceed past the '0'
        }

        // Parse width
        if (*it >= '0' && *it <= '9') {                 // Parse how many characters wide the format should end up as
          m_width = parse_positive_small_int(it, 255);  // Limit width to 255 characters
        }

        // Parse precision
        if (*it == '.') {  // Check for the decimal point which signifies a float precision
          ++it;
          USF_ENFORCE(*it >= '0' && *it <= '9', std::runtime_error);             // Check for a missing/invalid precision specifier
          m_precision = static_cast<int8_t>(parse_positive_small_int(it, 127));  // Extract the precision length from the string
        }

        // Parse type
        if (*it != '}') {  // Check that the format isn't something like {}
          switch (*it++) {
            // Check each of the possible types
            case 'c':
              m_type = Type::kChar;
              break;

            case 'd':
              m_type = Type::kIntegerDec;
              break;

            case 'X':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'x':
              m_type = Type::kIntegerHex;
              break;

            case 'o':
              m_type = Type::kIntegerOct;
              break;

            case 'B':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'b':
              m_type = Type::kIntegerBin;
              break;

            case 'P':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'p':
              m_type = Type::kPointer;
              break;

            case 'F':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'f':
              m_type = Type::kFloatFixed;
              break;

            case 'E':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'e':
              m_type = Type::kFloatScientific;
              break;

            case 'G':
              m_flags |= Flags::kUppercase;
              USF_FALLTHROUGH;
            case 'g':
              m_type = Type::kFloatGeneral;
              break;

            case 's':
              m_type = Type::kString;
              break;

            default:  // A character specifier must be found otherwise there is an error
              m_type = Type::kInvalid;
              break;
          }

          USF_ENFORCE(m_type != Type::kInvalid, std::runtime_error);
        }

        // Validate the read format spec!

        if (fill_zero) {
          // Fill zero flag has precedence over any other alignment and fill character.
          m_flags = static_cast<uint8_t>((m_flags & (~Flags::kAlignBitmask)) | Flags::kAlignNumeric);
          m_fill_char = '0';
        }

        if (align() == Align::kNumeric) {
          // Numeric alignment are only valid for numeric and pointer types.
          USF_ENFORCE(type_is_numeric() || type_is_pointer(), std::runtime_error);
        }

        if (sign() != Sign::kNone) {
          // Sign is only valid for numeric types.
          USF_ENFORCE(type_is_numeric(), std::runtime_error);
        }

        if (hash()) {
          // Alternative format is valid for hexadecimal (including
          // pointers), octal, binary and all floating point types.
          USF_ENFORCE(type_allow_hash(), std::runtime_error);
        }

        if (m_precision != -1) {
          // Precision is only valid for floating point and string types.
          USF_ENFORCE(type_is_float() || type_is_string(), std::runtime_error);
        }
      }

      // Test for unterminated argument format spec.
      USF_ENFORCE(it < fmt.cend() && *it++ == '}', std::runtime_error);

      fmt.remove_prefix(static_cast<uint32_t>(it - fmt.cbegin()));  // TODO: Resolve sign error better
    }

    // Writes the alignment (sign, prefix and fill before) for any
    // argument type. Returns the fill counter to write after argument.
    constexpr int write_alignment(iterator &it, const_iterator end, int digits, const bool negative) const {  // TODO: Figure out what this does
      digits += sign_width(negative) + prefix_width();

      int fill_after = 0;

      if (width() <= digits) {                               // If the width of the numbers is <= the calculated full length, it means that there is a negative sign / prefix (eg hex, bin, oct) or it is a decimal number
        USF_ENFORCE(it + digits < end, std::runtime_error);  // Check that the total width of the characters to be written does not exceed the size of the buffer
        write_sign(it, negative);                            // Write a negative sign if applicable
        write_prefix(it);                                    // Write the prefix if applicable
      } else {
        USF_ENFORCE(it + width() < end, std::runtime_error);  // Check that the total width of the characters to be written by appending the number will not exceed the buffer size

        int fill_count = width() - digits;  //

        const Align al = align();

        if (al == Align::kLeft) {
          fill_after = fill_count;
        } else if (al == Align::kCenter) {
          fill_after = fill_count - (fill_count / 2);
          fill_count /= 2;
        }

        if (al != Align::kLeft && al != Align::kNumeric) {  // If it is right align
          // None (default right), Right or Center alignment
          CharTraits::assign(it, fill_char(), fill_count);
        }

        write_sign(it, negative);
        write_prefix(it);

        if (al == Align::kNumeric) {
          CharTraits::assign(it, fill_char(), fill_count);
        }
      }

      return fill_after;
    }

    inline constexpr CharT fill_char() const noexcept { return m_fill_char; }

    inline constexpr Type type() const noexcept { return m_type; }

    inline constexpr int width() const noexcept { return static_cast<int>(m_width); }

    inline constexpr int precision() const noexcept { return static_cast<int>(m_precision); }

    inline constexpr int index() const noexcept { return static_cast<int>(m_index); }

    inline constexpr Align align() const noexcept { return Align(m_flags & Flags::kAlignBitmask); }

    inline constexpr Sign sign() const noexcept { return Sign(m_flags & Flags::kSignBitmask); }

    inline constexpr bool is_empty() const noexcept { return (m_flags & Flags::kEmpty) != 0; }

    inline constexpr bool hash() const noexcept { return (m_flags & Flags::kHash) != 0; }

    inline constexpr bool uppercase() const noexcept { return (m_flags & Flags::kUppercase) != 0; }

    inline constexpr bool type_is_none() const noexcept { return m_type == Type::kNone; }

    inline constexpr bool type_is_char() const noexcept { return m_type == Type::kChar; }

    inline constexpr bool type_is_string() const noexcept { return m_type == Type::kString; }

    inline constexpr bool type_is_pointer() const noexcept { return m_type == Type::kPointer; }

    inline constexpr bool type_is_integer() const noexcept {
      return m_type >= Type::kIntegerDec && m_type <= Type::kIntegerBin;
    }

    inline constexpr bool type_is_float() const noexcept {
      return m_type >= Type::kFloatFixed && m_type <= Type::kFloatGeneral;
    }

    inline constexpr bool type_is_numeric() const noexcept {
      return m_type >= Type::kIntegerDec && m_type <= Type::kFloatGeneral;
    }

    inline constexpr bool type_is_integer_dec() const noexcept { return m_type == Type::kIntegerDec; }

    inline constexpr bool type_is_integer_hex() const noexcept { return m_type == Type::kIntegerHex; }

    inline constexpr bool type_is_integer_oct() const noexcept { return m_type == Type::kIntegerOct; }

    inline constexpr bool type_is_integer_bin() const noexcept { return m_type == Type::kIntegerBin; }

    inline constexpr bool type_is_float_fixed() const noexcept { return m_type == Type::kFloatFixed; }

    inline constexpr bool type_is_float_scientific() const noexcept { return m_type == Type::kFloatScientific; }

    inline constexpr bool type_is_float_general() const noexcept { return m_type == Type::kFloatGeneral; }

    inline constexpr bool type_allow_hash() const noexcept {
      // Alternative format is valid for hexadecimal (including
      // pointers), octal, binary and all floating point types.
      return m_type >= Type::kIntegerHex && m_type <= Type::kFloatGeneral;
    }

    inline constexpr void default_align_left() noexcept {
      if ((m_flags & Flags::kAlignBitmask) == Flags::kAlignNone) {
        m_flags |= Flags::kAlignLeft;
      }
    }

   private:
    // --------------------------------------------------------------------
    // PRIVATE DEFINITIONS
    // --------------------------------------------------------------------

    enum Flags : uint8_t {
      kNone = (0U << 0U),

      kEmpty = (1U << 0U),

      kAlignNone = (0U << 1U),
      kAlignLeft = (1U << 1U),
      kAlignRight = (2U << 1U),
      kAlignCenter = (3U << 1U),
      kAlignNumeric = (4U << 1U),
      kAlignBitmask = (7U << 1U),

      kSignNone = (0U << 4U),
      kSignMinus = (1U << 4U),
      kSignPlus = (2U << 4U),
      kSignSpace = (3U << 4U),
      kSignBitmask = (3U << 4U),

      kHash = (1U << 6U),

      kUppercase = (1U << 7U)
    };

    // --------------------------------------------------------------------
    // PRIVATE MEMBER FUNCTIONS
    // --------------------------------------------------------------------

    /**
     * @brief Returns whether or not there is a negative sign for the number.
     * @param negative
     * @returns 1 or 0 for if there is or is not a negative sign.
     */
    inline constexpr int sign_width(const bool negative) const noexcept {
      return (!negative && sign() <= Sign::kMinus) ? 0 : 1;
    }

    /**
     * @returns The width in characters of the prefix.
     */
    inline constexpr int prefix_width() const noexcept {
      // Alternative format is valid for hexadecimal (including
      // pointers), octal, binary and all floating point types.
      return (!hash() || type_is_float()) ? 0 : type_is_integer_oct() ? 1
                                                                      : 2;
    }

    constexpr void write_sign(iterator &it, const bool negative) const noexcept {
      if (negative) {
        *it++ = '-';
      } else {
        const Sign s = sign();

        if (s != Sign::kNone) {
          if (s == Sign::kPlus) {
            *it++ = '+';
          } else if (s == Sign::kSpace) {
            *it++ = ' ';
          }
        }
      }
    }

    constexpr void write_prefix(iterator &it) const noexcept {
      // Alternative format is valid for hexadecimal (including
      // pointers), octal, binary and all floating point types.
      if (hash() && !type_is_float()) {
        *it++ = '0';

        if (type_is_integer_bin()) {
          *it++ = uppercase() ? 'B' : 'b';
        } else if (type_is_integer_hex() || type_is_pointer()) {
          *it++ = uppercase() ? 'X' : 'x';
        }
      }
    }

    // --------------------------------------------------------------------
    // PRIVATE STATIC FUNCTIONS
    // --------------------------------------------------------------------

    /**
     * @brief Parses the input as a positive integer that fits into a 'uint8_t' type.
     * @note This function assumes that the first character is a digit and terminates parsing at the presence of the first non-digit character or when value overflows.
     * @param it The iterator that is the start of the number string | eg. it = 1 when number string = 142.
     * @param max_value The max value the inputted string can convert to before it is an error.
     * @returns The string's value as an 8 bit number.
     */
    static constexpr uint8_t parse_positive_small_int(const_iterator &it, const int max_value) {
      assert(max_value < 256);

      int value = 0;  // The running converted number
      do {            // TODO: Stop after 3 parsed characters as extra measure
        value = (value * 10) + static_cast<int>(*it++ - '0');
        USF_ENFORCE(value <= max_value, std::runtime_error);  // Check for overflow
      } while (*it >= '0' && *it <= '9');                     // Keep parsing the string until a non-numeric value is reached

      return static_cast<uint8_t>(value);
    }

    /**
     * @brief Maps a character to an alignment type
     * @param ch The character that could be an alignment type
     * @returns The flag which represents the alignment of the argument, or a none flag if the character is not an alignment signifier
     */
    static constexpr uint8_t parse_align_flag(const CharT ch) noexcept {
      switch (ch) {
        case '<':
          return Flags::kAlignLeft;
          break;
        case '>':
          return Flags::kAlignRight;
          break;
        case '^':
          return Flags::kAlignCenter;
          break;
        case '=':
          return Flags::kAlignNumeric;
          break;
        default:
          return Flags::kNone;
          break;
      }
    }

    // --------------------------------------------------------------------
    // PRIVATE MEMBER VARIABLES
    // --------------------------------------------------------------------

    CharT m_fill_char = ' ';
    Type m_type = Type::kNone;
    uint8_t m_flags = Flags::kEmpty;
    uint8_t m_width = 0;
    int8_t m_precision = -1;
    int8_t m_index = -1;
  };

}  // namespace usf::internal

#endif  // USF_ARG_FORMAT_HPP
