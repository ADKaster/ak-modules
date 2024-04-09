/*
* Copyright (c) 2024, Andrew Kaster <akaster@serenityos.org>
*
* SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#    define outln_if(flag, fmt, ...)       \
        do {                               \
            if constexpr (flag)            \
                outln(fmt, ##__VA_ARGS__); \
        } while (0)

#    define warnln_if(flag, fmt, ...)       \
        do {                                \
            if constexpr (flag)             \
                warnln(fmt, ##__VA_ARGS__); \
        } while (0)

#    define dbgln_if(flag, fmt, ...)       \
        do {                               \
            if constexpr (flag)            \
                dbgln(fmt, ##__VA_ARGS__); \
        } while (0)
