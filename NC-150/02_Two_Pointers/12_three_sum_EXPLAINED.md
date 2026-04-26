# 3Sum (LeetCode #15)

## Problem Statement

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must **not contain duplicate triplets**.

### Examples

```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0
Unique triplets are [-1,0,1] and [-1,-1,2].

Input: nums = [0,0,0]
Output: [[0,0,0]]
```

### Constraints
- 3 <= nums.length <= 3000
- -10^5 <= nums[i] <= 10^5

## Intuition

This is an extension of Two Sum. For each element, we need to find two other elements that sum to its negative.

**Key insights**:
1. **Sort first**: Enables two-pointer technique and duplicate handling
2. **Fix one element**: Reduce 3Sum to 2Sum problem
3. **Skip duplicates**: Avoid duplicate triplets by skipping same values

## Approach

### Algorithm: Sort + Fix One + Two Pointers

```
1. Sort the array
2. For each element nums[i] (first element of triplet):
   a. Skip if duplicate (nums[i] == nums[i-1])
   b. Use two pointers (left = i+1, right = n-1) to find pairs summing to -nums[i]
   c. When found, add triplet and skip duplicates
3. Return all unique triplets
```

### Why Sorting Helps

1. **Enables two-pointer technique**: Works on sorted arrays
2. **Easy duplicate skipping**: Same values are adjacent after sorting
3. **Early termination**: If nums[i] > 0, remaining sums can't be 0

## Visual Walkthrough

### Example: nums = [-1, 0, 1, 2, -1, -4]

```
Step 1: Sort
Sorted: [-4, -1, -1, 0, 1, 2]

Step 2: Fix i = 0 (nums[i] = -4)
Target = -(-4) = 4

[-4, -1, -1, 0, 1, 2]
  ↑   ↑            ↑
  i  left        right

-1 + 2 = 1 < 4 → left++
-1 + 2 = 1 < 4 → left++
0 + 2 = 2 < 4 → left++
1 + 2 = 3 < 4 → left++
left >= right → done

No triplet with -4.

Step 3: Fix i = 1 (nums[i] = -1)
Target = -(-1) = 1

[-4, -1, -1, 0, 1, 2]
      ↑   ↑        ↑
      i  left    right

-1 + 2 = 1 == 1 → FOUND! Add [-1, -1, 2]
Skip duplicates, move both pointers

[-4, -1, -1, 0, 1, 2]
      ↑      ↑  ↑
      i    left right

0 + 1 = 1 == 1 → FOUND! Add [-1, 0, 1]
Move pointers → left >= right → done

Step 4: Fix i = 2 (nums[i] = -1)
SKIP! (nums[2] == nums[1])

Step 5: Fix i = 3 (nums[i] = 0)
Target = 0

[-4, -1, -1, 0, 1, 2]
            ↑  ↑  ↑
            i  l  r

1 + 2 = 3 > 0 → right--
left >= right → done

Step 6: nums[4] = 1 > 0 → break (early termination)

Result: [[-1,-1,2], [-1,0,1]]
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Less than 3 elements | `[1,2]` | `[]` | Can't form triplet |
| All zeros | `[0,0,0]` | `[[0,0,0]]` | Only valid triplet |
| No solution | `[1,2,3]` | `[]` | All positive |
| Many duplicates | `[-1,-1,-1,2]` | `[[-1,-1,2]]` | Must deduplicate |
| All positive | `[1,1,1]` | `[]` | Can't sum to 0 |
| All negative | `[-1,-1,-1]` | `[]` | Can't sum to 0 |

## Complexity Analysis

- **Time Complexity**: O(n²)
  - Sorting: O(n log n)
  - Outer loop: O(n)
  - Inner two-pointer: O(n) for each outer iteration
  - Total: O(n log n + n²) = O(n²)
  
- **Space Complexity**: O(1) extra
  - Excluding output array
  - Sorting may use O(log n) to O(n) depending on implementation

## Common Mistakes

1. **Forgetting to skip duplicates**: Leads to duplicate triplets
2. **Wrong duplicate skip position**: 
   - For i: Check `nums[i] == nums[i-1]` not `nums[i] == nums[i+1]`
   - For left/right: Skip after finding a match
3. **Not sorting first**: Two-pointer only works on sorted arrays
4. **Missing early termination**: If `nums[i] > 0`, break
5. **Index out of bounds**: Careful with `i > 0` check for duplicate skip

## Skipping Duplicates - Correct vs Wrong

```python
# WRONG - might miss valid triplets
for i in range(n):
    if nums[i] == nums[i + 1]:  # Wrong comparison
        continue

# CORRECT - skip after processing first occurrence
for i in range(n):
    if i > 0 and nums[i] == nums[i - 1]:
        continue
```

## Related Problems

- [Two Sum II](02_two_sum_ii_EXPLAINED.md) - Foundation for this problem
- [4Sum](https://leetcode.com/problems/4sum/) - Extend to 4 numbers
- [3Sum Closest](https://leetcode.com/problems/3sum-closest/) - Find closest sum to target
- [3Sum Smaller](https://leetcode.com/problems/3sum-smaller/) - Count triplets less than target

## Key Takeaways

1. **Reduce dimension**: 3Sum → Fix one + 2Sum
2. **Sort for two-pointer**: Enables O(n²) instead of O(n³)
3. **Handle duplicates carefully**: Skip same values to avoid duplicate triplets
4. **Early termination**: Break when minimum element is positive
5. **Classic pattern**: Used in many k-Sum variants

