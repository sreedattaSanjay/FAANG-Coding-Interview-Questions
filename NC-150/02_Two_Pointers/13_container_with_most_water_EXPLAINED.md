# Container With Most Water (LeetCode #11)

## Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`th line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the **most water**.

Return the **maximum amount of water** a container can store.

**Note**: You may not slant the container.

### Examples

```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The max area is between index 1 (height 8) and index 8 (height 7).
Area = min(8, 7) * (8 - 1) = 7 * 7 = 49

Input: height = [1,1]
Output: 1
```

### Constraints
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4

## Intuition

**Area formula**: `Area = width × min(left_height, right_height)`

Two pointers start at the ends (maximum width). Moving a pointer inward decreases width, so we must find taller heights to compensate.

**Key insight**: Always move the pointer with the **smaller height**. Why?
- The current area is limited by the smaller height
- Moving the smaller pointer might find a taller bar (potential improvement)
- Moving the larger pointer can only keep or reduce the minimum height (no improvement possible)

## Approach

### Algorithm: Greedy Two Pointers

```
1. Start with pointers at both ends (left = 0, right = n-1)
2. Calculate area and update maximum
3. Move the pointer with smaller height inward
4. Repeat until pointers meet
```

### Why Moving Smaller Pointer is Correct

Consider pointers at `left` and `right` where `height[left] < height[right]`:

- Current area = `(right - left) × height[left]`
- If we move `right` left:
  - Width decreases
  - Height is still limited by `height[left]` (or smaller if `height[new_right] < height[left]`)
  - Area can only decrease or stay same
- If we move `left` right:
  - Width decreases
  - But `height[new_left]` might be larger than `height[left]`
  - New minimum could be larger, potentially increasing area despite smaller width

## Visual Walkthrough

### Example: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]

```
Index:    0  1  2  3  4  5  6  7  8
Height:   1  8  6  2  5  4  8  3  7

Step 1:
         1  8  6  2  5  4  8  3  7
         ↑                       ↑
        left                   right
        
Area = min(1, 7) × (8 - 0) = 1 × 8 = 8
height[left] < height[right] → move left

Step 2:
         1  8  6  2  5  4  8  3  7
            ↑                    ↑
           left                right
           
Area = min(8, 7) × (8 - 1) = 7 × 7 = 49 ← MAX!
height[right] < height[left] → move right

Step 3:
         1  8  6  2  5  4  8  3  7
            ↑                 ↑
           left             right
           
Area = min(8, 3) × (7 - 1) = 3 × 6 = 18
height[right] < height[left] → move right

... continue until pointers meet ...

Maximum area found: 49
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Two elements | `[1, 1]` | `1` | Minimal case |
| Same heights | `[5, 5, 5]` | `10` | Width matters most |
| One tall, others short | `[1, 100, 1]` | `2` | Limited by short sides |
| Increasing | `[1, 2, 3, 4]` | `4` | Best at ends |
| Decreasing | `[4, 3, 2, 1]` | `4` | Best at ends |
| Large at ends | `[10, 1, 10]` | `20` | Skip middle |
| Zero height | `[0, 5, 0]` | `0` | Area is 0 |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Each pointer moves at most n times
  - Total pointer movements ≤ n
  
- **Space Complexity**: O(1)
  - Only using a few variables

### Why O(n) is Optimal

- Must look at each bar at least once (they could all be part of the answer)
- O(n) is the lower bound for this problem

## Common Mistakes

1. **Moving wrong pointer**: Always move the smaller one
2. **Using wrong area formula**: It's `min(h1, h2) × width`, not `max` or `sum`
3. **Off-by-one in width**: Width is `right - left`, not `right - left + 1`
4. **Forgetting to update max**: Must track maximum after each calculation

## Proof of Correctness

Why don't we miss the optimal solution?

Suppose optimal solution uses indices `(i, j)` where `height[i] ≤ height[j]`.

When our pointers are at some `(left, right)` where `left ≤ i` and `right ≥ j`:
- We will compute area for `(i, j)` at some point
- We won't skip `i` from left because we only move left when `height[left] < height[right]`
- Since `height[i] ≤ height[j]`, when we reach `(i, j)`, we will calculate and record this area

## Related Problems

- [Trapping Rain Water](05_trapping_rain_water_EXPLAINED.md) - Similar two-pointer approach
- [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) - Different but related area problem

## Key Takeaways

1. **Greedy two pointers**: Move the limiting factor (shorter height)
2. **Width vs Height tradeoff**: Decreasing width must be compensated by taller heights
3. **Area = width × min(heights)**: Container limited by shorter side
4. **Start at extremes**: Maximum width first, then explore
5. **Proof by contradiction**: Moving larger pointer can't help

