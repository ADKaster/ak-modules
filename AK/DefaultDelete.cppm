/*
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:DefaultDelete;

namespace AK {

export template<class T>
struct DefaultDelete {
    constexpr DefaultDelete() = default;

    constexpr void operator()(T* t)
    {
        delete t;
    }
};

export template<class T>
struct DefaultDelete<T[]> {
    constexpr DefaultDelete() = default;

    constexpr void operator()(T* t)
    {
        delete[] t;
    }
};

}

#ifdef USING_AK_GLOBALLY
export using AK::DefaultDelete;
#endif
