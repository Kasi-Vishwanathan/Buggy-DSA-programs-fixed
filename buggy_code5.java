package com.example;

import java.util.ArrayList;
import java.util.List;

public class buggy_code5 {
    public static void main(String[] args) {
        for (int i = 1; i <= 10; i++) {
            System.out.println("Number: " + i);
        }
        List<Integer> numbers = new ArrayList<>();
        numbers.add(5);
        System.out.println("Number added: " + numbers.get(0));
    }
}