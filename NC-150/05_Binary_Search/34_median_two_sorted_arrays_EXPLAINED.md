# Median of Two Sorted Arrays (LeetCode #4)

## Problem Statement

Given two sorted arrays `nums1` and `nums2`, find the median of the combined sorted array in O(log(m+n)) time.

## Intuition

Instead of merging arrays (O(m+n)), we can binary search for the correct partition point:
- Partition both arrays so left parts combined have half the elements
- Elements in left parts must all be ≤ elements in right parts

## Approach

1. Binary search on smaller array (for efficiency)
2. For partition `i` in nums1, partition `j = half - i` in nums2
3. Check if partition is valid (all left ≤ all right)
4. Calculate median based on odd/even total length

## Key Formula

```
half = (m + n + 1) / 2
j = half - i

Valid partition:
nums1[i-1] <= nums2[j] AND nums2[j-1] <= nums1[i]
```

## Complexity

- **Time**: O(log(min(m,n)))
- **Space**: O(1)

## Key Takeaways

1. Binary search on partition, not values
2. Search on smaller array for efficiency
3. Use ±infinity for boundary conditions
4. Classic hard interview problem

