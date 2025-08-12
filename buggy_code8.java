package com.example;

import java.util.ArrayList;
import java.util.List;

public class BuggyCode8 {
    public static void main(String[] args) {
        int x = 5;
        int y = 1; // Corrected divisor to prevent division by zero
        System.out.println("Result: " + (x / y));

        for (int i = 0; i < 10; i++) { // Removed redundant increment in loop body
            if (i % 2 == 0) {
                System.out.println(i + " is even");
            } else {
                System.out.println(i + " is odd");
            }
        }

        List<Integer> numbers = new ArrayList<>(); // Added generics for type safety
        numbers.add(5); // Corrected to add Integer instead of String
        for (Integer num : numbers) {
            System.out.println("Number: " + num);
        }

        doSomething(); // No exception handling needed as method no longer throws
    }

    public static void doSomething() { // Removed redundant throws declaration
        // Method implementation (if any)
    }
}