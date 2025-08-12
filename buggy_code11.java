package com.example;

import java.util.Arrays;
import java.util.List;

public class BuggyCode11 {

    public static void main(String[] args) {
        BuggyCode11 instance = new BuggyCode11();
        instance.processNumbers();
        instance.processUser();
    }

    public void processNumbers() {
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5);
        int sum = 0;
        for (Integer num : numbers) {
            sum += num;
            System.out.println("Sum: " + sum);
        }
    }

    public void processUser() {
        User user = new User("John", 30);
        if (user.getName().equals("John") && user.getAge() > 25) {
            System.out.println("User validated");
        } else if (user.getName().equals("John") || user.getAge() > 25) {
            System.out.println("Partial validation");
        } else {
            System.out.println("User invalid");
        }
    }

    private static class User {
        private final String name;
        private final int age;

        public User(String name, int age) {
            this.name = name;
            this.age = age;
        }

        public String getName() {
            return name;
        }

        public int getAge() {
            return age;
        }
    }
}