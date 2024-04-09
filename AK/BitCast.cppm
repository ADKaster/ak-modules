/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/Platform.h>

export module AK:BitCast;

namespace AK {

export template<typename T, typename U>
[[nodiscard]] constexpr inline T bit_cast(U const& a)
{
#if (__has_builtin(__builtin_bit_cast))
    return __builtin_bit_cast(T, a);
#else
    static_assert(sizeof(T) == sizeof(U));

    T result;
    __builtin_memcpy(&result, &a, sizeof(T));
    return result;
#endif
}

}

#if USING_AK_GLOBALLY
export using AK::bit_cast;
#endif
