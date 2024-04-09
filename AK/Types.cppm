/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:Types;
export import :StdLibExtras;

export using u64 = __UINT64_TYPE__;
export using u32 = __UINT32_TYPE__;
export using u16 = __UINT16_TYPE__;
export using u8 = __UINT8_TYPE__;
export using i64 = __INT64_TYPE__;
export using i32 = __INT32_TYPE__;
export using i16 = __INT16_TYPE__;
export using i8 = __INT8_TYPE__;

#ifndef KERNEL
export using f32 = float;
static_assert(__FLT_MANT_DIG__ == 24 && __FLT_MAX_EXP__ == 128);

export using f64 = double;
static_assert(__DBL_MANT_DIG__ == 53 && __DBL_MAX_EXP__ == 1024);

#    if defined(AK_HAS_FLOAT_80)
export using f80 = long double;
static_assert(__LDBL_MANT_DIG__ == 64 && __LDBL_MAX_EXP__ == 16384);
#    elif defined(AK_HAS_FLOAT_128)
export using f128 = long double;
static_assert(__LDBL_MANT_DIG__ == 113 && __LDBL_MAX_EXP__ == 16384);
#    endif
#endif

#ifdef AK_OS_SERENITY
export using size_t = __SIZE_TYPE__;
export using ssize_t = AK::Detail::MakeSigned<size_t>;

export using ptrdiff_t = __PTRDIFF_TYPE__;

export using intptr_t = __INTPTR_TYPE__;
export using uintptr_t = __UINTPTR_TYPE__;

export using uint8_t = u8;
export using uint16_t = u16;
export using uint32_t = u32;
export using uint64_t = u64;

export using int8_t = i8;
export using int16_t = i16;
export using int32_t = i32;
export using int64_t = i64;

export using pid_t = int;

#elif defined(AK_OS_WINDOWS)
export using ssize_t = AK::Detail::MakeSigned<size_t>;
export using mode_t = unsigned short;
#endif

export using FlatPtr = AK::Detail::Conditional<sizeof(void*) == 8, u64, u32>;

export constexpr u64 KiB = 1024;
export constexpr u64 MiB = KiB * KiB;
export constexpr u64 GiB = KiB * KiB * KiB;
export constexpr u64 TiB = KiB * KiB * KiB * KiB;
export constexpr u64 PiB = KiB * KiB * KiB * KiB * KiB;
export constexpr u64 EiB = KiB * KiB * KiB * KiB * KiB * KiB;

namespace AK_REPLACED_STD_NAMESPACE { // NOLINT(cert-dcl58-cpp) nullptr_t must be in ::std:: for some analysis tools
using nullptr_t = decltype(nullptr);
}

namespace AK {

export using nullptr_t = AK_REPLACED_STD_NAMESPACE::nullptr_t;
export using size_t = ::size_t;

export constexpr FlatPtr explode_byte(u8 b)
{
    FlatPtr value = b;
    if constexpr (sizeof(FlatPtr) == 4)
        return value << 24 | value << 16 | value << 8 | value;
    else if (sizeof(FlatPtr) == 8)
        return value << 56 | value << 48 | value << 40 | value << 32 | value << 24 | value << 16 | value << 8 | value;
}

static_assert(explode_byte(0xff) == static_cast<FlatPtr>(0xffffffffffffffffull));
static_assert(explode_byte(0x80) == static_cast<FlatPtr>(0x8080808080808080ull));
static_assert(explode_byte(0x7f) == static_cast<FlatPtr>(0x7f7f7f7f7f7f7f7full));
static_assert(explode_byte(0) == 0);

export constexpr size_t align_up_to(const size_t value, const size_t alignment)
{
    return (value + (alignment - 1)) & ~(alignment - 1);
}

export constexpr size_t align_down_to(const size_t value, const size_t alignment)
{
    return value & ~(alignment - 1);
}

export enum class [[nodiscard]] TriState : u8 {
    False,
    True,
    Unknown
};

export enum MemoryOrder {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
};

}

#if USING_AK_GLOBALLY
export using AK::align_down_to;
export using AK::align_up_to;
export using AK::explode_byte;
export using AK::MemoryOrder;
export using AK::nullptr_t;
export using AK::TriState;
#endif
