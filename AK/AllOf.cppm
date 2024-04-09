/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:AllOf;
import :Concepts;
import :Find;

namespace AK {

export template<typename TEndIterator, IteratorPairWith<TEndIterator> TIterator>
[[nodiscard]] constexpr bool all_of(
    TIterator const& begin,
    TEndIterator const& end,
    auto const& predicate)
{
    constexpr auto negated_predicate = [](auto const& pred) {
        return [&](auto const& elem) { return !pred(elem); };
    };
    return !(find_if(begin, end, negated_predicate(predicate)) != end);
}

export template<IterableContainer Container>
[[nodiscard]] constexpr bool all_of(Container&& container, auto const& predicate)
{
    return all_of(container.begin(), container.end(), predicate);
}

}

#if USING_AK_GLOBALLY
export using AK::all_of;
#endif
