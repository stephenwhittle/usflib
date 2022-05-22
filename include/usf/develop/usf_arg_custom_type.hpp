// ----------------------------------------------------------------------------
// @file    usf_arg_custom_type.hpp
// @brief   User-defined custom type class (using the delegate idiom).
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARG_CUSTOM_TYPE_HPP
#define USF_ARG_CUSTOM_TYPE_HPP

namespace usf {
namespace internal {

  template <typename CharT>
  class ArgCustomType {
   public:
    // --------------------------------------------------------------------
    // PUBLIC MEMBER FUNCTIONS
    // --------------------------------------------------------------------

    constexpr ArgCustomType() = delete;

    template <typename T, std::span<CharT> (*func)(std::span<CharT>, const T&)>
    static constexpr ArgCustomType create(const T* obj) {
      return ArgCustomType(invoke_func<T, func>, obj);
    }

    constexpr std::span<CharT> operator()(std::span<CharT> dst) const {
      return m_function(dst, m_obj);
    }

   private:
    // --------------------------------------------------------------------
    // PRIVATE TYPE ALIASES
    // --------------------------------------------------------------------

    using FunctionType = std::span<CharT> (*)(std::span<CharT>, const void*);

    // --------------------------------------------------------------------
    // PRIVATE MEMBER FUNCTIONS
    // --------------------------------------------------------------------

    constexpr ArgCustomType(const FunctionType func, const void* obj)
        : m_function{func}, m_obj{obj} {}

    template <typename T, std::span<CharT> (*func)(std::span<CharT>, const T&)>
    static constexpr std::span<CharT> invoke_func(std::span<CharT> dst, const void* obj) {
      return func(dst, *static_cast<const T*>(obj));
    }

    // --------------------------------------------------------------------
    // PRIVATE VARIABLES
    // --------------------------------------------------------------------

    const FunctionType m_function{nullptr};
    const void* m_obj{nullptr};
  };

}
}  // namespace usf::internal

#endif  // USF_ARG_CUSTOM_TYPE_HPP
