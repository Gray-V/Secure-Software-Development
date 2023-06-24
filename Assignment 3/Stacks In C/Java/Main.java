public class Main {
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
