/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */


module;

#include <AK/Platform.h>

export module AK:Concepts;
import :IterationDecision;
import :StdLibExtras;

namespace AK {
export class StringView;
export template<typename T>
class Span;
}

namespace AK::Concepts {

export template<typename T>
concept Integral = IsIntegral<T>;

export template<typename T>
concept FloatingPoint = IsFloatingPoint<T>;

export template<typename T>
concept Fundamental = IsFundamental<T>;

export template<typename T>
concept Arithmetic = IsArithmetic<T>;

export template<typename T>
concept Signed = IsSigned<T>;

export template<typename T>
concept Unsigned = IsUnsigned<T>;

export template<typename T>
concept Enum = IsEnum<T>;

export template<typename T, typename U>
concept SameAs = IsSame<T, U>;

export template<class From, class To>
concept ConvertibleTo = IsConvertible<From, To>;

export template<typename U, typename... Ts>
concept OneOf = IsOneOf<U, Ts...>;

export template<typename U, typename... Ts>
concept OneOfIgnoringCV = IsOneOfIgnoringCV<U, Ts...>;

export template<typename T, template<typename...> typename S>
concept SpecializationOf = IsSpecializationOf<T, S>;

export template<typename T, typename S>
concept DerivedFrom = IsBaseOf<S, T>;

export template<typename T>
concept AnyString = IsConstructible<StringView, RemoveCVReference<T> const&>;

export template<typename T, typename U>
concept HashCompatible = IsHashCompatible<Detail::Decay<T>, Detail::Decay<U>>;

// Any indexable, sized, contiguous data structure.
export template<typename ArrayT, typename ContainedT, typename SizeT = size_t>
concept ArrayLike = requires(ArrayT array, SizeT index) {
    {
        array[index]
    }
    -> SameAs<RemoveReference<ContainedT>&>;

    {
        array.size()
    }
    -> SameAs<SizeT>;

    {
        array.span()
    }
    -> SameAs<Span<RemoveReference<ContainedT>>>;

    {
        array.data()
    }
    -> SameAs<RemoveReference<ContainedT>*>;
};

// Any indexable data structure.
export template<typename ArrayT, typename ContainedT, typename SizeT = size_t>
concept Indexable = requires(ArrayT array, SizeT index) {
    {
        array[index]
    }
    -> OneOf<RemoveReference<ContainedT>&, RemoveReference<ContainedT>>;
};

export template<typename Func, typename... Args>
concept VoidFunction = requires(Func func, Args... args) {
    {
        func(args...)
    }
    -> SameAs<void>;
};

export template<typename Func, typename... Args>
concept IteratorFunction = requires(Func func, Args... args) {
    {
        func(args...)
    }
    -> SameAs<IterationDecision>;
};

export template<typename T, typename EndT>
concept IteratorPairWith = requires(T it, EndT end) {
    *it;
    {
        it != end
    } -> SameAs<bool>;
    ++it;
};

export template<typename T>
concept IterableContainer = requires {
    {
        declval<T>().begin()
    } -> IteratorPairWith<decltype(declval<T>().end())>;
};

export template<typename Func, typename... Args>
concept FallibleFunction = requires(Func&& func, Args&&... args) {
    func(forward<Args>(args)...).is_error();
    func(forward<Args>(args)...).release_error();
    func(forward<Args>(args)...).release_value();
};

}
namespace AK::Detail {

export template<typename T, typename Out, typename... Args>
inline constexpr bool IsCallableWithArguments = requires(T t) {
    {
        t(declval<Args>()...)
    } -> Concepts::ConvertibleTo<Out>;
} || requires(T t) {
    {
        t(declval<Args>()...)
    } -> Concepts::SameAs<Out>;
};

}

namespace AK {

export using Detail::IsCallableWithArguments;

}

namespace AK::Concepts {

export template<typename Func, typename R, typename... Args>
concept CallableAs = Detail::IsCallableWithArguments<Func, R, Args...>;

}

#if !USING_AK_GLOBALLY
namespace AK {
#endif
export using AK::Concepts::Arithmetic;
export using AK::Concepts::ArrayLike;
export using AK::Concepts::CallableAs;
export using AK::Concepts::ConvertibleTo;
export using AK::Concepts::DerivedFrom;
export using AK::Concepts::Enum;
export using AK::Concepts::FallibleFunction;
export using AK::Concepts::FloatingPoint;
export using AK::Concepts::Fundamental;
export using AK::Concepts::Indexable;
export using AK::Concepts::Integral;
export using AK::Concepts::IterableContainer;
export using AK::Concepts::IteratorFunction;
export using AK::Concepts::IteratorPairWith;
export using AK::Concepts::OneOf;
export using AK::Concepts::OneOfIgnoringCV;
export using AK::Concepts::SameAs;
export using AK::Concepts::Signed;
export using AK::Concepts::SpecializationOf;
export using AK::Concepts::Unsigned;
export using AK::Concepts::VoidFunction;
#if !USING_AK_GLOBALLY
}
#endif
