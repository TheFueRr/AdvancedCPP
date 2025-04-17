#ifndef TYPEMAP_H
#define TYPEMAP_H

#include "typelist.hpp"
#include <tuple>
#include <optional>
#include <type_traits>

// Ассоциативный контейнер: типы-ключи связываются со значениями
namespace typelist {

namespace typemap {

// TypeMap хранит для каждого ключевого типа std::optional<T>
template <typename... Keys>
class TypeMap {
private:
    std::tuple<std::optional<Keys>...> data_;
    using KeyList = TypeList<Keys...>;

public:
    // Добавление или обновление значения ключа T
    template <typename T>
    void AddValue(T value) {
        static_assert(contains_v<KeyList, T>, "TypeMap::AddValue: T не является ключом");
        std::get<std::optional<T>>(data_) = std::move(value);
    }

    // Получение значения по ключу T (UB, если нет)
    template <typename T>
    T& GetValue() {
        static_assert(contains_v<KeyList, T>, "TypeMap::GetValue: T не является ключом");
        return *std::get<std::optional<T>>(data_);
    }

    template <typename T>
    const T& GetValue() const {
        static_assert(contains_v<KeyList, T>, "TypeMap::GetValue: T не является ключом");
        return *std::get<std::optional<T>>(data_);
    }

    // Проверка наличия значения по ключу T
    template <typename T>
    bool Contains() const {
        static_assert(contains_v<KeyList, T>, "TypeMap::Contains: T не является ключом");
        return std::get<std::optional<T>>(data_).has_value();
    }

    // Удаление значения по ключу T
    template <typename T>
    void RemoveValue() {
        static_assert(contains_v<KeyList, T>, "TypeMap::RemoveValue: T не является ключом");
        std::get<std::optional<T>>(data_).reset();
    }
};

} // namespace TypeMap

} // namespace TypeList

#endif // TYPEMAP_H