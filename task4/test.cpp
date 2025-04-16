#include "mixin.hpp"
#include <cassert>
#include <vector>

class Number: 
    public less_than_comparable<Number>,
    public counter<Number> 
{
public:
    Number(int value) : m_value{value} {}

    int value() const { return m_value; }

    bool operator<(const Number& other) const {
        return m_value < other.m_value;
    }

private:
    int m_value;
};

void test_comparison_operators() {
    // Тест 1: Проверка базовых операций сравнения
    Number a(5), b(10), c(5);
    
    assert(a < b);    // 5 < 10
    assert(b > a);    // 10 > 5
    assert(a <= c);   // 5 <= 5
    assert(b >= a);   // 10 >= 5
    assert(a == c);   // 5 == 5
    assert(a != b);   // 5 != 10
    
    std::cout << "Test 1: Comparison operators passed\n";
}

void test_edge_cases() {
    // Тест 2: Проверка пограничных случаев
    Number zero(0), negative(-5), max_int(2147483647);
    
    assert(negative < zero);
    assert(zero > negative);
    assert(max_int >= Number(100));
    assert(negative != zero);
    assert(zero == Number(0));
    
    assert(!(zero < zero));
    assert(zero <= zero);
    assert(zero >= zero);
    
    std::cout << "Test 2: Edge cases passed\n";
}

void test_counter_basic() {
    // Тест 3: Базовая проверка счетчика
    const size_t initial_count = counter<Number>::count();
    
    {
        Number n1(1);
        Number n2(2);
        assert(counter<Number>::count() == initial_count + 2);
    }
    
    assert(counter<Number>::count() == initial_count);
    
    std::cout << "Test 3: Basic counter test passed\n";
}

void test_counter_advanced() {
    // Тест 4: Продвинутая проверка счетчика с копированием и перемещением
    const size_t initial_count = counter<Number>::count();
    
    Number original(100);
    assert(counter<Number>::count() == initial_count + 1);

    // Тестирование копирования
    Number copy = original;
    assert(counter<Number>::count() == initial_count + 2);

    // Тестирование перемещения
    Number moved = std::move(original);
    assert(counter<Number>::count() == initial_count + 3);

    // Тестирование в контейнерах
    {
        std::vector<Number> numbers;
        numbers.emplace_back(1);
        numbers.emplace_back(2);
        assert(counter<Number>::count() == initial_count + 5);
    }
    
    assert(counter<Number>::count() == initial_count + 3);
    
    std::cout << "Test 4: Advanced counter test passed\n";
}

int main() {
    test_comparison_operators();
    test_edge_cases();
    test_counter_basic();
    test_counter_advanced();
    
    std::cout << "\nAll mixin tests passed successfully!\n";
    return 0;
}