/*
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:SinglyLinkedListSizePolicy;
import :Types;

namespace AK {

export struct DefaultSizeCalculationPolicy {
    constexpr void increase_size(auto const&) { }

    constexpr void decrease_size(auto const&) { }

    constexpr void reset() { }

    constexpr size_t size(auto const* head) const
    {
        size_t size = 0;
        for (auto* node = head; node; node = node->next)
            ++size;
        return size;
    }
};

export struct CountingSizeCalculationPolicy {
    constexpr void increase_size(auto const&) { ++m_size; }

    constexpr void decrease_size(auto const&) { --m_size; }

    constexpr void reset() { m_size = 0; }

    constexpr size_t size(auto const*) const { return m_size; }

private:
    size_t m_size { 0 };
};

}

#ifdef USING_AK_GLOBALLY
export using AK::CountingSizeCalculationPolicy;
export using AK::DefaultSizeCalculationPolicy;
#endif
