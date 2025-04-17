#ifndef TYPELIST_H
#define TYPELIST_H

#include <cstddef>
#include <type_traits>
#include <limits>

namespace typelist {

template <typename... Ts>
struct TypeList {};

template <std::size_t I, typename List>
struct Get;

// Специализация: элемент 0
template <typename T, typename... Ts>
struct Get<0, TypeList<T, Ts...>> {
    using type = T;
};

// Рекурсивный шаг
template <std::size_t I, typename T, typename... Ts>
struct Get<I, TypeList<T, Ts...>> : Get<I - 1, TypeList<Ts...>> {};

// Ошибка компиляции при выходе за границы
template <std::size_t I>
struct Get<I, TypeList<>> {
    static_assert(I != I, "typelist::Get: index out of bounds of list");
};

template <typename List>
struct Size;

template <typename... Ts>
struct Size<TypeList<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <typename List, typename T>
struct Contains;

template <typename T>
struct Contains<TypeList<>, T> : std::false_type {};

template <typename U, typename... Us, typename T>
struct Contains<TypeList<U, Us...>, T>
    : std::conditional_t< std::is_same_v<U, T>,
                        std::true_type,
                        Contains<TypeList<Us...>, T> > {};

// IndexOf: индекс первого вхождения T или max() если нет
template <typename List, typename T>
struct IndexOf;

template <typename T>
struct IndexOf<TypeList<>, T>
    : std::integral_constant<std::size_t, std::numeric_limits<std::size_t>::max()> {};

template <typename U, typename... Us, typename T>
struct IndexOf<TypeList<U, Us...>, T>
    : std::conditional_t< std::is_same_v<U, T>,
        std::integral_constant<std::size_t, 0>,
        std::integral_constant<
            std::size_t,
            (Contains<TypeList<Us...>, T>::value
                ? 1 + IndexOf<TypeList<Us...>, T>::value
                : std::numeric_limits<std::size_t>::max())
        >
      > {};

// Append: добавление типа T в конец списка
template <typename List, typename T>
struct Append;

template <typename... Ts, typename T>
struct Append<TypeList<Ts...>, T> {
    using type = TypeList<Ts..., T>;
};

// Prepend: добавление типа T в начало списка
template <typename List, typename T>
struct Prepend;

template <typename... Ts, typename T>
struct Prepend<TypeList<Ts...>, T> {
    using type = TypeList<T, Ts...>;
};

// Получить тип по индексу: GetType<List, I>
template <typename List, std::size_t I>
using GetType = typename Get<I, List>::type;

// Размер списка: size_v<List>
template <typename List>
inline constexpr std::size_t size_v = Size<List>::value;

// Проверка наличия типа: contains_v<List, T>
template <typename List, typename T>
inline constexpr bool contains_v = Contains<List, T>::value;

// Индекс типа: index_of_v<List, T>
template <typename List, typename T>
inline constexpr std::size_t index_of_v = IndexOf<List, T>::value;

// Добавить тип в конец: append_t<List, T>
template <typename List, typename T>
using append_t = typename Append<List, T>::type;

// Добавить тип в начало: prepend_t<List, T>
template <typename List, typename T>
using prepend_t = typename Prepend<List, T>::type;

} // namespace TypeList

#endif // TYPELIST_H