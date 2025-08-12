package com.example;

public class BuggyCode3 {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        
        // Calculate sum using enhanced for-loop to avoid index errors
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        System.out.println("Sum: " + sum);
        
        printMessage("Hello");
        
        // Corrected variable type to double for accurate average calculation
        double average = calculateAverage(numbers);
        System.out.println("Average: " + average);
        
        // Check if average is negative (handles cases with possible negative values)
        if (average < 0) {
            System.out.println("Average is negative!");
        } else {
            System.out.println("Average is positive!");
        }
    }
    
    // Fixed parameter name typo (message -> msg)
    public static void printMessage(String msg) {
        System.out.println(msg);
    }
    
    // Corrected average calculation with division handling and type casting
    public static double calculateAverage(int[] numbers) {
        if (numbers.length == 0) {
            return 0.0; // Handle empty array case to prevent division by zero
        }
        int sum = 0;
        for (int num : numbers) { // Enhanced for-loop for readability and safety
            sum += num;
        }
        return (double) sum / numbers.length; // Ensure floating-point division
    }
}