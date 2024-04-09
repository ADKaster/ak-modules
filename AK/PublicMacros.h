/*
* Copyright (c) 2023, Andrew Kaster <akaster@serenityos.org>
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

#include <AK/Platform.h>

#include <AK/Assertions.h>
#include <AK/Diagnostics.h>
#include <AK/EnumBits.h>
#include <AK/FormatMacros.h>
#include <AK/Noncopyable.h>
#include <AK/Try.h>

#if !defined(AK_OS_SERENITY)
#    include <stddef.h>
#    include <stdint.h>
#    include <sys/types.h>
#endif

#if defined(AK_OS_MACOS)
#    include <malloc/malloc.h>
#    include <libkern/OSByteOrder.h>
#    include <machine/endian.h>

#    define htobe16(x) OSSwapHostToBigInt16(x)
#    define htole16(x) OSSwapHostToLittleInt16(x)
#    define be16toh(x) OSSwapBigToHostInt16(x)
#    define le16toh(x) OSSwapLittleToHostInt16(x)

#    define htobe32(x) OSSwapHostToBigInt32(x)
#    define htole32(x) OSSwapHostToLittleInt32(x)
#    define be32toh(x) OSSwapBigToHostInt32(x)
#    define le32toh(x) OSSwapLittleToHostInt32(x)

#    define htobe64(x) OSSwapHostToBigInt64(x)
#    define htole64(x) OSSwapHostToLittleInt64(x)
#    define be64toh(x) OSSwapBigToHostInt64(x)
#    define le64toh(x) OSSwapLittleToHostInt64(x)

#    define __BIG_ENDIAN BIG_ENDIAN
#    define __LITTLE_ENDIAN LITTLE_ENDIAN
#    define __BYTE_ORDER BYTE_ORDER
#endif

#if defined(KERNEL)
#    include <Kernel/Heap/kmalloc.h>
#else
#    include <new>
#    include <stdlib.h>
#    include <string.h>
#    include <stdio.h>

#    define kcalloc calloc
#    define kmalloc malloc
#    define kmalloc_good_size malloc_good_size
#endif

#if defined(AK_OS_SERENITY) && defined(KERNEL)
#    include <errno_codes.h>
#else
#    include <errno.h>
#endif

#define OFFSET_OF(class, member) __builtin_offsetof(class, member)

#if !USING_AK_GLOBALLY || defined(AK_DONT_REPLACE_STD)
#    define AK_REPLACED_STD_NAMESPACE AK::replaced_std
#else
#    define AK_REPLACED_STD_NAMESPACE std
#endif

#if __LDBL_MANT_DIG__ == 64 && __LDBL_MAX_EXP__ == 16384
#    define AK_HAS_FLOAT_80 1
#elif __LDBL_MANT_DIG__ == 113 && __LDBL_MAX_EXP__ == 16384
#    define AK_HAS_FLOAT_128 1
#endif
