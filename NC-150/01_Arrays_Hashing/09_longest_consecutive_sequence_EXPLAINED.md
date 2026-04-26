# Longest Consecutive Sequence (LeetCode #128)

## Problem Statement

Given an unsorted array of integers `nums`, return the length of the **longest consecutive elements sequence**.

You must write an algorithm that runs in **O(n) time**.

### Examples

```
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive sequence is [1, 2, 3, 4]. Length = 4.

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Explanation: The longest consecutive sequence is [0,1,2,3,4,5,6,7,8]. Length = 9.
```

### Constraints
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9

## Intuition

**Naive approach**: Sort the array, then find longest consecutive run → O(n log n)

**O(n) approach**: Use a hash set for O(1) lookups. The key insight is to **only start counting from sequence beginnings**.

A number `num` is a sequence start if `num - 1` is NOT in the set. This ensures each sequence is counted exactly once.

```
[100, 4, 200, 1, 3, 2]

- 100: Is 99 in set? No → Start of sequence. Count: 100 (length 1)
- 4: Is 3 in set? Yes → Not a start, skip
- 200: Is 199 in set? No → Start of sequence. Count: 200 (length 1)
- 1: Is 0 in set? No → Start of sequence. Count: 1,2,3,4 (length 4) ✓
- 3: Is 2 in set? Yes → Not a start, skip
- 2: Is 1 in set? Yes → Not a start, skip

Answer: 4
```

## Approach

### Approach 1: Hash Set with Sequence Starts (Optimal)

```
1. Add all numbers to a hash set
2. For each number in set:
   a. If (num - 1) NOT in set, this is a sequence start
   b. Count consecutive numbers: num, num+1, num+2, ...
   c. Track maximum length
3. Return maximum length
```

### Approach 2: Expand From Each Element

```
1. Add all numbers to hash set
2. Pop a number from set
3. Expand left and right, removing from set as we go
4. Track length of expansion
5. Repeat until set is empty
```

### Approach 3: Sorting (O(n log n))

```
1. Sort the array
2. Remove duplicates
3. Find longest consecutive run
```

## Visual Walkthrough

### Example: nums = [100, 4, 200, 1, 3, 2]

```
Step 1: Create set
num_set = {100, 4, 200, 1, 3, 2}

Step 2: Find sequence starts and count

Checking 100:
  99 in set? No → 100 is a START
  Count: 100 → 101 in set? No
  Length = 1

Checking 4:
  3 in set? Yes → Skip (not a start)

Checking 200:
  199 in set? No → 200 is a START
  Count: 200 → 201 in set? No
  Length = 1

Checking 1:
  0 in set? No → 1 is a START
  Count: 1 → 2 in set? Yes
         2 → 3 in set? Yes
         3 → 4 in set? Yes
         4 → 5 in set? No
  Length = 4 ← MAXIMUM

Checking 3:
  2 in set? Yes → Skip

Checking 2:
  1 in set? Yes → Skip

Answer: 4
```

### Why This is O(n)?

```
Key insight: Each number is visited at most twice:
1. Once when checking if it's a sequence start
2. Once when counting (if part of a sequence starting earlier)

Total operations ≤ 2n = O(n)
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty array | `[]` | `0` | No elements |
| Single element | `[1]` | `1` | Sequence of length 1 |
| All same | `[5, 5, 5]` | `1` | Duplicates don't extend sequence |
| Negative numbers | `[-2, -1, 0]` | `3` | Consecutive works with negatives |
| Large gaps | `[1, 100, 1000]` | `1` | Three separate sequences |
| All consecutive | `[1, 2, 3, 4, 5]` | `5` | One big sequence |
| Reverse order | `[5, 4, 3, 2, 1]` | `5` | Order doesn't matter |
| Two equal sequences | `[1, 2, 10, 11]` | `2` | Return any max |

## Complexity Analysis

### Hash Set Approach
- **Time Complexity**: O(n)
  - Building set: O(n)
  - Each element checked once for start condition: O(n)
  - Each element counted at most once in sequence: O(n)
  - Total: O(n)
  
- **Space Complexity**: O(n)
  - Hash set stores up to n unique elements

### Sorting Approach
- **Time Complexity**: O(n log n)
  - Sorting dominates
  
- **Space Complexity**: O(1) to O(n)
  - Depends on sorting implementation

## Common Mistakes

1. **Counting from every element**: Results in O(n²) - counting same sequence multiple times
2. **Not handling duplicates**: Set naturally handles this, but be careful with arrays
3. **Off-by-one in counting**: Sequence length is `right - left + 1` or count iterations carefully
4. **Iterating over original array**: Iterate over set to avoid processing duplicates

## Why "Sequence Start" Check is Key

Without the start check:
```
[1, 2, 3, 4]

From 1: Count 1,2,3,4 → length 4
From 2: Count 2,3,4 → length 3  ← Redundant!
From 3: Count 3,4 → length 2    ← Redundant!
From 4: Count 4 → length 1      ← Redundant!

Total operations: 4 + 3 + 2 + 1 = O(n²) for consecutive sequence
```

With start check:
```
From 1: 0 not in set → START. Count 1,2,3,4 → length 4
From 2: 1 in set → Skip
From 3: 2 in set → Skip
From 4: 3 in set → Skip

Total operations: 4 + 3 skips = O(n)
```

## Related Problems

- [Longest Consecutive Sequence II](https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii/) - In binary tree
- [Missing Ranges](https://leetcode.com/problems/missing-ranges/)
- [Contains Duplicate](01_contains_duplicate_EXPLAINED.md) - Similar hash set usage

## Key Takeaways

1. **Identify sequence starts**: Only process from beginning of each sequence
2. **Hash set for O(1) lookup**: Enables O(n) solution
3. **Amortized analysis**: Each element touched at most twice
4. **Duplicates don't matter**: Set handles them automatically
5. **Think about invariants**: "Only count once per sequence" is the key insight

