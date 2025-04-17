#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Базовый класс выражения
class Expression {
public:
    virtual ~Expression() = default;
    virtual double calculate(const std::map<std::string, double>& context) const = 0;
    virtual void print() const = 0;
};

// Класс константы
class Constant : public Expression {
    int value;
    explicit Constant(int val) : value(val) {}
    friend class ExpressionFactory;

public:
    double calculate(const std::map<std::string, double>&) const override {
        return value;
    }

    void print() const override {
        std::cout << value;
    }
};

// Класс переменной
class Variable : public Expression {
    std::string name;
    explicit Variable(std::string var) : name(std::move(var)) {}
    friend class ExpressionFactory;

public:
    double calculate(const std::map<std::string, double>& context) const override {
        return context.at(name);
    }

    void print() const override {
        std::cout << name;
    }
};

// Класс сложения
class Addition : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    Addition(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    double calculate(const std::map<std::string, double>& context) const override {
        return left->calculate(context) + right->calculate(context);
    }

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " + ";
        right->print();
        std::cout << ")";
    }
};

// Фабрика выражений
class ExpressionFactory {
    std::map<int, std::shared_ptr<Constant>> constants;
    std::map<std::string, std::shared_ptr<Variable>> variables;
    std::vector<std::shared_ptr<Constant>> precreated;

public:
    ExpressionFactory() {
        // Предварительное создание констант от -5 до 256
        for (int i = -5; i <= 256; ++i) {
            precreated.emplace_back(new Constant(i));
            constants[i] = precreated.back();
        }
    }

    std::shared_ptr<Constant> createConstant(int value) {
        if (value < -5 || value > 256) {
            if (auto it = constants.find(value); it != constants.end()) {
                return it->second;
            }
            auto ptr = std::shared_ptr<Constant>(new Constant(value));
            constants[value] = ptr;
            return ptr;
        }
        return constants[value];
    }

    std::shared_ptr<Variable> createVariable(const std::string& name) {
        if (auto it = variables.find(name); it != variables.end()) {
            return it->second;
        }
        auto ptr = std::shared_ptr<Variable>(new Variable(name));
        variables[name] = ptr;
        return ptr;
    }
};
