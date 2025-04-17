#include "bridge.hpp"

int main() {
    Set s;
    for (int i = 1; i <= 15; ++i) {
        s.add(i);
        std::cout << "Added " << i << ", size: " << s.size() 
                  << ", using " << (i <= 10 ? "array" : "hash") << std::endl;
    }

    Set s2;
    s2.add(10);
    s2.add(15);
    s2.add(20);

    auto unionSet = s.unionWith(s2);
    auto intersectionSet = s.intersection(s2);

    std::cout << "Union size: " << unionSet.size() << std::endl;
    std::cout << "Intersection size: " << intersectionSet.size() << std::endl;

    return 0;
}