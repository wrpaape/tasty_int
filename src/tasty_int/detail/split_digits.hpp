#ifndef TASTY_INT_TASTY_INT_DETAIL_SPLIT_DIGITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SPLIT_DIGITS_HPP

#include <cassert>

#include <array>
#include <vector>

#include "tasty_int/detail/trailing_zero.hpp"


namespace tasty_int {
namespace detail {
namespace split_digits_detail {

constexpr
bool is_final_split(std::size_t split_index,
                    std::size_t count_pieces)
{
    return (split_index + 1) == count_pieces;
}

template<std::size_t SPLIT_INDEX, std::size_t COUNT_PIECES>
void
split(const std::vector<digit_type>                     &digits,
      std::vector<digit_type>::size_type                 split_size,
      std::array<std::vector<digit_type>, COUNT_PIECES> &result)
{
    auto split_begin = digits.begin() + (SPLIT_INDEX * split_size);

    if constexpr (is_final_split(SPLIT_INDEX, COUNT_PIECES)) {
        result[SPLIT_INDEX] = std::vector<digit_type>(split_begin,
                                                      digits.end());
    } else {
        auto split_end = split_begin + split_size;
        auto piece     = std::vector<digit_type>(split_begin, split_end);
        trim_trailing_zeros(piece);

        result[SPLIT_INDEX] = std::move(piece);

        split<SPLIT_INDEX + 1>(digits, split_size, result);
    }
}

} // namespace split_digits_detail


/**
 * @brief Splits @p digits into @p COUNT_PIECES pieces with sizes of at least
 *     @p split_size.
 *
 * @details The first `COUNT_PIECES - 1` pieces are allocated @p split_size
 *     digits a piece, and the final piece is allocated the remainder.  Leading
 *     zeros are stripped from the resulting pieces.
 *
 * @tparam COUNT_PIECES the number of pieces
 * @param[in] digits     a little-endian sequence of digits
 * @param[in] split_size the minimum split interval between consecutive pieces
 *
 *
 * @pre `COUNT_PIECES > 0`
 * @pre `digits.size() > (split_size * (COUNT_PIECES - 1))`
 */
template<std::size_t COUNT_PIECES>
std::array<std::vector<digit_type>, COUNT_PIECES>
split_digits(const std::vector<digit_type>      &digits,
             std::vector<digit_type>::size_type  split_size)
{
    static_assert(COUNT_PIECES > 0);

    assert(split_size > 0);
    assert(digits.size() > (split_size * (COUNT_PIECES - 1)));

    std::array<std::vector<digit_type>, COUNT_PIECES> result;

    split_digits_detail::split<0>(digits,
                                  split_size,
                                  result);

    return result;
}

} // namespace tasty_int
} // namespace detail

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SPLIT_DIGITS_HPP
