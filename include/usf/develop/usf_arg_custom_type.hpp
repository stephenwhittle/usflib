// ----------------------------------------------------------------------------
// @file    usf_arg_custom_type.hpp
// @brief   User-defined custom type class (using the delegate idiom).
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARG_CUSTOM_TYPE_HPP
#define USF_ARG_CUSTOM_TYPE_HPP

#include <span>
#include <string_view>

namespace usf
{
namespace internal
{

template<typename CharT>
class ArgCustomType
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        USF_CPP14_CONSTEXPR ArgCustomType() = delete;

        template<typename T, std::span<CharT>(*func)(std::basic_string_view<CharT>, const T&)>
        static USF_CPP14_CONSTEXPR ArgCustomType create(const T* obj)
        {
            return ArgCustomType(invoke_func<T, func>, obj);
        }

        USF_CPP14_CONSTEXPR std::span<CharT> operator()(std::span<CharT> dst) const
        {
            return m_function(dst, m_obj);
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE TYPE ALIASES
        // --------------------------------------------------------------------

        using FunctionType = std::span<CharT>(*)(std::span<CharT>, const void*);

        // --------------------------------------------------------------------
        // PRIVATE MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        USF_CPP14_CONSTEXPR ArgCustomType(const FunctionType func, const void* obj)
            : m_function{func}, m_obj{obj} {}

        template<typename T, std::span<CharT>(*func)(std::span<CharT>, const T&)>
        static USF_CPP14_CONSTEXPR std::span<CharT> invoke_func(std::span<CharT> dst, const void* obj)
        {
            return func(dst, *static_cast<const T*>(obj));
        }

        // --------------------------------------------------------------------
        // PRIVATE VARIABLES
        // --------------------------------------------------------------------

        const FunctionType m_function{nullptr};
        const void*        m_obj     {nullptr};
};

} // namespace internal
} // namespace usf

#endif // USF_ARG_CUSTOM_TYPE_HPP
