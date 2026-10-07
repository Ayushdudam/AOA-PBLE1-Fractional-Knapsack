# AOA PBLE 1 – Smart Delivery Planning: Fractional Knapsack

**Student:** Ayush Dudam  
**Roll No.:** 25102B0079  
**Branch:** CMPN B – Computer Engineering  
**Subject:** Analysis of Algorithm

## Problem Statement

Develop a menu-driven C program to solve the **Fractional Knapsack** problem for smart delivery planning. Each package has a value and weight. The program calculates the value/weight ratio, sorts packages in decreasing order of ratio, and selects complete packages first, taking a fraction of a package only when necessary to fill the delivery capacity.

## Menu

1. Enter Package Details
2. Display Package Details
3. Calculate Value/Weight Ratio
4. Sort Packages by Ratio
5. Find Maximum Value
6. Display Selected Packages
7. Exit

## Algorithm

1. Read package value, weight, and delivery capacity.
2. Calculate `value / weight` for every package.
3. Sort packages by ratio in decreasing order using Bubble Sort.
4. Traverse the sorted packages.
5. If a package fits completely, take the whole package.
6. Otherwise, take the fraction that fits in the remaining capacity.
7. Report selected fractions, total weight, and maximum value.

## Complexity

- Ratio calculation: **O(n)**
- Bubble sort: **O(n²)** worst-case time
- Greedy selection: **O(n)** after sorting
- Overall time complexity: **O(n²)**
- Auxiliary space: **O(1)** apart from the package array

## Sample Test Case

| Package | Value | Weight | Ratio |
|---|---:|---:|---:|
| 1 | 40 | 5 | 8.00 |
| 2 | 30 | 10 | 3.00 |
| 3 | 50 | 5 | 10.00 |
| 4 | 20 | 4 | 5.00 |

Capacity = **15**

Sorted order: **Package 3 → Package 1 → Package 4 → Package 2**

Selection:
- Package 3: 1.00 fraction, weight 5, value 50
- Package 1: 1.00 fraction, weight 5, value 40
- Package 4: 1.00 fraction, weight 4, value 20
- Package 2: 0.10 fraction, weight 1, value 3

Total weight = **15**  
Maximum value = **113.00**

## Compilation

```bash
gcc fractional_knapsack.c -o fractional_knapsack
./fractional_knapsack
```

## Repository

GitHub: https://github.com/Ayushdudam/AOA-PBLE1-Fractional-Knapsack
