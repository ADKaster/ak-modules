/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2020, Fei Wu <f.eiwu@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:StringUtils;
import :Concepts;
import :Forward;
import :Types;

namespace AK {

namespace Detail {
export template<Concepts::AnyString T, Concepts::AnyString U>
inline constexpr bool IsHashCompatible<T, U> = true;
}

export enum class CaseSensitivity {
    CaseInsensitive,
    CaseSensitive,
};

export enum class ReplaceMode {
    All,
    FirstOnly,
};

export enum class TrimMode {
    Left,
    Right,
    Both
};

export enum class TrimWhitespace {
    Yes,
    No,
};

export enum class SplitBehavior : unsigned {
    // Neither keep empty substrings nor keep the trailing separator.
    // This is the default behavior if unspecified.
    Nothing = 0,

    // If two separators follow each other without any characters
    // in between, keep a "" in the resulting vector. (or only the
    // separator if KeepTrailingSeparator is used)
    KeepEmpty = 1,

    // Do not strip off the separator at the end of the string.
    KeepTrailingSeparator = 2,
};
AK_ENUM_BITWISE_OPERATORS(SplitBehavior);

export enum class TrailingCodePointTransformation : u8 {
    // Default behaviour; Puts the first typographic letter unit of each word, if lowercase, in titlecase; the other characters in lowercase.
    Lowercase,
    // Puts the first typographic letter unit of each word, if lowercase, in titlecase; other characters are unaffected. (https://drafts.csswg.org/css-text/#valdef-text-transform-capitalize)
    PreserveExisting,
};

export struct MaskSpan {
    size_t start;
    size_t length;

    bool operator==(MaskSpan const& other) const
    {
        return start == other.start && length == other.length;
    }
};

namespace StringUtils {

export bool matches(StringView str, StringView mask, CaseSensitivity = CaseSensitivity::CaseInsensitive, Vector<MaskSpan>* match_spans = nullptr);
export template<typename T = int>
Optional<T> convert_to_int(StringView, TrimWhitespace = TrimWhitespace::Yes);
export template<typename T = unsigned>
Optional<T> convert_to_uint(StringView, TrimWhitespace = TrimWhitespace::Yes);
export template<typename T = unsigned>
Optional<T> convert_to_uint_from_hex(StringView, TrimWhitespace = TrimWhitespace::Yes);
export template<typename T = unsigned>
Optional<T> convert_to_uint_from_octal(StringView, TrimWhitespace = TrimWhitespace::Yes);
#ifndef KERNEL
export template<typename T>
Optional<T> convert_to_floating_point(StringView, TrimWhitespace = TrimWhitespace::Yes);
#endif
export bool equals_ignoring_ascii_case(StringView, StringView);
export bool ends_with(StringView a, StringView b, CaseSensitivity);
export bool starts_with(StringView, StringView, CaseSensitivity);
export bool contains(StringView, StringView, CaseSensitivity);
export bool is_whitespace(StringView);
export StringView trim(StringView string, StringView characters, TrimMode mode);
export StringView trim_whitespace(StringView string, TrimMode mode);

export Optional<size_t> find(StringView haystack, char needle, size_t start = 0);
export Optional<size_t> find(StringView haystack, StringView needle, size_t start = 0);
export Optional<size_t> find_last(StringView haystack, char needle);
export Optional<size_t> find_last(StringView haystack, StringView needle);
export Optional<size_t> find_last_not(StringView haystack, char needle);
export Vector<size_t> find_all(StringView haystack, StringView needle);
export enum class SearchDirection {
    Forward,
    Backward
};
export Optional<size_t> find_any_of(StringView haystack, StringView needles, SearchDirection);

export ByteString to_snakecase(StringView);
export ByteString to_titlecase(StringView);
export ByteString invert_case(StringView);

export ByteString replace(StringView, StringView needle, StringView replacement, ReplaceMode);
export ErrorOr<String> replace(String const&, StringView needle, StringView replacement, ReplaceMode);

export size_t count(StringView, StringView needle);
export size_t count(StringView, char needle);

}

}

#if USING_AK_GLOBALLY
export using AK::CaseSensitivity;
export using AK::ReplaceMode;
export using AK::SplitBehavior;
export using AK::TrailingCodePointTransformation;
export using AK::TrimMode;
export using AK::TrimWhitespace;
#endif
