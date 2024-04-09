/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/PublicMacros.h>

export module AK:TypeList;
import :Types;

namespace AK {

export template<typename... Types>
struct TypeList;

export template<unsigned Index, typename List>
struct TypeListElement;

#if __has_builtin(__type_pack_element)
export template<unsigned Index, typename... Types>
struct TypeListElement<Index, TypeList<Types...>> {
    using Type = __type_pack_element<Index, Types...>;
};
#else
export template<unsigned Index, typename Head, typename... Tail>
struct TypeListElement<Index, TypeList<Head, Tail...>>
    : TypeListElement<Index - 1, TypeList<Tail...>> {
};

export template<typename Head, typename... Tail>
struct TypeListElement<0, TypeList<Head, Tail...>> {
    using Type = Head;
};
#endif

export template<typename... Types>
struct TypeList {
    static constexpr unsigned size = sizeof...(Types);

    template<unsigned N>
    using Type = typename TypeListElement<N, TypeList<Types...>>::Type;
};

export template<typename T>
struct TypeWrapper {
    using Type = T;
};

export template<typename List, typename F, unsigned... Indices>
constexpr void for_each_type_impl(F&& f, IndexSequence<Indices...>)
{
    (forward<F>(f)(TypeWrapper<typename List::template Type<Indices>> {}), ...);
}

export template<typename List, typename F>
constexpr void for_each_type(F&& f)
{
    for_each_type_impl<List>(forward<F>(f), MakeIndexSequence<List::size> {});
}

export template<typename ListA, typename ListB, typename F, unsigned... Indices>
constexpr void for_each_type_zipped_impl(F&& f, IndexSequence<Indices...>)
{
    (forward<F>(f)(TypeWrapper<typename ListA::template Type<Indices>> {}, TypeWrapper<typename ListB::template Type<Indices>> {}), ...);
}

export template<typename ListA, typename ListB, typename F>
constexpr void for_each_type_zipped(F&& f)
{
    static_assert(ListA::size == ListB::size, "Can't zip TypeLists that aren't the same size!");
    for_each_type_zipped_impl<ListA, ListB>(forward<F>(f), MakeIndexSequence<ListA::size> {});
}

}

#if USING_AK_GLOBALLY
export using AK::for_each_type;
export using AK::for_each_type_zipped;
export using AK::TypeList;
export using AK::TypeListElement;
export using AK::TypeWrapper;
#endif
