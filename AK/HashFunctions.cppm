/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

export module AK:HashFunctions;
import :Types;

export constexpr unsigned int_hash(u32 key)
{
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}

export constexpr unsigned pair_int_hash(u32 key1, u32 key2)
{
    return int_hash((int_hash(key1) * 209) ^ (int_hash(key2 * 413)));
}

export constexpr unsigned u64_hash(u64 key)
{
    u32 first = key & 0xFFFFFFFF;
    u32 last = key >> 32;
    return pair_int_hash(first, last);
}

export constexpr unsigned ptr_hash(FlatPtr ptr)
{
    if constexpr (sizeof(ptr) == 8)
        return u64_hash(ptr);
    else
        return int_hash(ptr);
}

export inline unsigned ptr_hash(void const* ptr)
{
    return ptr_hash(FlatPtr(ptr));
}
