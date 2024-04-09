/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:AnyOf;
import :Concepts;
import :Find;

namespace AK {

export template<typename TEndIterator, IteratorPairWith<TEndIterator> TIterator>
[[nodiscard]] constexpr bool any_of(
    TIterator const& begin,
    TEndIterator const& end,
    auto const& predicate)
{
    return find_if(begin, end, predicate) != end;
}

export template<IterableContainer Container>
[[nodiscard]] constexpr bool any_of(Container&& container, auto const& predicate)
{
    return any_of(container.begin(), container.end(), predicate);
}

}

#if USING_AK_GLOBALLY
export using AK::any_of;
#endif
