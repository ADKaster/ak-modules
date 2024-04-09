/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:Forward;

import :DefaultDelete;
import :SinglyLinkedListSizePolicy;
import :Types;

namespace AK {

namespace Detail {
template<size_t inline_capacity>
class ByteBuffer;
}

export enum class TrailingCodePointTransformation : u8;

export class BigEndianInputBitStream;
export class BigEndianOutputBitStream;
export class Bitmap;
export using ByteBuffer = Detail::ByteBuffer<32>;
export class CircularBuffer;
export class ConstrainedStream;
export class CountingStream;
export class DeprecatedFlyString;
export class ByteString;
export class DeprecatedStringCodePointIterator;
export class Duration;
export class Error;
export class FlyString;
export class GenericLexer;
export class IPv4Address;
export class JsonArray;
export class JsonObject;
export class JsonValue;
export class LexicalPath;
export class LittleEndianInputBitStream;
export class LittleEndianOutputBitStream;
export class SearchableCircularBuffer;
export class SeekableStream;
export class StackInfo;
export class Stream;
export class String;
export class StringBuilder;
export class StringImpl;
export class StringView;
export class URL;
export class UnixDateTime;
export class Utf16View;
export class Utf32CodePointIterator;
export class Utf32View;
export class Utf8CodePointIterator;
export class Utf8View;

export template<typename T>
class Span;

export template<typename T, size_t Size>
struct Array;

export template<typename Container, typename ValueType>
class SimpleIterator;

export template<typename T>
using ReadonlySpan = Span<T const>;

export using ReadonlyBytes = ReadonlySpan<u8>;
export using Bytes = Span<u8>;

export template<typename T, AK::MemoryOrder DefaultMemoryOrder>
class Atomic;

export template<typename T, typename TSizeCalculationPolicy = DefaultSizeCalculationPolicy>
class SinglyLinkedList;

export template<typename T>
class DoublyLinkedList;

export template<typename T, size_t capacity>
class CircularQueue;

export template<typename T>
struct Traits;

export template<typename T, typename TraitsForT = Traits<T>, bool IsOrdered = false>
class HashTable;

export template<typename T, typename TraitsForT = Traits<T>>
using OrderedHashTable = HashTable<T, TraitsForT, true>;

export template<typename K, typename V, typename KeyTraits = Traits<K>, typename ValueTraits = Traits<V>, bool IsOrdered = false>
class HashMap;

export template<typename K, typename V, typename KeyTraits = Traits<K>, typename ValueTraits = Traits<V>>
using OrderedHashMap = HashMap<K, V, KeyTraits, ValueTraits, true>;

export template<typename T>
class Badge;

export template<typename T>
class FixedArray;

export template<size_t precision, typename Underlying = i32>
class FixedPoint;

export template<typename>
class Function;

export template<typename Out, typename... In>
class Function<Out(In...)>;

export template<typename T>
class NonnullRefPtr;

export template<typename T>
class NonnullOwnPtr;

export template<typename T>
class Optional;

#ifdef KERNEL
export template<typename T>
class NonnullLockRefPtr;

export template<typename T>
struct LockRefPtrTraits;

export template<typename T, typename PtrTraits = LockRefPtrTraits<T>>
class LockRefPtr;
#endif

export template<typename T>
class RefPtr;

export template<typename T, typename TDeleter = DefaultDelete<T>>
class OwnPtr;

export template<typename T>
class WeakPtr;

export template<typename T, size_t inline_capacity = 0>
requires(!IsRvalueReference<T>) class Vector;

export template<typename T, typename ErrorType = Error>
class [[nodiscard]] ErrorOr;

}

#if USING_AK_GLOBALLY
export using AK::Array;
export using AK::Atomic;
export using AK::Badge;
export using AK::BigEndianInputBitStream;
export using AK::BigEndianOutputBitStream;
export using AK::Bitmap;
export using AK::ByteBuffer;
export using AK::Bytes;
export using AK::ByteString;
export using AK::CircularBuffer;
export using AK::CircularQueue;
export using AK::ConstrainedStream;
export using AK::CountingStream;
export using AK::DeprecatedFlyString;
export using AK::DeprecatedStringCodePointIterator;
export using AK::DoublyLinkedList;
export using AK::Duration;
export using AK::Error;
export using AK::ErrorOr;
export using AK::FixedArray;
export using AK::FixedPoint;
export using AK::FlyString;
export using AK::Function;
export using AK::GenericLexer;
export using AK::HashMap;
export using AK::HashTable;
export using AK::IPv4Address;
export using AK::JsonArray;
export using AK::JsonObject;
export using AK::JsonValue;
export using AK::LexicalPath;
export using AK::LittleEndianInputBitStream;
export using AK::LittleEndianOutputBitStream;
export using AK::NonnullOwnPtr;
export using AK::NonnullRefPtr;
export using AK::Optional;
export using AK::OwnPtr;
export using AK::ReadonlyBytes;
export using AK::RefPtr;
export using AK::SearchableCircularBuffer;
export using AK::SeekableStream;
export using AK::SinglyLinkedList;
export using AK::Span;
export using AK::StackInfo;
export using AK::Stream;
export using AK::String;
export using AK::StringBuilder;
export using AK::StringImpl;
export using AK::StringView;
export using AK::TrailingCodePointTransformation;
export using AK::Traits;
export using AK::UnixDateTime;
export using AK::URL;
export using AK::Utf16View;
export using AK::Utf32CodePointIterator;
export using AK::Utf32View;
export using AK::Utf8CodePointIterator;
export using AK::Utf8View;
export using AK::Vector;

#    ifdef KERNEL
export using AK::LockRefPtr;
export using AK::LockRefPtrTraits;
export using AK::NonnullLockRefPtr;
#    endif

#endif
