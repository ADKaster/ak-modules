/*
 * Copyright (c) 2021, Max Wipfli <mail@maxwipfli.ch>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:CharacterTypes;
import :Array;
import :Types;

// NOTE: For a quick reference for most of this, see https://www.cplusplus.com/reference/cctype/ and https://infra.spec.whatwg.org/#code-points.
// NOTE: To avoid ambiguity when including this header, all methods contains names should contain "ascii" or "unicode".

namespace AK {

export constexpr bool is_ascii(u32 code_point)
{
    return code_point < 0x80;
}

export constexpr bool is_ascii_digit(u32 code_point)
{
    return code_point >= '0' && code_point <= '9';
}

export constexpr bool is_ascii_upper_alpha(u32 code_point)
{
    return (code_point >= 'A' && code_point <= 'Z');
}

export constexpr bool is_ascii_lower_alpha(u32 code_point)
{
    return (code_point >= 'a' && code_point <= 'z');
}

export constexpr bool is_ascii_alpha(u32 code_point)
{
    return is_ascii_lower_alpha(code_point) || is_ascii_upper_alpha(code_point);
}

export constexpr bool is_ascii_alphanumeric(u32 code_point)
{
    return is_ascii_alpha(code_point) || is_ascii_digit(code_point);
}

export constexpr bool is_ascii_binary_digit(u32 code_point)
{
    return code_point == '0' || code_point == '1';
}

export constexpr bool is_ascii_octal_digit(u32 code_point)
{
    return code_point >= '0' && code_point <= '7';
}

export constexpr bool is_ascii_hex_digit(u32 code_point)
{
    return is_ascii_digit(code_point) || (code_point >= 'A' && code_point <= 'F') || (code_point >= 'a' && code_point <= 'f');
}

export constexpr bool is_ascii_blank(u32 code_point)
{
    return code_point == '\t' || code_point == ' ';
}

export constexpr bool is_ascii_space(u32 code_point)
{
    return code_point == ' ' || code_point == '\t' || code_point == '\n' || code_point == '\v' || code_point == '\f' || code_point == '\r';
}

export constexpr bool is_ascii_punctuation(u32 code_point)
{
    return (code_point >= 0x21 && code_point <= 0x2F) || (code_point >= 0x3A && code_point <= 0x40) || (code_point >= 0x5B && code_point <= 0x60) || (code_point >= 0x7B && code_point <= 0x7E);
}

export constexpr bool is_ascii_graphical(u32 code_point)
{
    return code_point >= 0x21 && code_point <= 0x7E;
}

export constexpr bool is_ascii_printable(u32 code_point)
{
    return code_point >= 0x20 && code_point <= 0x7E;
}

export constexpr bool is_ascii_c0_control(u32 code_point)
{
    return code_point < 0x20;
}

export constexpr bool is_ascii_control(u32 code_point)
{
    return is_ascii_c0_control(code_point) || code_point == 0x7F;
}

export constexpr bool is_unicode(u32 code_point)
{
    return code_point <= 0x10FFFF;
}

export constexpr bool is_unicode_control(u32 code_point)
{
    return is_ascii_c0_control(code_point) || (code_point >= 0x7E && code_point <= 0x9F);
}

export constexpr bool is_unicode_surrogate(u32 code_point)
{
    return code_point >= 0xD800 && code_point <= 0xDFFF;
}

export constexpr bool is_unicode_scalar_value(u32 code_point)
{
    return is_unicode(code_point) && !is_unicode_surrogate(code_point);
}

export constexpr bool is_unicode_noncharacter(u32 code_point)
{
    return is_unicode(code_point) && ((code_point >= 0xFDD0 && code_point <= 0xFDEF) || ((code_point & 0xFFFE) == 0xFFFE) || ((code_point & 0xFFFF) == 0xFFFF));
}

export constexpr u32 to_ascii_lowercase(u32 code_point)
{
    if (is_ascii_upper_alpha(code_point))
        return code_point + 0x20;
    return code_point;
}

export constexpr u32 to_ascii_uppercase(u32 code_point)
{
    if (is_ascii_lower_alpha(code_point))
        return code_point - 0x20;
    return code_point;
}

export constexpr u32 parse_ascii_digit(u32 code_point)
{
    if (is_ascii_digit(code_point))
        return code_point - '0';
    VERIFY_NOT_REACHED();
}

export constexpr u32 parse_ascii_hex_digit(u32 code_point)
{
    if (is_ascii_digit(code_point))
        return parse_ascii_digit(code_point);
    if (code_point >= 'A' && code_point <= 'F')
        return code_point - 'A' + 10;
    if (code_point >= 'a' && code_point <= 'f')
        return code_point - 'a' + 10;
    VERIFY_NOT_REACHED();
}

export constexpr u32 parse_ascii_base36_digit(u32 code_point)
{
    if (is_ascii_digit(code_point))
        return parse_ascii_digit(code_point);
    if (code_point >= 'A' && code_point <= 'Z')
        return code_point - 'A' + 10;
    if (code_point >= 'a' && code_point <= 'z')
        return code_point - 'a' + 10;
    VERIFY_NOT_REACHED();
}

export constexpr u32 to_ascii_base36_digit(u32 digit)
{
    constexpr Array<char, 36> base36_map = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    VERIFY(digit < base36_map.size());
    return base36_map[digit];
}

}

#if USING_AK_GLOBALLY
export using AK::is_ascii;
export using AK::is_ascii_alpha;
export using AK::is_ascii_alphanumeric;
export using AK::is_ascii_binary_digit;
export using AK::is_ascii_blank;
export using AK::is_ascii_c0_control;
export using AK::is_ascii_control;
export using AK::is_ascii_digit;
export using AK::is_ascii_graphical;
export using AK::is_ascii_hex_digit;
export using AK::is_ascii_lower_alpha;
export using AK::is_ascii_octal_digit;
export using AK::is_ascii_printable;
export using AK::is_ascii_punctuation;
export using AK::is_ascii_space;
export using AK::is_ascii_upper_alpha;
export using AK::is_unicode;
export using AK::is_unicode_control;
export using AK::is_unicode_noncharacter;
export using AK::is_unicode_scalar_value;
export using AK::is_unicode_surrogate;
export using AK::parse_ascii_base36_digit;
export using AK::parse_ascii_digit;
export using AK::parse_ascii_hex_digit;
export using AK::to_ascii_base36_digit;
export using AK::to_ascii_lowercase;
export using AK::to_ascii_uppercase;
#endif
