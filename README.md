# μSF - Micro String Format
[![Standard](https://img.shields.io/badge/C%2B%2B-20-C%2B%2B20?logo=c%2B%2B&color=00599C&style=flat)](https://isocpp.org/std/the-standard)
[![Test Status](https://img.shields.io/github/workflow/status/TSprech/Micro-String-Format/CMake?label=Test&logo=githubactions&logoColor=white)](https://github.com/TSprech/Micro-String-Format/actions)
[![Coverage](https://img.shields.io/coveralls/github/TSprech/Micro-String-Format?label=Coverage&logo=coveralls&logoColor=white)](https://coveralls.io/github/TSprech/Micro-String-Format)
[![Download](https://img.shields.io/badge/Download%20%20-latest-blue.svg)](https://raw.githubusercontent.com/TSprech/Micro-String-Format/main/include/usf/usf.hpp)
[![License](https://img.shields.io/github/license/TSprech/Micro-String-Format?label=License&color=A41E34)](https://opensource.org/licenses/MIT)

μSF is a lean C++ string format library (mainly) for embedded platforms.
Its main purpose is to be a small, safe and fast alternative to (s)(n)printf functions adding some additional features.
These additional features include localization and translation lookup support, providing an alternative to STL locale and GNU gettext.
This library is still in development, however has a majority of functionality ready for use.

## Motivation (For This Fork)
I wanted std::format style formatting for embedded projects. I found hparracho's [usflib](https://github.com/hparracho/usflib) and it seemed like the perfect jumping off point.
 I have noticed a significant lack of open source, embedded oriented, localization libraries. And when such an opportunity presented itself,
I figured someone should fill that gap, so here we are.

I think it is clear why an alternative to the antiquated (s)(n)printf is wanted, why the heavy std::iostream library isn't space efficient for embedded, and why the behemoth std::locale is not ideal.
 However, iostream and locale are only half the localization battle. An embedded equivalent to something like GNU gettext is also needed for translating strings.

## Features
- Safe alternative to (s)(n)printf and IOStream functions
- Doesn't allocate any dynamic memory
- Ease of use: single header file library [usf.hpp](https://raw.githubusercontent.com/TSprech/Micro-String-Format/main/include/usf/usf.hpp) without any external dependencies
- Small code size: both in terms of source code and produced binary size
- Reliable: it has an extensive set of [unit tests](https://raw.githubusercontent.com/TSprech/Micro-String-Format/main/test) (*work in progress*)
- Support for positional arguments
- Support for user-defined custom types
- Portable and consistent across platforms and compilers
- Clean warning-free codebase even with aggressive warning levels
- Support for  C\+\+20 standard, in the future compatability with C\+\+11/14/17 may be added back once localization support is completed

#### Roadmap - upcoming features
- Number localization support
- Complete unit tests
- Dynamic width and precision support
- Better floating point conversion routine. Looking at the possibility of adapting [ryu](https://github.com/ulfjack/ryu)'s algorithm

## Benchmarks
(*wip*)

## Usage
To get started with **usflib** all you need to do is download the [**latest version**](https://raw.githubusercontent.com/hparracho/usflib/master/include/usf/usf.hpp) which is just a single header file and add it to your source files (or add this repository as a git submodule).

Assuming you can use the single header file directly: ```#include "usf.hpp"``` - place it either in the same folder of your source files or add its location to the include paths of your build system. 

#### A minimal example
```c++
#include "usf.hpp"
/*...*/
char str[64]{};
usf::format_to(str, 64, "Hello, {}!", "world");      // str == "Hello, world!"
usf::format_to(str, 64, "dec:{0} hex:{0:x}", 16);    // str == "dec:16 hex:10"
usf::format_to(str, 64, "{0}{1}{0}", "abra", "cad"); // str == "abracadabra"
```

## API Reference
All functions and types provided by the μSF library reside in namespace ```usf``` and macros have prefix ```USF_```.
The library API provides a few simple format functions and a minimal string view / string span like classes that offer an alternative to the standard ones.

The string view / string span types are template classes that accepts the type of character via a template parameter, having (for now) a *char* type specialization.
```c++
template <typename CharT>
class BasicStringView{ /*...*/ };
using StringView = BasicStringView<char>;

template <typename CharT>
class BasicStringSpan{ /*...*/ };
using StringSpan = BasicStringSpan<char>;
```
Similarly, the format functions are template functions, allowing the use of different character types. Two sets are defined, a ```basic_format_to``` being the template version and another called ```format_to``` being the *char* type specialization.

The following format functions use the same [format string syntax](#syntax) of {fmt}, which is itself similar to that of Pythons's [str.format](https://docs.python.org/3.8/library/string.html) (although not every option is implemented).

The output format is specified in the *str_fmt* string/string view. It can contain literal text and replacement fields surrounded by braces ```{}```. The fields are replaced with formatted arguments in the resulting string.

The objects to be formated are represented by the *args* argument list.

1. Formats the *args* arguments, writes the result to the iterator (pointer) *str* and returns an iterator (pointer) past the end of the output range.
The function fails if the resulting output string size is greater than *str_count* size.
```c++
template <typename CharT, typename... Args>
CharT* usf::basic_format_to(CharT* str, const std::ptrdiff_t str_count,
                            usf::BasicStringView<CharT> str_fmt, Args&&... args);

template <typename... Args>
char* usf::format_to(char* str, const std::ptrdiff_t str_count,
                     usf::StringView str_fmt, Args&&... args);
```
2. Formats the *args* arguments, writes the result to the string holded by the string span *str* (don't change the span range) and returns a new string span with the range adjusted to the output string size.
The function fails if the resulting output string size is greater than *str*'s span range.
```c++
template <typename CharT, typename... Args>
usf::BasicStringSpan<CharT> usf::basic_format_to(usf::BasicStringSpan<CharT> str,
                                                 usf::BasicStringView<CharT> str_fmt, Args&&... args);

template <typename... Args>
usf::StringSpan usf::format_to(usf::StringSpan str, usf::StringView str_fmt, Args&&... args);
```
## Syntax
(*wip*)

## License
(*wip*)

## Acknowledgments
hparracho's original library: [usflib](https://github.com/hparracho/usflib)

mapbox's constexpr map library: [eternal](https://github.com/mapbox/eternal)
