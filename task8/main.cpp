#include "factory.hpp"

int main() {
    ExpressionFactory factory;
    
    auto c = factory.createConstant(2);
    auto v = factory.createVariable("x");
    auto expr = std::make_shared<Addition>(c, std::make_shared<Addition>(c,v));
    
    std::map<std::string, double> context{{"x", 3}};
    
    std::cout << "Expression: ";
    expr->print();
    std::cout << "\nResult: " << expr->calculate(context) << std::endl;

    return 0;
}