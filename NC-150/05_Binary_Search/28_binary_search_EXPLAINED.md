# Binary Search (LeetCode #704)

## Problem Statement

Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with **O(log n)** runtime complexity.

### Examples

```
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums
```

### Constraints
- 1 <= nums.length <= 10^4
- -10^4 < nums[i], target < 10^4
- All integers in nums are unique
- nums is sorted in ascending order

## Intuition

Binary search works by repeatedly dividing the search interval in half:
1. Start with the entire array
2. Compare target with middle element
3. If equal, found it!
4. If target is greater, search right half
5. If target is smaller, search left half
6. Repeat until found or interval is empty

## Approach

### Iterative Algorithm

```
1. Initialize left = 0, right = n - 1
2. While left <= right:
   a. mid = left + (right - left) / 2
   b. If nums[mid] == target: return mid
   c. If nums[mid] < target: left = mid + 1
   d. Else: right = mid - 1
3. Return -1 (not found)
```

## Visual Walkthrough

### Example: nums = [-1, 0, 3, 5, 9, 12], target = 9

```
Step 1:
[-1, 0, 3, 5, 9, 12]
  ↑        ↑      ↑
 left     mid   right

mid = 2, nums[2] = 3 < 9
→ left = mid + 1 = 3

Step 2:
[-1, 0, 3, 5, 9, 12]
           ↑  ↑   ↑
         left mid right

mid = 4, nums[4] = 9 == 9
→ Found! Return 4
```

### Example: target = 2 (not found)

```
Step 1: mid=2, nums[2]=3 > 2 → right = 1
Step 2: mid=0, nums[0]=-1 < 2 → left = 1
Step 3: mid=1, nums[1]=0 < 2 → left = 2
Step 4: left=2 > right=1 → Not found, return -1
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why |
|-----------|---------------|-----------------|-----|
| Single element, found | `[5], target=5` | `0` | Only element matches |
| Single element, not found | `[5], target=3` | `-1` | Only element doesn't match |
| First element | `[1,2,3], target=1` | `0` | At left boundary |
| Last element | `[1,2,3], target=3` | `2` | At right boundary |
| Target too small | `[2,3,4], target=1` | `-1` | Less than all elements |
| Target too large | `[2,3,4], target=5` | `-1` | Greater than all elements |

## Complexity Analysis

- **Time Complexity**: O(log n)
  - Each iteration halves the search space
  - After k iterations: n/2^k = 1 → k = log₂(n)
  
- **Space Complexity**: O(1) iterative, O(log n) recursive
  - Iterative uses constant extra space
  - Recursive has O(log n) call stack depth

## Common Mistakes

1. **Integer overflow**: Use `mid = left + (right - left) / 2` instead of `(left + right) / 2`
2. **Wrong condition**: `left <= right` for this template, not `left < right`
3. **Wrong update**: `left = mid + 1` and `right = mid - 1`, not `left = mid`
4. **Infinite loop**: Ensure left or right changes each iteration

## Why `mid = left + (right - left) / 2`?

```
If left = 2,000,000,000 and right = 2,000,000,000
(left + right) = 4,000,000,000 → Integer overflow!

left + (right - left) / 2 = 2,000,000,000 + 0 = 2,000,000,000 ✓
```

## Related Problems

- [Search Insert Position](https://leetcode.com/problems/search-insert-position/)
- [First Bad Version](https://leetcode.com/problems/first-bad-version/)
- [Search a 2D Matrix](02_search_2d_matrix_EXPLAINED.md)

## Key Takeaways

1. **Binary search requires sorted data**: Can't use on unsorted arrays
2. **Halving is logarithmic**: O(log n) is very efficient
3. **Template matters**: Slight variations for different use cases
4. **Prevent overflow**: Use `left + (right - left) / 2`
5. **Foundation for harder problems**: Master this before variants

