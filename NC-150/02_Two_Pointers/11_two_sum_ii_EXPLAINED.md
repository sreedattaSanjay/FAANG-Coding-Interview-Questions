# Two Sum II - Input Array Is Sorted (LeetCode #167)

## Problem Statement

Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number.

Return the indices of the two numbers, `index1` and `index2`, **added by one** as an integer array `[index1, index2]`.

The tests are generated such that there is **exactly one solution**.

### Examples

```
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: 2 + 7 = 9. Indices are 1 and 2 (1-indexed).

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: 2 + 4 = 6. Indices are 1 and 3.

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: -1 + 0 = -1. Indices are 1 and 2.
```

### Constraints
- 2 <= numbers.length <= 3 * 10^4
- -1000 <= numbers[i] <= 1000
- numbers is sorted in non-decreasing order
- -1000 <= target <= 1000
- Exactly one solution exists
- Cannot use the same element twice

## Intuition

Unlike the original Two Sum problem, the array is **sorted**. This allows us to use **two pointers** instead of a hash map.

**Key insight**: With pointers at both ends of a sorted array:
- If `sum < target`: Move left pointer right (increases sum)
- If `sum > target`: Move right pointer left (decreases sum)
- If `sum == target`: Found the answer!

This works because we can always make progress toward the target by choosing the correct pointer to move.

## Approach

### Approach 1: Two Pointers (Optimal)

```
1. Initialize left = 0, right = n - 1
2. While left < right:
   a. Calculate sum = numbers[left] + numbers[right]
   b. If sum == target: return [left + 1, right + 1]
   c. If sum < target: left++ (need bigger sum)
   d. If sum > target: right-- (need smaller sum)
```

### Approach 2: Binary Search

```
1. For each element at index i:
   a. Calculate complement = target - numbers[i]
   b. Binary search for complement in [i+1, n-1]
   c. If found, return indices
```

## Visual Walkthrough

### Example: numbers = [2, 7, 11, 15], target = 9

```
Initial:
[2, 7, 11, 15]
 ↑          ↑
left      right

Sum = 2 + 15 = 17 > 9
→ Move right pointer left

[2, 7, 11, 15]
 ↑      ↑
left  right

Sum = 2 + 11 = 13 > 9
→ Move right pointer left

[2, 7, 11, 15]
 ↑  ↑
left right

Sum = 2 + 7 = 9 == 9
→ Found! Return [1, 2] (1-indexed)
```

### Why Two Pointers Work on Sorted Arrays

```
Given sorted array and target sum:

If current_sum < target:
  - Moving left pointer right → guaranteed to increase sum
  - Moving right pointer left → would decrease sum (wrong direction)
  
If current_sum > target:
  - Moving right pointer left → guaranteed to decrease sum
  - Moving left pointer right → would increase sum (wrong direction)

Therefore, we always make progress toward the target!
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Two elements | `[2,7], target=9` | `[1,2]` | Minimal case |
| Same elements | `[3,3], target=6` | `[1,2]` | Works fine |
| Negative + Positive | `[-1,1], target=0` | `[1,2]` | Cross zero |
| All negative | `[-3,-1], target=-4` | `[1,2]` | Negative sum |
| First and last | `[1,2,3,4], target=5` | `[1,4]` | Max distance |
| Adjacent | `[1,2,3,4], target=3` | `[1,2]` | Min distance |

## Complexity Analysis

### Two Pointers
- **Time Complexity**: O(n)
  - Each pointer moves at most n times
  - Total moves ≤ 2n
  
- **Space Complexity**: O(1)
  - Only two pointers

### Binary Search
- **Time Complexity**: O(n log n)
  - n iterations, each with O(log n) binary search
  
- **Space Complexity**: O(1)
  - No extra space needed

### Comparison with Original Two Sum

| Aspect | Two Sum (unsorted) | Two Sum II (sorted) |
|--------|-------------------|---------------------|
| Time | O(n) | O(n) |
| Space | O(n) | O(1) |
| Technique | Hash Map | Two Pointers |

## Common Mistakes

1. **0-indexed vs 1-indexed**: Problem asks for 1-indexed result
2. **Moving wrong pointer**: Always move the pointer that helps reach target
3. **Using extra space**: This problem specifically asks for O(1) space
4. **Not leveraging sorted property**: Hash map works but wastes the sorted guarantee

## Related Problems

- [Two Sum](../01_Arrays_Hashing/03_two_sum_EXPLAINED.md) - Unsorted version with hash map
- [3Sum](03_three_sum_EXPLAINED.md) - Extend to three numbers
- [Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)

## Key Takeaways

1. **Sorted arrays enable two pointers**: No need for extra space
2. **Move pointer strategically**: Based on whether sum is too small or too large
3. **Constant space is possible**: Because array is sorted
4. **1-indexed output**: Read problem carefully for index format
5. **This is a building block**: Same technique used in 3Sum, 4Sum, etc.

