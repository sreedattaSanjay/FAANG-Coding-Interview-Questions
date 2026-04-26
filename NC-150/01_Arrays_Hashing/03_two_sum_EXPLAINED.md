# Two Sum (LeetCode #1)

## Problem Statement

Given an array of integers `nums` and an integer `target`, return **indices** of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may **not use the same element twice**.

You can return the answer in any order.

### Examples

```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9

Input: nums = [3,2,4], target = 6
Output: [1,2]

Input: nums = [3,3], target = 6
Output: [0,1]
```

### Constraints
- 2 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
- -10^9 <= target <= 10^9
- Only one valid answer exists

## Intuition

For each number `num`, we need to find if `target - num` (the **complement**) exists in the array.

**Brute force**: Check all pairs → O(n²)

**Optimization**: Use a hash map to store numbers we've seen. For each new number, check if its complement is already in the map → O(n)

Key insight: **We're trading space for time** by using a hash map.

## Approach

### Approach 1: One-Pass Hash Map (Optimal)

```
1. Create empty hash map: number → index
2. For each element at index i:
   a. Calculate complement = target - nums[i]
   b. If complement exists in map → return [map[complement], i]
   c. Add nums[i] → i to map
3. Return empty (shouldn't happen per problem guarantee)
```

Why one-pass works: When we find a match, we've already seen and stored the complement earlier.

### Approach 2: Two-Pass Hash Map

```
1. First pass: Build map of all number → index
2. Second pass: For each number, look for complement
   - Make sure complement index != current index
```

### Approach 3: Brute Force

```
1. For each element i from 0 to n-1:
   2. For each element j from i+1 to n-1:
      - If nums[i] + nums[j] == target → return [i, j]
```

## Visual Walkthrough

### Example: nums = [2, 7, 11, 15], target = 9

```
Hash Map: {}

i=0, num=2:
  complement = 9 - 2 = 7
  7 not in map
  map = {2: 0}

i=1, num=7:
  complement = 9 - 7 = 2
  2 IS in map at index 0!
  Return [0, 1] ✓
```

### Example: nums = [3, 2, 4], target = 6

```
Hash Map: {}

i=0, num=3:
  complement = 6 - 3 = 3
  3 not in map
  map = {3: 0}

i=1, num=2:
  complement = 6 - 2 = 4
  4 not in map
  map = {3: 0, 2: 1}

i=2, num=4:
  complement = 6 - 4 = 2
  2 IS in map at index 1!
  Return [1, 2] ✓
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Two elements | `[3,3], target=6` | `[0,1]` | Same value, different indices |
| Negative numbers | `[-1,2], target=1` | `[0,1]` | Complements can be negative |
| Zero target | `[0,0], target=0` | `[0,1]` | 0 + 0 = 0 is valid |
| Large numbers | `[10^9, -10^9], target=0` | `[0,1]` | Handle integer range |
| Non-adjacent | `[1,5,3,4], target=8` | `[1,2]` or `[0,3]` | Answer not always adjacent |
| Negative target | `[-3,-2], target=-5` | `[0,1]` | Negative + negative |

## Complexity Analysis

### One-Pass Hash Map
- **Time Complexity**: O(n)
  - Single iteration through the array
  - Hash map lookup and insertion are O(1) average
  
- **Space Complexity**: O(n)
  - In worst case, store n-1 elements before finding answer

### Brute Force
- **Time Complexity**: O(n²)
  - Nested loops checking all pairs
  
- **Space Complexity**: O(1)
  - No extra space needed

## Common Mistakes

1. **Using same element twice**: `nums = [3], target = 6` → Can't use index 0 twice
2. **Returning values instead of indices**: Problem asks for indices, not the numbers
3. **Not handling duplicates**: `[3,3], target=6` has two 3's at different indices
4. **Two-pass: forgetting index check**: Must ensure `complement_index != current_index`

## Related Problems

- [Two Sum II - Sorted Array](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) - Two pointers approach
- [3Sum](https://leetcode.com/problems/3sum/) - Extension to three numbers
- [4Sum](https://leetcode.com/problems/4sum/) - Extension to four numbers
- [Two Sum III - Data Structure Design](https://leetcode.com/problems/two-sum-iii-data-structure-design/)

## Key Takeaways

1. **Hash map for complement lookup**: Classic pattern for pair-sum problems
2. **One-pass is often possible**: Check before insert in same loop
3. **Trade space for time**: O(n) space gives O(n) time vs O(1) space with O(n²) time
4. **This is THE most common interview question**: Master it completely!
5. **Follow-up variations**: 
   - What if array is sorted? → Use two pointers
   - What if we need all pairs? → Modify to collect all results
   - What if duplicates allowed in answer? → Different counting approach

