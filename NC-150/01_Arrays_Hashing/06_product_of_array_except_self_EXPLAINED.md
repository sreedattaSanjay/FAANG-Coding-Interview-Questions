# Product of Array Except Self (LeetCode #238)

## Problem Statement

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of nums is **guaranteed to fit in a 32-bit integer**.

You must write an algorithm that runs in **O(n) time** and **without using the division operation**.

### Examples

```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Explanation:
- answer[0] = 2*3*4 = 24
- answer[1] = 1*3*4 = 12
- answer[2] = 1*2*4 = 8
- answer[3] = 1*2*3 = 6

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

### Constraints
- 2 <= nums.length <= 10^5
- -30 <= nums[i] <= 30
- Product of any prefix/suffix fits in 32-bit integer

## Intuition

For each position i, we need:
```
answer[i] = (product of all elements to the LEFT) × (product of all elements to the RIGHT)
          = prefix_product[i] × suffix_product[i]
```

Key insight: We can compute prefix products in one pass (left to right) and suffix products in another pass (right to left).

**Space optimization**: Instead of storing both arrays, we can:
1. Store prefix products in the result array
2. Multiply by suffix products in a second pass using a single variable

## Approach

### Approach 1: Two-Pass with Single Result Array (Optimal)

```
1. Initialize result array with 1s
2. First pass (left to right):
   - result[i] = product of all elements before i
   - Maintain running prefix product
3. Second pass (right to left):
   - result[i] *= product of all elements after i
   - Maintain running suffix product
```

### Approach 2: Separate Prefix and Suffix Arrays

```
1. Create prefix array: prefix[i] = product of nums[0..i-1]
2. Create suffix array: suffix[i] = product of nums[i+1..n-1]
3. result[i] = prefix[i] * suffix[i]
```

## Visual Walkthrough

### Example: nums = [1, 2, 3, 4]

```
Step 1: First pass - compute prefix products

i=0: result[0] = 1 (nothing to left)
     prefix = 1 * nums[0] = 1

i=1: result[1] = 1 (prefix so far)
     prefix = 1 * nums[1] = 2

i=2: result[2] = 2 (prefix so far)
     prefix = 2 * nums[2] = 6

i=3: result[3] = 6 (prefix so far)
     prefix = 6 * nums[3] = 24

After first pass: result = [1, 1, 2, 6]
                           ↑  ↑  ↑  ↑
                          1×  1  1×2 1×2×3


Step 2: Second pass - multiply by suffix products

i=3: result[3] = 6 * 1 = 6 (nothing to right)
     suffix = 1 * nums[3] = 4

i=2: result[2] = 2 * 4 = 8
     suffix = 4 * nums[2] = 12

i=1: result[1] = 1 * 12 = 12
     suffix = 12 * nums[1] = 24

i=0: result[0] = 1 * 24 = 24
     suffix = 24 * nums[0] = 24

Final result: [24, 12, 8, 6]
```

### Visual Representation

```
nums:    [  1,    2,    3,    4  ]
         
prefix:  [  1,    1,    2,    6  ]  ← products before each index
suffix:  [ 24,   12,    4,    1  ]  ← products after each index

result:  [ 24,   12,    8,    6  ]  ← prefix × suffix
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Two elements | `[1, 2]` | `[2, 1]` | Minimal case |
| Contains zero | `[1, 0, 3]` | `[0, 3, 0]` | Only zero position is non-zero |
| Multiple zeros | `[0, 0, 1]` | `[0, 0, 0]` | All products are zero |
| All zeros | `[0, 0, 0]` | `[0, 0, 0]` | Trivial case |
| Negative numbers | `[-1, -2]` | `[-2, -1]` | Signs matter |
| Mixed signs | `[-1, 2, -3]` | `[-6, 3, -2]` | Careful with negatives |
| All ones | `[1, 1, 1]` | `[1, 1, 1]` | Product is always 1 |

## Complexity Analysis

### Two-Pass Approach (Optimal)
- **Time Complexity**: O(n)
  - Two passes through the array, each O(n)
  
- **Space Complexity**: O(1) extra space
  - Only using the output array (which doesn't count per problem)
  - Two variables for prefix and suffix

### Prefix/Suffix Arrays Approach
- **Time Complexity**: O(n)
  - Three passes: prefix, suffix, combine
  
- **Space Complexity**: O(n)
  - Two extra arrays of size n

## Common Mistakes

1. **Including current element**: `prefix[i]` should NOT include `nums[i]`
2. **Forgetting base case**: Initialize with 1, not 0 (multiplicative identity)
3. **Using division**: Problem explicitly forbids this
4. **Zero handling with division**: If using division, multiple zeros break it
5. **Integer overflow**: Problem guarantees it won't happen, but be aware

## Why Division Doesn't Work (Simply)

```
Total product = 1 * 2 * 3 * 4 = 24
result[i] = total / nums[i]  # Seems simple!

But what if nums[i] = 0?
result[i] = 24 / 0 = undefined!

Also, problem explicitly says no division.
```

## Related Problems

- [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) - Similar prefix/suffix max idea
- [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) - Product DP
- [Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/) - Sliding window with products

## Key Takeaways

1. **Prefix/Suffix products**: Powerful technique for "except self" type problems
2. **Space optimization**: Store one array in result, compute other on-the-fly
3. **Two-pass technique**: When you need info from both directions
4. **Multiplicative identity**: Initialize products with 1, not 0
5. **No division trick**: Think prefix × suffix instead of total ÷ current

