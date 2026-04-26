# Sliding Window Maximum (LeetCode #239)

## Problem Statement

You are given an array of integers `nums`, and there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return the **max** sliding window.

### Examples

```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Input: nums = [1], k = 1
Output: [1]
```

### Constraints
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- 1 <= k <= nums.length

## Intuition

**Brute Force**: For each window, find max in O(k) → Total O(n*k)

**Optimization**: Use a **monotonic decreasing deque**:
- Deque stores indices of elements in decreasing order of values
- Front of deque is always the maximum in current window
- When new element comes, remove smaller elements from back (they can never be max)
- Remove front if it's outside the window

**Key insight**: If we have elements `[..., a, ..., b]` where `a < b` and `a` comes before `b`, then `a` can NEVER be the maximum as long as `b` is in the window. So we remove `a`.

## Approach

### Algorithm: Monotonic Decreasing Deque

```
1. Use deque to store indices (not values)
2. For each element at index i:
   a. Remove indices from front if outside window (index < i - k + 1)
   b. Remove indices from back if their values < nums[i]
   c. Add current index to deque
   d. If window is formed (i >= k - 1), front is the max
```

### Why Deque?

- Need to add/remove from both ends efficiently
- Front: remove old elements outside window
- Back: remove smaller elements that can never be max

## Visual Walkthrough

### Example: nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3

```
Deque stores INDICES, showing values for clarity

i=0: nums[0]=1
     deque = [0] (value 1)
     Window not yet formed

i=1: nums[1]=3
     3 > 1, pop back
     deque = [1] (value 3)
     Window not yet formed

i=2: nums[2]=-1
     -1 < 3, just append
     deque = [1, 2] (values 3, -1)
     Window formed! max = nums[1] = 3
     
i=3: nums[3]=-3
     -3 < -1, just append
     deque = [1, 2, 3] (values 3, -1, -3)
     Check front: 1 >= 3-3+1=1 ✓ (still in window)
     max = nums[1] = 3

i=4: nums[4]=5
     Remove back while < 5: remove 3, 2, 1
     deque = [4] (value 5)
     max = nums[4] = 5

i=5: nums[5]=3
     3 < 5, just append
     deque = [4, 5] (values 5, 3)
     max = nums[4] = 5

i=6: nums[6]=6
     Remove back while < 6: remove 5, 4
     deque = [6] (value 6)
     max = nums[6] = 6

i=7: nums[7]=7
     Remove back while < 7: remove 6
     deque = [7] (value 7)
     max = nums[7] = 7

Result: [3, 3, 5, 5, 6, 7]
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| k = 1 | `[1,2,3], k=1` | `[1,2,3]` | Each element is its own max |
| k = n | `[1,2,3], k=3` | `[3]` | Single window = global max |
| All same | `[5,5,5], k=2` | `[5,5]` | Multiple maxes |
| Decreasing | `[5,4,3,2], k=2` | `[5,4,3]` | Max always at front |
| Increasing | `[1,2,3,4], k=2` | `[2,3,4]` | Max always at back |
| Single element | `[1], k=1` | `[1]` | Trivial |
| Negative numbers | `[-1,-2,-3], k=2` | `[-1,-2]` | Handle negatives |

## Complexity Analysis

### Monotonic Deque
- **Time Complexity**: O(n)
  - Each element added to deque once
  - Each element removed from deque at most once
  - Total operations: 2n = O(n)
  
- **Space Complexity**: O(k)
  - Deque contains at most k elements

### Max Heap with Lazy Deletion
- **Time Complexity**: O(n log n) worst case
  - Each push: O(log n)
  - Lazy deletion may accumulate elements
  
- **Space Complexity**: O(n)
  - Heap may store all elements in worst case

## Common Mistakes

1. **Storing values instead of indices**: Need indices to check if element is in window
2. **Wrong window boundary check**: Element at index `i-k+1` to `i` are in window
3. **Not checking window formation**: Only output after first `k` elements
4. **Wrong order of operations**: Remove old elements before checking max
5. **Using stack instead of deque**: Need to remove from front for old elements

## Why Monotonic Decreasing?

```
If deque has [a, b, c] where nums[a] > nums[b] > nums[c]:
- Maximum is always at front (nums[a])
- When a leaves window, b becomes max
- Maintaining this order means front is always the answer

If we have [3, 1, 2]:
- When 2 enters, 1 can never be max while 2 is present
- So remove 1: [3, 2]
- This is the "pop back while smaller" step
```

## Related Problems

- [Minimum Window Substring](05_minimum_window_substring_EXPLAINED.md)
- [Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)
- [Daily Temperatures](../04_Stack/05_daily_temperatures_EXPLAINED.md) - Uses monotonic stack

## Key Takeaways

1. **Monotonic deque pattern**: Maintain elements in sorted order for O(1) min/max
2. **Store indices, not values**: Enables window boundary checking
3. **Remove from back**: Smaller elements that can never be max
4. **Remove from front**: Elements outside the window
5. **Classic hard problem**: Combines sliding window with advanced data structure

