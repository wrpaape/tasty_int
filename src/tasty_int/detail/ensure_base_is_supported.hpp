#ifndef TASTY_INT_TASTY_INT_DETAIL_ENSURE_BASE_IS_SUPPORTED_HPP
#define TASTY_INT_TASTY_INT_DETAIL_ENSURE_BASE_IS_SUPPORTED_HPP

namespace tasty_int {
namespace detail {

/**
 * @brief checks that @p base is a supported numeric base/radix
 *
 * @throw std::invalid_argument if @p base is unsupported
 */
void
ensure_base_is_supported(unsigned int base);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_ENSURE_BASE_IS_SUPPORTED_HPP
