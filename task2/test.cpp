#include "typelist.hpp"
#include <type_traits>
#include <limits>

using namespace typelist;

// Пустой список
using Empty = TypeList<>;
// Список из нескольких типов
using L1 = TypeList<int, char, double>;

// Проверка GetType
static_assert(std::is_same_v<GetType<L1, 0>, int>, "GetType<L1,0> должен быть int");
static_assert(std::is_same_v<GetType<L1, 1>, char>, "GetType<L1,1> должен быть char");
static_assert(std::is_same_v<GetType<L1, 2>, double>, "GetType<L1,2> должен быть double");

// Проверка размера
static_assert(size_v<Empty> == 0, "Пустой список должен иметь размер 0");
static_assert(size_v<L1> == 3, "L1 должен иметь размер 3");

// Проверка contains
static_assert(!contains_v<Empty, int>, "Empty не должен содержать int");
static_assert(contains_v<L1, char>, "L1 должен содержать char");
static_assert(!contains_v<L1, float>, "L1 не должен содержать float");

// Проверка index_of
static_assert(index_of_v<L1, int> == 0, "index_of int в L1 должен быть 0");
static_assert(index_of_v<L1, char> == 1, "index_of char в L1 должен быть 1");
static_assert(index_of_v<L1, double> == 2, "index_of double в L1 должен быть 2");
static_assert(index_of_v<L1, float> == std::numeric_limits<std::size_t>::max(), "float отсутствует, должен быть max");

// Проверка append
using L2 = append_t<L1, float>;
static_assert(std::is_same_v<L2, TypeList<int, char, double, float>>, "append не работает корректно");

// Проверка prepend
using L3 = prepend_t<L1, bool>;
static_assert(std::is_same_v<L3, TypeList<bool, int, char, double>>, "prepend не работает корректно");

// Следующая строка должна приводить к ошибке компиляции при раскомментировании:
//static_assert(std::is_same_v<GetType<L1, 3>, void>, "Out of bounds!!!");

int main() {
    return 0;
}
