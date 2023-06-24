import java.util.Arrays;

public class Stack {
    private static final int INITIAL_CAPACITY = 10;
    private static final int MAX_CAPACITY = 1000;
    private static final int MAX_STRING_SIZE = 100;

    private String[] elements;
    private int top;

    public Stack() {
        elements = new String[INITIAL_CAPACITY];
        top = -1;
    }

    public void push(String str) {
        if (str.getBytes().length > MAX_STRING_SIZE) {
            throw new IllegalArgumentException("String size exceeds the maximum limit.");
        }

        if (top == elements.length - 1) {
            if (elements.length >= MAX_CAPACITY) {
                throw new IllegalStateException("Stack capacity reached the maximum limit.");
            }

            expandCapacity();
        }

        elements[++top] = str;
    }

    public String pop() {
        if (top == -1) {
            throw new IllegalStateException("Stack is empty.");
        }

        String popped = elements[top];
        elements[top--] = null;

        return popped;
    }

    private void expandCapacity() {
        int newCapacity = Math.min(elements.length * 2, MAX_CAPACITY);
        elements = Arrays.copyOf(elements, newCapacity);
    }

    public static void main(String[] args) {
        try {
            Stack stack = new Stack();

            stack.push("Hello");
            stack.push("World");
            stack.push("OpenAI");

            System.out.println("Popped string: " + stack.pop());
            System.out.println("Popped string: " + stack.pop());
            System.out.println("Popped string: " + stack.pop());
            System.out.println("Popped string: " + stack.pop()); // Throws IllegalStateException
        } catch (Exception ex) {
            System.err.println("Exception occurred: " + ex.getMessage());
        }
    }
}
