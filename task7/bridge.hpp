#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
#include <algorithm>

// Абстрактная реализация
class SetImpl {
public:
    virtual ~SetImpl() = default;
    virtual bool addImpl(int element) = 0;
    virtual bool removeImpl(int element) = 0;
    virtual bool containsImpl(int element) const = 0;
    virtual std::vector<int> getAllElementsImpl() const = 0;
    virtual size_t sizeImpl() const = 0;
    virtual std::unique_ptr<SetImpl> cloneImpl() const = 0;
};

// Конкретная реализация для малого количества элементов (массив)
class ArraySetImpl : public SetImpl {
public:
    bool addImpl(int element) override {
        if (std::find(data.begin(), data.end(), element) != data.end())
            return false;
        
        data.push_back(element);
        return true;
    }

    bool removeImpl(int element) override {
        auto it = std::remove(data.begin(), data.end(), element);
        if (it == data.end()) return false;
        
        data.erase(it, data.end());
        return true;
    }

    bool containsImpl(int element) const override {
        return std::find(data.begin(), data.end(), element) != data.end();
    }

    std::vector<int> getAllElementsImpl() const override {
        return data;
    }

    size_t sizeImpl() const override {
        return data.size();
    }

    std::unique_ptr<SetImpl> cloneImpl() const override {
        return std::make_unique<ArraySetImpl>(*this);
    }

private:
    std::vector<int> data;
};

// Конкретная реализация для большого количества элементов (хэш-таблица)
class HashSetImpl : public SetImpl {
public:
    bool addImpl(int element) override {
        return data.insert(element).second;
    }

    bool removeImpl(int element) override {
        return data.erase(element) > 0;
    }

    bool containsImpl(int element) const override {
        return data.count(element) > 0;
    }

    std::vector<int> getAllElementsImpl() const override {
        return {data.begin(), data.end()};
    }

    size_t sizeImpl() const override {
        return data.size();
    }

    std::unique_ptr<SetImpl> cloneImpl() const override {
        return std::make_unique<HashSetImpl>(*this);
    }

private:
    std::unordered_set<int> data;
};

// Абстракция - класс Множество
class Set {
public:
    Set() : impl(std::make_unique<ArraySetImpl>()) {}

    void add(int element) {
        checkAndMigrate(1);
        impl->addImpl(element);
        checkAndMigrate(-1);
    }

    bool remove(int element) {
        bool result = impl->removeImpl(element);
        checkAndMigrate(-1);
        return result;
    }

    bool contains(int element) const {
        return impl->containsImpl(element);
    }

    size_t size() const {
        return impl->sizeImpl();
    }

    Set unionWith(const Set& other) const {
        Set result;
        for (auto&& e : getAllElements()) result.add(e);
        for (auto&& e : other.getAllElements()) result.add(e);
        return result;
    }

    Set intersection(const Set& other) const {
        Set result;
        for (auto&& e : getAllElements()) {
            if (other.contains(e)) {
                result.add(e);
            }
        }
        return result;
    }

private:
    static constexpr size_t SWITCH_THRESHOLD = 10;
    std::unique_ptr<SetImpl> impl;

    std::vector<int> getAllElements() const {
        return impl->getAllElementsImpl();
    }

    void checkAndMigrate(int delta) {
        const size_t new_size = size() + delta;
        const bool should_switch = 
            (dynamic_cast<ArraySetImpl*>(impl.get()) && new_size > SWITCH_THRESHOLD) ||
            (dynamic_cast<HashSetImpl*>(impl.get()) && new_size <= SWITCH_THRESHOLD);

        if (should_switch) {
            auto elements = getAllElements();
            if (new_size > SWITCH_THRESHOLD) {
                impl = std::make_unique<HashSetImpl>();
            } else {
                impl = std::make_unique<ArraySetImpl>();
            }
            for (auto&& e : elements) impl->addImpl(e);
        }
    }
};
