package com.example;

import java.util.ArrayList;
import java.util.List;

public class BuggyCode20 {
    public static void main(String[] args) {
        List<Integer> numbers = new ArrayList<>();
        for (int i = 1; i <= 5; i++) {
            numbers.add(i);
        }
        int sum = sumEvenNumbers(numbers);
        System.out.println("Sum of even numbers: " + sum);
    }

    public static int sumEvenNumbers(List<Integer> numbers) {
        int sum = 0;
        for (int num : numbers) {
            if (num % 2 == 0) {
                sum += num;
            }
        }
        return sum;
    }
}