/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/AnyOf.cppm>
#include <AK/ByteBuffer.h>
#include <AK/Find.cppm>
#include <AK/Function.h>
#include <AK/StringBuilder.h>
#include <AK/StringView.cppm>
#include <AK/Vector.cppm>

#ifndef KERNEL
#    include <AK/ByteString.h>
#    include <AK/DeprecatedFlyString.h>
#    include <AK/FlyString.h>
#    include <AK/String.h>
#endif

module AK:StringView;

namespace AK {

#ifndef KERNEL
StringView::StringView(String const& string)
    : m_characters(reinterpret_cast<char const*>(string.bytes().data()))
    , m_length(string.bytes().size())
{
}

StringView::StringView(FlyString const& string)
    : m_characters(reinterpret_cast<char const*>(string.bytes().data()))
    , m_length(string.bytes().size())
{
}

StringView::StringView(ByteString const& string)
    : m_characters(string.characters())
    , m_length(string.length())
{
}

StringView::StringView(DeprecatedFlyString const& string)
    : m_characters(string.characters())
    , m_length(string.length())
{
}
#endif

StringView::StringView(ByteBuffer const& buffer)
    : m_characters((char const*)buffer.data())
    , m_length(buffer.size())
{
}

Vector<StringView> StringView::split_view(char const separator, SplitBehavior split_behavior) const
{
    StringView seperator_view { &separator, 1 };
    return split_view(seperator_view, split_behavior);
}

Vector<StringView> StringView::split_view(StringView separator, SplitBehavior split_behavior) const
{
    Vector<StringView> parts;
    for_each_split_view(separator, split_behavior, [&](StringView view) {
        parts.append(view);
    });
    return parts;
}

Vector<StringView> StringView::lines(bool consider_cr) const
{
    if (is_empty())
        return {};

    if (!consider_cr)
        return split_view('\n', SplitBehavior::KeepEmpty);

    Vector<StringView> v;
    size_t substart = 0;
    bool last_ch_was_cr = false;
    bool split_view = false;
    for (size_t i = 0; i < length(); ++i) {
        char ch = characters_without_null_termination()[i];
        if (ch == '\n') {
            split_view = true;
            if (last_ch_was_cr) {
                substart = i + 1;
                split_view = false;
            }
        }
        if (ch == '\r') {
            split_view = true;
            last_ch_was_cr = true;
        } else {
            last_ch_was_cr = false;
        }
        if (split_view) {
            size_t sublen = i - substart;
            v.append(substring_view(substart, sublen));
            substart = i + 1;
        }
        split_view = false;
    }
    size_t taillen = length() - substart;
    if (taillen != 0)
        v.append(substring_view(substart, taillen));
    return v;
}

bool StringView::starts_with(char ch) const
{
    if (is_empty())
        return false;
    return ch == characters_without_null_termination()[0];
}

bool StringView::starts_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::starts_with(*this, str, case_sensitivity);
}

bool StringView::ends_with(char ch) const
{
    if (is_empty())
        return false;
    return ch == characters_without_null_termination()[length() - 1];
}

bool StringView::ends_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::ends_with(*this, str, case_sensitivity);
}

bool StringView::matches(StringView mask, Vector<MaskSpan>& mask_spans, CaseSensitivity case_sensitivity) const
{
    return StringUtils::matches(*this, mask, case_sensitivity, &mask_spans);
}

bool StringView::matches(StringView mask, CaseSensitivity case_sensitivity) const
{
    return StringUtils::matches(*this, mask, case_sensitivity);
}

bool StringView::contains(char needle) const
{
    for (char current : *this) {
        if (current == needle)
            return true;
    }
    return false;
}

bool StringView::contains(u32 needle) const
{
    // A code point should be at most four UTF-8 bytes, which easily fits into StringBuilder's inline-buffer.
    // Therefore, this will not allocate.
    StringBuilder needle_builder;
    auto result = needle_builder.try_append_code_point(needle);
    if (result.is_error()) {
        // The needle is invalid, therefore the string does not contain it.
        return false;
    }

    return contains(needle_builder.string_view());
}

bool StringView::contains(StringView needle, CaseSensitivity case_sensitivity) const
{
    return StringUtils::contains(*this, needle, case_sensitivity);
}

bool StringView::equals_ignoring_ascii_case(StringView other) const
{
    return StringUtils::equals_ignoring_ascii_case(*this, other);
}

#ifndef KERNEL
ByteString StringView::to_lowercase_string() const
{
    return StringImpl::create_lowercased(characters_without_null_termination(), length()).release_nonnull();
}

ByteString StringView::to_uppercase_string() const
{
    return StringImpl::create_uppercased(characters_without_null_termination(), length()).release_nonnull();
}

ByteString StringView::to_titlecase_string() const
{
    return StringUtils::to_titlecase(*this);
}
#endif

StringView StringView::substring_view_starting_from_substring(StringView substring) const
{
    char const* remaining_characters = substring.characters_without_null_termination();
    VERIFY(remaining_characters >= m_characters);
    VERIFY(remaining_characters <= m_characters + m_length);
    size_t remaining_length = m_length - (remaining_characters - m_characters);
    return { remaining_characters, remaining_length };
}

StringView StringView::substring_view_starting_after_substring(StringView substring) const
{
    char const* remaining_characters = substring.characters_without_null_termination() + substring.length();
    VERIFY(remaining_characters >= m_characters);
    VERIFY(remaining_characters <= m_characters + m_length);
    size_t remaining_length = m_length - (remaining_characters - m_characters);
    return { remaining_characters, remaining_length };
}

bool StringView::copy_characters_to_buffer(char* buffer, size_t buffer_size) const
{
    // We must fit at least the NUL-terminator.
    VERIFY(buffer_size > 0);

    size_t characters_to_copy = min(m_length, buffer_size - 1);
    __builtin_memcpy(buffer, m_characters, characters_to_copy);
    buffer[characters_to_copy] = 0;

    return characters_to_copy == m_length;
}

#ifndef KERNEL

bool StringView::operator==(ByteString const& string) const
{
    return *this == string.view();
}

ByteString StringView::to_byte_string() const { return ByteString { *this }; }

ByteString StringView::replace(StringView needle, StringView replacement, ReplaceMode replace_mode) const
{
    return StringUtils::replace(*this, needle, replacement, replace_mode);
}
#endif

Vector<size_t> StringView::find_all(StringView needle) const
{
    return StringUtils::find_all(*this, needle);
}

Vector<StringView> StringView::split_view_if(Function<bool(char)> const& predicate, SplitBehavior split_behavior) const
{
    if (is_empty())
        return {};

    Vector<StringView> v;
    size_t substart = 0;
    bool keep_empty = has_flag(split_behavior, SplitBehavior::KeepEmpty);
    bool keep_separator = has_flag(split_behavior, SplitBehavior::KeepTrailingSeparator);
    for (size_t i = 0; i < length(); ++i) {
        char ch = characters_without_null_termination()[i];
        if (predicate(ch)) {
            size_t sublen = i - substart;
            if (sublen != 0 || keep_empty)
                v.append(substring_view(substart, keep_separator ? sublen + 1 : sublen));
            substart = i + 1;
        }
    }
    size_t taillen = length() - substart;
    if (taillen != 0 || keep_empty)
        v.append(substring_view(substart, taillen));
    return v;
}

}