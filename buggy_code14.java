package com.example;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class BuggyCode14 {
    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5));
        
        // Modify even numbers
        for (int i = 0; i < list.size(); i++) {
            int element = list.get(i);
            if (element % 2 == 0) {
                int newValue = element * 2 + 100;
                list.set(i, newValue);
                System.out.println("Modified value: " + newValue);
            }
        }
        
        // Remove odd numbers
        Iterator<Integer> it = list.iterator();
        while (it.hasNext()) {
            if (it.next() % 2 != 0) {
                it.remove();
            }
        }
        
        System.out.println("Final list: " + list);
    }
}