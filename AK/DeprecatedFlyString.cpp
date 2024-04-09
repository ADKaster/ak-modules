/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/ByteString.h>
#include <AK/DeprecatedFlyString.h>
#include <AK/HashTable.h>
#include <AK/Optional.cppm>
#include <AK/Singleton.cppm>
#include <AK/StringUtils.cppm>
#include <AK/StringView.cppm>

namespace AK {

struct DeprecatedFlyStringImplTraits : public Traits<StringImpl*> {
    static unsigned hash(StringImpl const* s) { return s ? s->hash() : 0; }
    static bool equals(StringImpl const* a, StringImpl const* b)
    {
        VERIFY(a);
        VERIFY(b);
        return *a == *b;
    }
};

static Singleton<HashTable<StringImpl const*, DeprecatedFlyStringImplTraits>> s_table;

static HashTable<StringImpl const*, DeprecatedFlyStringImplTraits>& fly_impls()
{
    return *s_table;
}

void DeprecatedFlyString::did_destroy_impl(Badge<StringImpl>, StringImpl& impl)
{
    fly_impls().remove(&impl);
}

DeprecatedFlyString::DeprecatedFlyString(ByteString const& string)
{
    if (string.impl()->is_fly()) {
        m_impl = string.impl();
        return;
    }
    auto it = fly_impls().find(const_cast<StringImpl*>(string.impl()));
    if (it == fly_impls().end()) {
        fly_impls().set(const_cast<StringImpl*>(string.impl()));
        string.impl()->set_fly({}, true);
        m_impl = string.impl();
    } else {
        VERIFY((*it)->is_fly());
        m_impl = *it;
    }
}

DeprecatedFlyString::DeprecatedFlyString(StringView string)
{
    if (string.is_null())
        return;
    auto it = fly_impls().find(string.hash(), [&](auto& candidate) {
        return string == *candidate;
    });
    if (it == fly_impls().end()) {
        auto new_string = string.to_byte_string();
        fly_impls().set(new_string.impl());
        new_string.impl()->set_fly({}, true);
        m_impl = new_string.impl();
    } else {
        VERIFY((*it)->is_fly());
        m_impl = *it;
    }
}

bool DeprecatedFlyString::equals_ignoring_ascii_case(StringView other) const
{
    return StringUtils::equals_ignoring_ascii_case(view(), other);
}

bool DeprecatedFlyString::starts_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::starts_with(view(), str, case_sensitivity);
}

bool DeprecatedFlyString::ends_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::ends_with(view(), str, case_sensitivity);
}

DeprecatedFlyString DeprecatedFlyString::to_lowercase() const
{
    return ByteString(*m_impl).to_lowercase();
}

bool DeprecatedFlyString::operator==(ByteString const& other) const
{
    return m_impl == other.impl() || view() == other.view();
}

bool DeprecatedFlyString::operator==(StringView string) const
{
    return view() == string;
}

bool DeprecatedFlyString::operator==(char const* string) const
{
    return view() == string;
}

}
