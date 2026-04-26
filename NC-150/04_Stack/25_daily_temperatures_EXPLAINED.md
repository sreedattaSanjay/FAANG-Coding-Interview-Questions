# Daily Temperatures (LeetCode #739)

## Problem Statement

Given an array of integers `temperatures` represents the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `i`th day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

### Examples

```
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Input: temperatures = [30,30,30]
Output: [0,0,0]
```

### Constraints
- 1 <= temperatures.length <= 10^5
- 30 <= temperatures[i] <= 100

## Intuition

This is a classic **"next greater element"** problem, solved with a **monotonic decreasing stack**.

**Key insight**: We maintain a stack of indices where temperatures are in decreasing order. When we find a temperature greater than the stack top, we've found the "next warmer day" for that index.

## Approach

### Monotonic Stack Algorithm

```
1. Create result array of zeros
2. Use stack to store indices
3. For each day i:
   a. While stack not empty AND current temp > temp at stack top:
      - Pop index from stack
      - result[popped_index] = i - popped_index
   b. Push i to stack
4. Remaining stack elements have no warmer day (already 0)
```

## Visual Walkthrough

### Example: temperatures = [73, 74, 75, 71, 69, 72, 76, 73]

```
Index:  0   1   2   3   4   5   6   7
Temp:  73  74  75  71  69  72  76  73

i=0: temp=73, stack=[]
     Push 0
     stack=[0]

i=1: temp=74 > 73
     Pop 0, result[0]=1-0=1
     Push 1
     stack=[1]

i=2: temp=75 > 74
     Pop 1, result[1]=2-1=1
     Push 2
     stack=[2]

i=3: temp=71 < 75
     Push 3
     stack=[2,3]

i=4: temp=69 < 71
     Push 4
     stack=[2,3,4]

i=5: temp=72 > 69
     Pop 4, result[4]=5-4=1
     72 > 71: Pop 3, result[3]=5-3=2
     72 < 75: Stop
     Push 5
     stack=[2,5]

i=6: temp=76 > 72
     Pop 5, result[5]=6-5=1
     76 > 75: Pop 2, result[2]=6-2=4
     Push 6
     stack=[6]

i=7: temp=73 < 76
     Push 7
     stack=[6,7]

End: stack=[6,7] → no warmer days → result[6]=0, result[7]=0

Result: [1, 1, 4, 2, 1, 1, 0, 0]
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why |
|-----------|---------------|-----------------|-----|
| All increasing | `[30,40,50]` | `[1,1,0]` | Each day's next is immediate |
| All decreasing | `[50,40,30]` | `[0,0,0]` | No warmer days ahead |
| All same | `[30,30,30]` | `[0,0,0]` | Same != warmer |
| Single element | `[50]` | `[0]` | No future days |
| V-shape | `[50,40,60]` | `[2,1,0]` | Jump over valleys |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Each element pushed once, popped at most once
  - Total: 2n operations = O(n)
  
- **Space Complexity**: O(n)
  - Stack can hold up to n elements (all decreasing case)

## Why Monotonic Decreasing?

We want to find the **next greater** element. By maintaining decreasing order:
- Stack top is always the smallest temperature waiting for a warmer day
- When we find a warmer day, it applies to all smaller temps on the stack

If we wanted **next smaller**, we'd use monotonic increasing stack.

## Common Mistakes

1. **Storing values instead of indices**: Need indices for distance calculation
2. **Wrong comparison**: `>` not `>=` (same temp isn't "warmer")
3. **Forgetting default zeros**: Elements remaining in stack have no answer

## Related Problems

- [Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
- [Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) - Circular
- [Largest Rectangle in Histogram](07_largest_rectangle_histogram_EXPLAINED.md)

## Key Takeaways

1. **Monotonic stack for "next greater/smaller"**: Classic pattern
2. **Store indices, not values**: Need position information
3. **Each element handled twice**: Once pushed, once popped (or left)
4. **O(n) despite nested loop**: Amortized analysis

