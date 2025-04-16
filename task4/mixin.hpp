#include <iostream>
#include <cassert>

// MixIn для операторов сравнения
template <typename Derived>
class less_than_comparable {
public:
    friend bool operator>(const Derived& lhs, const Derived& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Derived& lhs, const Derived& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs) && !(rhs < lhs);
    }

    friend bool operator!=(const Derived& lhs, const Derived& rhs) {
        return !(lhs == rhs);
    }
};

// MixIn для подсчета экземпляров
template <typename Counted>
class counter {
protected:
    counter() { ++count_; }
    ~counter() { --count_; }
    
    counter(const counter&) { ++count_; }
    counter(counter&&) { ++count_; }

public:
    static size_t count() { return count_; }

private:
    static inline size_t count_ = 0;
};
