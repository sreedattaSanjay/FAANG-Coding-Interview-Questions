# Search a 2D Matrix (LeetCode #74)

## Problem Statement

You are given an `m x n` integer matrix `matrix` with the following properties:
- Each row is sorted in non-decreasing order.
- The first integer of each row is greater than the last integer of the previous row.

Given an integer `target`, return `true` if `target` is in `matrix` or `false` otherwise.

### Examples

```
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
```

## Intuition

Since the matrix is sorted row by row and each row's first element is greater than the previous row's last element, the entire matrix can be viewed as a **single sorted 1D array**.

**Key insight**: Convert 2D index to 1D and back:
- 1D index `i` → 2D: `row = i / n, col = i % n`
- 2D `(row, col)` → 1D: `i = row * n + col`

## Approach

### Treat as 1D Array

```
1. Let total = m * n elements
2. Binary search on indices 0 to total - 1
3. Convert mid index to (row, col)
4. Compare matrix[row][col] with target
```

## Visual Walkthrough

```
Matrix:
[[ 1,  3,  5,  7],
 [10, 11, 16, 20],
 [23, 30, 34, 60]]

As 1D: [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
Index:  0  1  2  3   4   5   6   7   8   9  10  11

For mid = 5:
row = 5 / 4 = 1
col = 5 % 4 = 1
matrix[1][1] = 11
```

## Complexity Analysis

- **Time**: O(log(m×n))
- **Space**: O(1)

## Key Takeaways

1. **Flatten to 1D conceptually**: No actual array creation needed
2. **Index conversion**: `mid / n` for row, `mid % n` for col
3. **Same as regular binary search**: Just with index mapping

