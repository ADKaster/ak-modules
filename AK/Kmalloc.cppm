/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Daniel Bertalan <dani@danielbertalan.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:Kmalloc;
import :Checked;
import :Types;

#if !defined(AK_OS_SERENITY) && !defined(AK_OS_MACOS)
extern "C" {
export inline size_t malloc_good_size(size_t size) { return size; }
}
#endif

#if !defined(KERNEL)
export inline void kfree_sized(void* ptr, size_t)
{
  free(ptr);
}
#endif

export using std::nothrow;

export inline void* kmalloc_array(AK::Checked<size_t> a, AK::Checked<size_t> b)
{
    auto size = a * b;
    VERIFY(!size.has_overflow());
    return kmalloc(size.value());
}

export inline void* kmalloc_array(AK::Checked<size_t> a, AK::Checked<size_t> b, AK::Checked<size_t> c)
{
    auto size = a * b * c;
    VERIFY(!size.has_overflow());
    return kmalloc(size.value());
}
