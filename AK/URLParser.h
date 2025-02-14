/*
 * Copyright (c) 2021, Max Wipfli <mail@maxwipfli.ch>
 * Copyright (c) 2023, Shannon Booth <shannon@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Optional.cppm>
#include <AK/StringView.cppm>
#include <AK/URL.h>

namespace AK {

#define ENUMERATE_STATES                 \
    STATE(SchemeStart)                   \
    STATE(Scheme)                        \
    STATE(NoScheme)                      \
    STATE(SpecialRelativeOrAuthority)    \
    STATE(PathOrAuthority)               \
    STATE(Relative)                      \
    STATE(RelativeSlash)                 \
    STATE(SpecialAuthoritySlashes)       \
    STATE(SpecialAuthorityIgnoreSlashes) \
    STATE(Authority)                     \
    STATE(Host)                          \
    STATE(Hostname)                      \
    STATE(Port)                          \
    STATE(File)                          \
    STATE(FileSlash)                     \
    STATE(FileHost)                      \
    STATE(PathStart)                     \
    STATE(Path)                          \
    STATE(CannotBeABaseUrlPath)          \
    STATE(Query)                         \
    STATE(Fragment)

class URLParser {
public:
    enum class State {
#define STATE(state) state,
        ENUMERATE_STATES
#undef STATE
    };

    static char const* state_name(State const& state)
    {
        switch (state) {
#define STATE(state)   \
    case State::state: \
        return #state;
            ENUMERATE_STATES
#undef STATE
        }
        VERIFY_NOT_REACHED();
    }

    // https://url.spec.whatwg.org/#concept-basic-url-parser
    static URL basic_parse(StringView input, Optional<URL> const& base_url = {}, Optional<URL> url = {}, Optional<State> state_override = {});

    // https://url.spec.whatwg.org/#string-percent-encode-after-encoding
    static ErrorOr<String> percent_encode_after_encoding(StringView input, URL::PercentEncodeSet percent_encode_set, bool space_as_plus = false);

    // https://url.spec.whatwg.org/#concept-host-serializer
    static ErrorOr<String> serialize_host(URL::Host const&);

    // https://url.spec.whatwg.org/#shorten-a-urls-path
    static void shorten_urls_path(URL&);
};

#undef ENUMERATE_STATES

}

#if USING_AK_GLOBALLY
using AK::URLParser;
#endif
