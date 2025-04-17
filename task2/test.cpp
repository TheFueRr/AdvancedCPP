// test.cpp
#include "typelist.hpp"
#include <type_traits>

using namespace tl;

using EmptyList = TypeList<>;
using TestList = TypeList<char, int, double>;

// Проверка TypeAt
static_assert(std::is_same_v<typename TypeAt<TestList, 0>::type, char>);
static_assert(std::is_same_v<typename TypeAt<TestList, 2>::type, double>);

// Проверка Size
static_assert(Size<EmptyList>::value == 0);
static_assert(Size<TestList>::value == 3);

// Проверка Contains
static_assert(Contains<TestList, int>::value);
static_assert(!Contains<TestList, float>::value);

// Проверка IndexOf
static_assert(IndexOf<TestList, char>::value == 0);
static_assert(IndexOf<TestList, double>::value == 2);

// Проверка Append/Prepend
using Appended = Append<TestList, float>::type;
static_assert(std::is_same_v<typename TypeAt<Appended, 3>::type, float>);

using Prepended = Prepend<TestList, bool>::type;
static_assert(std::is_same_v<typename TypeAt<Prepended, 0>::type, bool>);

// Проверка ошибок компиляции
// Раскомментировать для проверки:
// using Error1 = TypeAt<TestList, 5>::type; // Ошибка: индекс вне диапазона
// static_assert(IndexOf<TestList, void>::value); // Ошибка: тип не найден

int main() {
    return 0;
}
