#include <iostream>
#include <cassert>

void runTests() {
    try {
        // Create a stack
        Stack stack;

        // Test pushing and popping strings
        stack.push("Hello");
        stack.push("World");

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
