/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

export module AK:Find;
import :Concepts;
import :Traits;
import :Types;

namespace AK {

export template<typename TEndIterator, IteratorPairWith<TEndIterator> TIterator, typename TUnaryPredicate>
[[nodiscard]] constexpr TIterator find_if(TIterator first, TEndIterator last, TUnaryPredicate&& pred)
{
    for (; first != last; ++first) {
        if (pred(*first)) {
            return first;
        }
    }
    return last;
}

export template<typename TEndIterator, IteratorPairWith<TEndIterator> TIterator, typename V>
[[nodiscard]] constexpr TIterator find(TIterator first, TEndIterator last, V const& value)
{
    return find_if(first, last, [&]<typename T>(T const& entry) { return Traits<T>::equals(entry, value); });
}

export template<typename TEndIterator, IteratorPairWith<TEndIterator> TIterator, typename V>
[[nodiscard]] constexpr size_t find_index(TIterator first, TEndIterator last, V const& value)
requires(requires(TIterator it) { it.index(); })
{
    return find_if(first, last, [&]<typename T>(T const& entry) { return Traits<T>::equals(entry, value); }).index();
}

}
