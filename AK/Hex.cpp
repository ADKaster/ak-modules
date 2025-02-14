/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Hex.h>
#include <AK/StringBuilder.h>
#include <AK/Types.cppm>
#include <AK/Vector.cppm>

namespace AK {

ErrorOr<ByteBuffer> decode_hex(StringView input)
{
    if ((input.length() % 2) != 0)
        return Error::from_string_view_or_print_error_and_return_errno("Hex string was not an even length"sv, EINVAL);

    auto output = TRY(ByteBuffer::create_zeroed(input.length() / 2));

    for (size_t i = 0; i < input.length() / 2; ++i) {
        auto const c1 = decode_hex_digit(input[i * 2]);
        if (c1 >= 16)
            return Error::from_string_view_or_print_error_and_return_errno("Hex string contains invalid digit"sv, EINVAL);

        auto const c2 = decode_hex_digit(input[i * 2 + 1]);
        if (c2 >= 16)
            return Error::from_string_view_or_print_error_and_return_errno("Hex string contains invalid digit"sv, EINVAL);

        output[i] = (c1 << 4) + c2;
    }

    return { move(output) };
}

#ifdef KERNEL
ErrorOr<NonnullOwnPtr<Kernel::KString>> encode_hex(const ReadonlyBytes input)
{
    StringBuilder output(input.size() * 2);

    for (auto ch : input)
        TRY(output.try_appendff("{:02x}", ch));

    return Kernel::KString::try_create(output.string_view());
}
#else
ByteString encode_hex(const ReadonlyBytes input)
{
    StringBuilder output(input.size() * 2);

    for (auto ch : input)
        output.appendff("{:02x}", ch);

    return output.to_byte_string();
}
#endif

}
