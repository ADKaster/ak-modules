/*
 * Copyright (c) 2023, kleines Filmröllchen <filmroellchen@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:SipHash;
import :Forward;
import :Types;

namespace AK {

// Ported from the SipHash reference implementation, released to the public domain:
// https://github.com/veorq/SipHash/blob/eee7d0d84dc7731df2359b243aa5e75d85f6eaef/siphash.c
// The standard is SipHash-2-4, but we use 1-3 for a little more speed.
// Cryptography should use 4-8 for (relative) conservative security,
// though SipHash itself is NOT a cryptographically secure hash algorithm.
export template<size_t message_block_rounds, size_t finalization_rounds>
u64 sip_hash_bytes(ReadonlyBytes input);
export unsigned standard_sip_hash(u64 input);
export unsigned secure_sip_hash(u64 input);

}

#ifdef USING_AK_GLOBALLY
export using AK::secure_sip_hash;
export using AK::sip_hash_bytes;
export using AK::standard_sip_hash;
#endif
