# Largest Rectangle in Histogram (LeetCode #84)

## Problem Statement

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the area of the largest rectangle in the histogram.

### Examples

```
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The largest rectangle has area = 10 (height 5 × width 2)

Input: heights = [2,4]
Output: 4
```

### Constraints
- 1 <= heights.length <= 10^5
- 0 <= heights[i] <= 10^4

## Intuition

For each bar, we want to find the **largest rectangle where this bar is the shortest bar** (limiting factor).

This means finding:
- **Left boundary**: first bar shorter than current (to the left)
- **Right boundary**: first bar shorter than current (to the right)
- **Width** = right - left - 1
- **Area** = height × width

A **monotonic increasing stack** helps find these boundaries in O(n).

## Approach

### Algorithm: Single Pass with Stack

```
1. Use stack to store indices of bars in increasing order
2. For each bar:
   a. While current height < stack top height:
      - Pop the top
      - Calculate area with popped bar as height
      - Width = current index - new stack top - 1
   b. Push current index
3. Process remaining stack elements (using array length as right boundary)
```

**Sentinel trick**: Add height 0 at end to force processing all remaining bars.

## Visual Walkthrough

### Example: heights = [2, 1, 5, 6, 2, 3]

```
         ___
        |   |
     ___|   |
    |   |   |       ___
 ___|   |   |___   |   |
|   |   |   |   |  |   |
+---+---+---+---+---+---+
  2   1   5   6   2   3

With sentinel [2, 1, 5, 6, 2, 3, 0]:

i=0: h=2, stack=[]
     Push 0, stack=[0]

i=1: h=1 < heights[0]=2
     Pop 0, height=2, width=1, area=2
     Push 1, stack=[1]

i=2: h=5 > 1, push
     stack=[1,2]

i=3: h=6 > 5, push
     stack=[1,2,3]

i=4: h=2 < heights[3]=6
     Pop 3, height=6, width=4-2-1=1, area=6
     h=2 < heights[2]=5
     Pop 2, height=5, width=4-1-1=2, area=10 ← MAX!
     Push 4, stack=[1,4]

i=5: h=3 > 2, push
     stack=[1,4,5]

i=6: h=0 (sentinel)
     Pop 5, height=3, width=6-4-1=1, area=3
     Pop 4, height=2, width=6-1-1=4, area=8
     Pop 1, height=1, width=6, area=6

Maximum area: 10
```

## Edge Cases Analysis

| Edge Case | Input | Expected | Why |
|-----------|-------|----------|-----|
| Single bar | `[5]` | 5 | Height × 1 |
| All same | `[3,3,3]` | 9 | 3 × 3 |
| Increasing | `[1,2,3]` | 4 | 2 × 2 or 1 × 3 |
| Decreasing | `[3,2,1]` | 4 | 2 × 2 or 1 × 3 |
| Valley | `[3,1,3]` | 3 | Limited by middle bar |
| Mountain | `[1,3,1]` | 3 | 1 × 3 or 3 × 1 |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Each bar pushed once, popped once
  
- **Space Complexity**: O(n)
  - Stack can hold up to n indices

## Two-Pass Alternative

```
Pass 1: Find left[i] = first index with smaller height to left
Pass 2: Find right[i] = first index with smaller height to right
Area[i] = heights[i] × (right[i] - left[i] - 1)
```

## Common Mistakes

1. **Forgetting remaining stack**: Must process bars left in stack after iteration
2. **Width calculation**: `right - left - 1`, not `right - left`
3. **Empty stack check**: When stack is empty, left boundary is -1 (or use width = i)
4. **Wrong stack order**: Must be increasing for "next smaller" pattern

## Why Increasing Stack?

We want the rectangle limited by each bar:
- When we find a shorter bar, the taller bar's rectangle ends
- Stack in increasing order ensures we process bars in the right sequence
- Each bar is processed exactly when its rectangle can no longer extend

## Related Problems

- [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) - 2D version
- [Trapping Rain Water](../02_Two_Pointers/05_trapping_rain_water_EXPLAINED.md) - Similar stack approach
- [Daily Temperatures](05_daily_temperatures_EXPLAINED.md) - Monotonic stack basics

## Key Takeaways

1. **Monotonic increasing stack**: For "next smaller" problems
2. **Sentinel value**: Simplifies handling remaining elements
3. **Width = right - left - 1**: Area formula
4. **Classic hard problem**: Appears in FAANG interviews
5. **Building block**: Used in Maximal Rectangle problem

