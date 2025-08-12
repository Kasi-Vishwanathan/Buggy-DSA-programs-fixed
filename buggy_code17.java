package com.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class BuggyCode17 {
    public static void main(String[] args) {
        BuggyCode17 bc = new BuggyCode17();
        bc.processData();

        // Properly handle scanner resource
        Scanner scanner = new Scanner(System.in);
        System.out.println("Press enter to exit...");
        scanner.nextLine();
        scanner.close();
    }

    public void processData() {
        List<Integer> numbers = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            numbers.add(i);
        }

        List<Integer> processed = processNumbers(numbers);
        printList(processed);
    }

    private List<Integer> processNumbers(List<Integer> list) {
        List<Integer> result = new ArrayList<>();
        for (Integer original : list) {
            int value = original * 2;
            result.add(value);
            if (original % 2 == 0) {
                result.add(value + 1);
            }
        }
        return result;
    }

    public static void printList(List<Integer> list) {
        for (Integer num : list) {
            System.out.println(num);
        }
    }
}