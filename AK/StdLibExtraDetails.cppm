/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Ali Mohammad Pur <mpfard@serenityos.org>
 * Copyright (c) 2021, Daniel Bertalan <dani@danielbertalan.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/Platform.h>

export module AK:StdLibExtraDetails;

namespace AK::Detail {

export template<class T, T v>
struct IntegralConstant {
    static constexpr T value = v;
    using ValueType = T;
    using Type = IntegralConstant;
    constexpr operator ValueType() const { return value; }
    constexpr ValueType operator()() const { return value; }
};

export using FalseType = IntegralConstant<bool, false>;
export using TrueType = IntegralConstant<bool, true>;

export template<class T>
using AddConst = const T;

template<class T>
struct __AddConstToReferencedType {
    using Type = T;
};

template<class T>
struct __AddConstToReferencedType<T&> {
    using Type = AddConst<T>&;
};

template<class T>
struct __AddConstToReferencedType<T&&> {
    using Type = AddConst<T>&&;
};

export template<class T>
using AddConstToReferencedType = typename __AddConstToReferencedType<T>::Type;

template<class T>
struct __RemoveConst {
    using Type = T;
};
template<class T>
struct __RemoveConst<T const> {
    using Type = T;
};
export template<class T>
using RemoveConst = typename __RemoveConst<T>::Type;

template<class T>
struct __RemoveVolatile {
    using Type = T;
};

template<class T>
struct __RemoveVolatile<T volatile> {
    using Type = T;
};

export template<typename T>
using RemoveVolatile = typename __RemoveVolatile<T>::Type;

export template<class T>
using RemoveCV = RemoveVolatile<RemoveConst<T>>;

template<typename...>
using VoidType = void;

export template<class T>
inline constexpr bool IsLvalueReference = false;

export template<class T>
inline constexpr bool IsLvalueReference<T&> = true;

template<class T>
inline constexpr bool __IsPointerHelper = false;

template<class T>
inline constexpr bool __IsPointerHelper<T*> = true;

export template<class T>
inline constexpr bool IsPointer = __IsPointerHelper<RemoveCV<T>>;

export template<class>
inline constexpr bool IsFunction = false;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...)> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...)> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...)&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...)&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...)&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...)&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile&&> = true;
export template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&&> = true;

export template<class T>
inline constexpr bool IsRvalueReference = false;
export template<class T>
inline constexpr bool IsRvalueReference<T&&> = true;

template<class T>
struct __RemovePointer {
    using Type = T;
};
template<class T>
struct __RemovePointer<T*> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* const> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* volatile> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* const volatile> {
    using Type = T;
};
export template<typename T>
using RemovePointer = typename __RemovePointer<T>::Type;

export template<typename T, typename U>
inline constexpr bool IsSame = false;

export template<typename T>
inline constexpr bool IsSame<T, T> = true;

template<bool condition, class TrueType, class FalseType>
struct __Conditional {
    using Type = TrueType;
};

template<class TrueType, class FalseType>
struct __Conditional<false, TrueType, FalseType> {
    using Type = FalseType;
};

export template<bool condition, class TrueType, class FalseType>
using Conditional = typename __Conditional<condition, TrueType, FalseType>::Type;

export template<typename T>
inline constexpr bool IsNullPointer = IsSame<decltype(nullptr), RemoveCV<T>>;

template<typename T>
struct __RemoveReference {
    using Type = T;
};
template<class T>
struct __RemoveReference<T&> {
    using Type = T;
};
template<class T>
struct __RemoveReference<T&&> {
    using Type = T;
};

export template<typename T>
using RemoveReference = typename __RemoveReference<T>::Type;

export template<typename T>
using RemoveCVReference = RemoveCV<RemoveReference<T>>;

template<typename T>
struct __MakeUnsigned {
    using Type = void;
};
template<>
struct __MakeUnsigned<signed char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<short> {
    using Type = unsigned short;
};
template<>
struct __MakeUnsigned<int> {
    using Type = unsigned int;
};
template<>
struct __MakeUnsigned<long> {
    using Type = unsigned long;
};
template<>
struct __MakeUnsigned<long long> {
    using Type = unsigned long long;
};
template<>
struct __MakeUnsigned<unsigned char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<unsigned short> {
    using Type = unsigned short;
};
template<>
struct __MakeUnsigned<unsigned int> {
    using Type = unsigned int;
};
template<>
struct __MakeUnsigned<unsigned long> {
    using Type = unsigned long;
};
template<>
struct __MakeUnsigned<unsigned long long> {
    using Type = unsigned long long;
};
template<>
struct __MakeUnsigned<char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<char8_t> {
    using Type = char8_t;
};
template<>
struct __MakeUnsigned<char16_t> {
    using Type = char16_t;
};
template<>
struct __MakeUnsigned<char32_t> {
    using Type = char32_t;
};
template<>
struct __MakeUnsigned<bool> {
    using Type = bool;
};
#if ARCH(AARCH64)
template<>
struct __MakeUnsigned<wchar_t> {
    using Type = wchar_t;
};
#endif

export template<typename T>
using MakeUnsigned = typename __MakeUnsigned<T>::Type;

template<typename T>
struct __MakeSigned {
    using Type = void;
};
template<>
struct __MakeSigned<signed char> {
    using Type = signed char;
};
template<>
struct __MakeSigned<short> {
    using Type = short;
};
template<>
struct __MakeSigned<int> {
    using Type = int;
};
template<>
struct __MakeSigned<long> {
    using Type = long;
};
template<>
struct __MakeSigned<long long> {
    using Type = long long;
};
template<>
struct __MakeSigned<unsigned char> {
    using Type = char;
};
template<>
struct __MakeSigned<unsigned short> {
    using Type = short;
};
template<>
struct __MakeSigned<unsigned int> {
    using Type = int;
};
template<>
struct __MakeSigned<unsigned long> {
    using Type = long;
};
template<>
struct __MakeSigned<unsigned long long> {
    using Type = long long;
};
template<>
struct __MakeSigned<char> {
    using Type = char;
};
#if ARCH(AARCH64)
template<>
struct __MakeSigned<wchar_t> {
    using Type = void;
};
#endif

export template<typename T>
using MakeSigned = typename __MakeSigned<T>::Type;

export template<typename T>
auto declval() -> T;

template<typename...>
struct __CommonType;

template<typename T>
struct __CommonType<T> {
    using Type = T;
};

template<typename T1, typename T2>
struct __CommonType<T1, T2> {
    using Type = decltype(true ? declval<T1>() : declval<T2>());
};

template<typename T1, typename T2, typename... Ts>
struct __CommonType<T1, T2, Ts...> {
    using Type = typename __CommonType<typename __CommonType<T1, T2>::Type, Ts...>::Type;
};

export template<typename... Ts>
using CommonType = typename __CommonType<Ts...>::Type;

export template<class T>
inline constexpr bool IsVoid = IsSame<void, RemoveCV<T>>;

export template<class T>
inline constexpr bool IsConst = false;

export template<class T>
inline constexpr bool IsConst<T const> = true;

export template<typename T>
inline constexpr bool IsEnum = __is_enum(T);

export template<typename T>
inline constexpr bool IsUnion = __is_union(T);

export template<typename T>
inline constexpr bool IsClass = __is_class(T);

export template<typename Base, typename Derived>
inline constexpr bool IsBaseOf = __is_base_of(Base, Derived);

template<typename T>
inline constexpr bool __IsIntegral = false;

template<>
inline constexpr bool __IsIntegral<bool> = true;
template<>
inline constexpr bool __IsIntegral<unsigned char> = true;
template<>
inline constexpr bool __IsIntegral<char8_t> = true;
template<>
inline constexpr bool __IsIntegral<char16_t> = true;
template<>
inline constexpr bool __IsIntegral<char32_t> = true;
template<>
inline constexpr bool __IsIntegral<unsigned short> = true;
template<>
inline constexpr bool __IsIntegral<unsigned int> = true;
template<>
inline constexpr bool __IsIntegral<unsigned long> = true;
template<>
inline constexpr bool __IsIntegral<unsigned long long> = true;

export template<typename T>
inline constexpr bool IsIntegral = __IsIntegral<MakeUnsigned<RemoveCV<T>>>;

template<typename T>
inline constexpr bool __IsFloatingPoint = false;
template<>
inline constexpr bool __IsFloatingPoint<float> = true;
template<>
inline constexpr bool __IsFloatingPoint<double> = true;
template<>
inline constexpr bool __IsFloatingPoint<long double> = true;

export template<typename T>
inline constexpr bool IsFloatingPoint = __IsFloatingPoint<RemoveCV<T>>;

export template<typename ReferenceType, typename T>
using CopyConst = Conditional<IsConst<ReferenceType>, AddConst<T>, RemoveConst<T>>;

export template<typename... Ts>
using Void = void;

export template<typename... _Ignored>
constexpr auto DependentFalse = false;

export template<typename T>
inline constexpr bool IsSigned = IsSame<T, MakeSigned<T>>;

export template<typename T>
inline constexpr bool IsUnsigned = IsSame<T, MakeUnsigned<T>>;

export template<typename T>
inline constexpr bool IsArithmetic = IsIntegral<T> || IsFloatingPoint<T>;

export template<typename T>
inline constexpr bool IsFundamental = IsArithmetic<T> || IsVoid<T> || IsNullPointer<T>;

export template<typename T, T... Ts>
struct IntegerSequence {
    using Type = T;
    static constexpr unsigned size() noexcept { return sizeof...(Ts); }
};

export template<unsigned... Indices>
using IndexSequence = IntegerSequence<unsigned, Indices...>;

#if __has_builtin(__make_integer_seq)
export template<typename T, T N>
using MakeIntegerSequence = __make_integer_seq<IntegerSequence, T, N>;
#elif __has_builtin(__integer_pack)
export template<typename T, T N>
using MakeIntegerSequence = IntegerSequence<T, __integer_pack(N)...>;
#else
export template<typename T, T N, T... Ts>
auto make_integer_sequence_impl()
{
    if constexpr (N == 0)
        return IntegerSequence<T, Ts...> {};
    else
        return make_integer_sequence_impl<T, N - 1, N - 1, Ts...>();
}

export template<typename T, T N>
using MakeIntegerSequence = decltype(make_integer_sequence_impl<T, N>());
#endif

export template<unsigned N>
using MakeIndexSequence = MakeIntegerSequence<unsigned, N>;

template<typename T>
struct __IdentityType {
    using Type = T;
};

export template<typename T>
using IdentityType = typename __IdentityType<T>::Type;

template<typename T, typename = void>
struct __AddReference {
    using LvalueType = T;
    using TvalueType = T;
};

template<typename T>
struct __AddReference<T, VoidType<T&>> {
    using LvalueType = T&;
    using RvalueType = T&&;
};

export template<typename T>
using AddLvalueReference = typename __AddReference<T>::LvalueType;

export template<typename T>
using AddRvalueReference = typename __AddReference<T>::RvalueType;

export template<class T>
requires(IsEnum<T>) using UnderlyingType = __underlying_type(T);

template<typename T, unsigned ExpectedSize, unsigned ActualSize>
struct __AssertSize : TrueType {
    static_assert(ActualSize == ExpectedSize,
        "actual size does not match expected size");

    consteval explicit operator bool() const { return value; }
};

// Note: This type is useful, as the sizes will be visible in the
//       compiler error messages, as they will be part of the
//       template parameters. This is not possible with a
//       static_assert on the sizeof a type.
export template<typename T, unsigned ExpectedSize>
using AssertSize = __AssertSize<T, ExpectedSize, sizeof(T)>;

export template<typename T>
inline constexpr bool IsPOD = __is_pod(T);

export template<typename T>
inline constexpr bool IsTrivial = __is_trivial(T);

export template<typename T>
inline constexpr bool IsTriviallyCopyable = __is_trivially_copyable(T);

export template<typename T, typename... Args>
inline constexpr bool IsConstructible = requires { ::new T(declval<Args>()...); };

export template<typename T, typename... Args>
inline constexpr bool IsTriviallyConstructible = __is_trivially_constructible(T, Args...);

export template<typename From, typename To>
inline constexpr bool IsConvertible = requires { declval<void (*)(To)>()(declval<From>()); };

export template<typename T, typename U>
inline constexpr bool IsAssignable = requires { declval<T>() = declval<U>(); };

export template<typename T, typename U>
inline constexpr bool IsTriviallyAssignable = __is_trivially_assignable(T, U);

export template<typename T>
inline constexpr bool IsDestructible = requires { declval<T>().~T(); };

export template<typename T>
#if defined(AK_COMPILER_CLANG)
inline constexpr bool IsTriviallyDestructible = __is_trivially_destructible(T);
#else
inline constexpr bool IsTriviallyDestructible = __has_trivial_destructor(T) && IsDestructible<T>;
#endif

export template<typename T>
inline constexpr bool IsCopyConstructible = IsConstructible<T, AddLvalueReference<AddConst<T>>>;

export template<typename T>
inline constexpr bool IsTriviallyCopyConstructible = IsTriviallyConstructible<T, AddLvalueReference<AddConst<T>>>;

export template<typename T>
inline constexpr bool IsCopyAssignable = IsAssignable<AddLvalueReference<T>, AddLvalueReference<AddConst<T>>>;

export template<typename T>
inline constexpr bool IsTriviallyCopyAssignable = IsTriviallyAssignable<AddLvalueReference<T>, AddLvalueReference<AddConst<T>>>;

export template<typename T>
inline constexpr bool IsMoveConstructible = IsConstructible<T, AddRvalueReference<T>>;

export template<typename T>
inline constexpr bool IsTriviallyMoveConstructible = IsTriviallyConstructible<T, AddRvalueReference<T>>;

export template<typename T>
inline constexpr bool IsMoveAssignable = IsAssignable<AddLvalueReference<T>, AddRvalueReference<T>>;

export template<typename T>
inline constexpr bool IsTriviallyMoveAssignable = IsTriviallyAssignable<AddLvalueReference<T>, AddRvalueReference<T>>;

export template<typename T, template<typename...> typename U>
inline constexpr bool IsSpecializationOf = false;

export template<template<typename...> typename U, typename... Us>
inline constexpr bool IsSpecializationOf<U<Us...>, U> = true;

template<typename T>
struct __Decay {
    typedef RemoveCVReference<T> type;
};
template<typename T>
struct __Decay<T[]> {
    typedef T* type;
};
template<typename T, decltype(sizeof(T)) N>
struct __Decay<T[N]> {
    typedef T* type;
};
// FIXME: Function decay
export template<typename T>
using Decay = typename __Decay<T>::type;

export template<typename T, typename U>
inline constexpr bool IsPointerOfType = IsPointer<Decay<U>> && IsSame<T, RemoveCV<RemovePointer<Decay<U>>>>;

export template<typename T, typename U>
inline constexpr bool IsHashCompatible = false;
export template<typename T>
inline constexpr bool IsHashCompatible<T, T> = true;

export template<typename T, typename... Ts>
inline constexpr bool IsOneOf = (IsSame<T, Ts> || ...);

export template<typename T, typename U>
inline constexpr bool IsSameIgnoringCV = IsSame<RemoveCV<T>, RemoveCV<U>>;

export template<typename T, typename... Ts>
inline constexpr bool IsOneOfIgnoringCV = (IsSameIgnoringCV<T, Ts> || ...);

template<typename...>
struct __InvokeResult { };

template<typename MethodDefBaseType, typename MethodType, typename InstanceType, typename... Args>
struct __InvokeResult<MethodType MethodDefBaseType::*, InstanceType, Args...> {
    using type = decltype((
        declval<InstanceType>()
        .*declval<MethodType MethodDefBaseType::*>())(declval<Args>()...));
};

template<typename F, typename... Args>
struct __InvokeResult<F, Args...> {
    using type = decltype((declval<F>())(declval<Args>()...));
};

export template<typename F, typename... Args>
using InvokeResult = typename __InvokeResult<F, Args...>::type;

}

#if !USING_AK_GLOBALLY
namespace AK {
#endif
export using AK::Detail::AddConst;
export using AK::Detail::AddConstToReferencedType;
export using AK::Detail::AddLvalueReference;
export using AK::Detail::AddRvalueReference;
export using AK::Detail::AssertSize;
export using AK::Detail::CommonType;
export using AK::Detail::Conditional;
export using AK::Detail::CopyConst;
export using AK::Detail::declval;
export using AK::Detail::DependentFalse;
export using AK::Detail::FalseType;
export using AK::Detail::IdentityType;
export using AK::Detail::IndexSequence;
export using AK::Detail::IntegerSequence;
export using AK::Detail::InvokeResult;
export using AK::Detail::IsArithmetic;
export using AK::Detail::IsAssignable;
export using AK::Detail::IsBaseOf;
export using AK::Detail::IsClass;
export using AK::Detail::IsConst;
export using AK::Detail::IsConstructible;
export using AK::Detail::IsConvertible;
export using AK::Detail::IsCopyAssignable;
export using AK::Detail::IsCopyConstructible;
export using AK::Detail::IsDestructible;
export using AK::Detail::IsEnum;
export using AK::Detail::IsFloatingPoint;
export using AK::Detail::IsFunction;
export using AK::Detail::IsFundamental;
export using AK::Detail::IsHashCompatible;
export using AK::Detail::IsIntegral;
export using AK::Detail::IsLvalueReference;
export using AK::Detail::IsMoveAssignable;
export using AK::Detail::IsMoveConstructible;
export using AK::Detail::IsNullPointer;
export using AK::Detail::IsOneOf;
export using AK::Detail::IsOneOfIgnoringCV;
export using AK::Detail::IsPOD;
export using AK::Detail::IsPointer;
export using AK::Detail::IsRvalueReference;
export using AK::Detail::IsSame;
export using AK::Detail::IsSameIgnoringCV;
export using AK::Detail::IsSigned;
export using AK::Detail::IsSpecializationOf;
export using AK::Detail::IsTrivial;
export using AK::Detail::IsTriviallyAssignable;
export using AK::Detail::IsTriviallyConstructible;
export using AK::Detail::IsTriviallyCopyable;
export using AK::Detail::IsTriviallyCopyAssignable;
export using AK::Detail::IsTriviallyCopyConstructible;
export using AK::Detail::IsTriviallyDestructible;
export using AK::Detail::IsTriviallyMoveAssignable;
export using AK::Detail::IsTriviallyMoveConstructible;
export using AK::Detail::IsUnion;
export using AK::Detail::IsUnsigned;
export using AK::Detail::IsVoid;
export using AK::Detail::MakeIndexSequence;
export using AK::Detail::MakeIntegerSequence;
export using AK::Detail::MakeSigned;
export using AK::Detail::MakeUnsigned;
export using AK::Detail::RemoveConst;
export using AK::Detail::RemoveCV;
export using AK::Detail::RemoveCVReference;
export using AK::Detail::RemovePointer;
export using AK::Detail::RemoveReference;
export using AK::Detail::RemoveVolatile;
export using AK::Detail::TrueType;
export using AK::Detail::UnderlyingType;
export using AK::Detail::Void;
#if !USING_AK_GLOBALLY
}
#endif
