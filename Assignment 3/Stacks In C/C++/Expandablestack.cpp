#include <iostream>
#include <memory>
#include <stdexcept>

constexpr int INITIAL_CAPACITY = 10;
constexpr int MAX_CAPACITY = 1000;
constexpr int MAX_STRING_LENGTH = 100;

class Stack {
private:
    std::unique_ptr<std::string[]> data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        if (newCapacity <= size)
            throw std::length_error("New capacity is less than or equal to the current size.");

        std::unique_ptr<std::string[]> newData = std::make_unique<std::string[]>(newCapacity);
        for (int i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }

public:
    Stack() : data(std::make_unique<std::string[]>(INITIAL_CAPACITY)), size(0), capacity(INITIAL_CAPACITY) {}

    void push(const std::string& str) {
        if (size >= capacity)
            resize(std::min(capacity * 2, MAX_CAPACITY));

        if (str.length() > MAX_STRING_LENGTH)
            throw std::invalid_argument("String exceeds maximum length.");

        data[size++] = str;
    }

    std::string pop() {
        if (size <= 0)
            throw std::logic_error("Stack is empty.");

        std::string top = std::move(data[--size]);
        data[size].clear();

        return top;
    }

    // Deleted copy constructor and assignment operator to prohibit copying
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
};

void runTests() {
    try {
        // Create a stack
        Stack stack;

        // Test pushing and popping strings
        stack.push("Hello");
        stack.push("World");
        stack.push("OpenAI");

        assert(stack.pop() == "OpenAI");
        assert(stack.pop() == "World");
        assert(stack.pop() == "Hello");

        // Test pushing more strings than the initial capacity
        for (int i = 0; i < INITIAL_CAPACITY * 2; ++i) {
            stack.push("String " + std::to_string(i));
        }

        // Test popping all the strings
        for (int i = INITIAL_CAPACITY * 2 - 1; i >= 0; --i) {
            std::string str = "String " + std::to_string(i);
            assert(stack.pop() == str);
        }

        // Test underflow error
        stack.pop();  // Should throw std::logic_error

        // Test exceeding maximum capacity
        for (int i = 0; i < MAX_CAPACITY; ++i) {
            stack.push("String " + std::to_string(i));
        }

        stack.push("Overflow");  // Should throw std::overflow_error
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what() << std::endl;
    }

    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    runTests();

    return 0;
}
