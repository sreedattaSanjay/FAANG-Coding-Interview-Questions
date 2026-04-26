# Contains Duplicate (LeetCode #217)

## Problem Statement

Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

### Examples

```
Input: nums = [1,2,3,1]
Output: true
Explanation: 1 appears twice

Input: nums = [1,2,3,4]
Output: false
Explanation: All elements are distinct

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

### Constraints
- 1 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9

## Intuition

The key insight is that we need to efficiently check if we've seen an element before. This is a classic use case for a **Hash Set**:
- Hash Set provides O(1) average-time lookups
- As we iterate through the array, we check if the current element exists in our set
- If it does, we found a duplicate; if not, we add it to the set

## Approach

### Approach 1: Hash Set (Optimal)

```
1. Create an empty hash set
2. For each number in the array:
   a. If number exists in set → return true (duplicate found)
   b. Otherwise, add number to set
3. Return false (no duplicates found)
```

### Approach 2: Sorting

```
1. Sort the array
2. Check adjacent elements for equality
3. If any two adjacent elements are equal → duplicate found
```

### Approach 3: Set Size Comparison

```
1. Convert array to set (removes duplicates)
2. If set size < array size → duplicates existed
```

## Visual Walkthrough

### Example: nums = [1, 2, 3, 1]

```
Step 1: seen = {}
        Check 1: not in seen
        seen = {1}

Step 2: seen = {1}
        Check 2: not in seen
        seen = {1, 2}

Step 3: seen = {1, 2}
        Check 3: not in seen
        seen = {1, 2, 3}

Step 4: seen = {1, 2, 3}
        Check 1: 1 IS in seen!
        Return TRUE
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty array | `[]` | `false` | No elements means no duplicates |
| Single element | `[1]` | `false` | Can't have duplicate with one element |
| Two same elements | `[1, 1]` | `true` | Minimum case for duplicate |
| All same elements | `[5, 5, 5, 5]` | `true` | Many duplicates |
| All unique | `[1, 2, 3, 4, 5]` | `false` | No duplicates exist |
| Negative numbers | `[-1, -1]` | `true` | Negatives can duplicate too |
| Large range | `[-10^9, 10^9]` | `false` | Handle integer range |

## Complexity Analysis

### Hash Set Approach
- **Time Complexity**: O(n)
  - We iterate through the array once
  - Each hash set operation (lookup/insert) is O(1) average
  - Total: n * O(1) = O(n)
  
- **Space Complexity**: O(n)
  - In worst case (no duplicates), we store all n elements in the set

### Sorting Approach
- **Time Complexity**: O(n log n)
  - Sorting dominates the complexity
  - Checking adjacent elements is O(n)
  
- **Space Complexity**: O(1) or O(n)
  - Depends on sorting algorithm
  - In-place sort: O(1), otherwise O(n)

## Common Mistakes

1. **Not handling empty array**: Always check if the input could be empty
2. **Using nested loops**: O(n²) brute force is too slow for large inputs
3. **Modifying input**: Sorting changes the original array (may not be allowed)
4. **Off-by-one in sorting check**: Start loop from index 1, not 0

## Related Problems

- [Two Sum](03_two_sum_EXPLAINED.md) - Uses hash map for complement lookup
- [Valid Anagram](02_valid_anagram_EXPLAINED.md) - Uses hash map for character counting
- [Single Number](https://leetcode.com/problems/single-number/) - Find the non-duplicate

## Key Takeaways

1. **Hash Set for membership testing**: O(1) lookup is your friend
2. **Trade space for time**: Using extra O(n) space gives us O(n) time
3. **Consider alternatives**: Sorting is valid if O(n log n) is acceptable
4. **Pythonic solutions**: `len(set(nums)) < len(nums)` is clean and readable

