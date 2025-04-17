#ifndef TYPELIST_H
#define TYPELIST_H

#include <type_traits>
#include <cstddef>

namespace tl {

template <typename... Ts>
struct TypeList {};

// Получение элемента по индексу
template <typename List, size_t Index>
struct TypeAt;

template <typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0> {
    using type = Head;
};

template <size_t Index, typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, Index> {
    using type = typename TypeAt<TypeList<Tail...>, Index - 1>::type;
};

// Размер списка
template <typename List>
struct Size;

template <typename... Ts>
struct Size<TypeList<Ts...>> {
    static constexpr size_t value = sizeof...(Ts);
};

// Проверка наличия типа
template <typename List, typename T>
struct Contains;

template <typename T>
struct Contains<TypeList<>, T> {
    static constexpr bool value = false;
};

template <typename Head, typename... Tail, typename T>
struct Contains<TypeList<Head, Tail...>, T> {
    static constexpr bool value =
        std::is_same_v<Head, T> || Contains<TypeList<Tail...>, T>::value;
};

// Поиск индекса типа
template <typename List, typename T, size_t Index = 0>
struct IndexOf;

// Ошибка: тип не найден
template <typename T, size_t Index>
struct IndexOf<TypeList<>, T, Index> {
    static_assert(!std::is_same_v<T, T>, "Type not found in TypeList");
};

// Спец. случай: нашли Head == T
template <typename Head, typename... Tail, typename T, size_t Index>
requires std::is_same_v<Head, T>
struct IndexOf<TypeList<Head, Tail...>, T, Index> {
    static constexpr size_t value = Index;
};

// Рекурсивный случай: не нашли в Head, ищем дальше
template <typename Head, typename... Tail, typename T, size_t Index>
requires (!std::is_same_v<Head, T>)
struct IndexOf<TypeList<Head, Tail...>, T, Index> {
    static constexpr size_t value =
        IndexOf<TypeList<Tail...>, T, Index + 1>::value;
};

// Добавление в конец
template <typename List, typename T>
struct Append;

template <typename... Ts, typename T>
struct Append<TypeList<Ts...>, T> {
    using type = TypeList<Ts..., T>;
};

// Добавление в начало
template <typename List, typename T>
struct Prepend;

template <typename... Ts, typename T>
struct Prepend<TypeList<Ts...>, T> {
    using type = TypeList<T, Ts...>;
};

} // namespace tl

#endif // TYPELIST_H