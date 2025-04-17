#include "typemap.hpp"
#include <iostream>

struct DataA { std::string value; };
struct DataB { int value; };

int main() {
    typelist::typemap::TypeMap<int, DataA, double, DataB> myTypeMap;

    // Добавление значений
    myTypeMap.AddValue<int>(42);
    myTypeMap.AddValue<DataA>({"Hello, TypeMap!"});
    myTypeMap.AddValue<double>(3.14);
    myTypeMap.AddValue<DataB>({10});

    // Получение и вывод значений
    std::cout << "int: " << myTypeMap.GetValue<int>() << "\n"; // 42
    std::cout << "DataA: " << myTypeMap.GetValue<DataA>().value << "\n"; // Hello, TypeMap!
    
    // Проверка наличия
    std::cout << "Contains double: " 
              << (myTypeMap.Contains<double>() ? "Yes" : "No") << "\n"; // Yes

    // Удаление значения
    myTypeMap.RemoveValue<double>();
    std::cout << "Contains double after removal: "
              << (myTypeMap.Contains<double>() ? "Yes" : "No") << "\n"; // No

    return 0;
}