# Trapping Rain Water (LeetCode #42)

## Problem Statement

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

### Examples

```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: 6 units of rain water are trapped.

Input: height = [4,2,0,3,2,5]
Output: 9
```

### Constraints
- n == height.length
- 1 <= n <= 2 * 10^4
- 0 <= height[i] <= 10^5

## Intuition

Water at any position is determined by the **minimum of the maximum heights** on its left and right, minus its own height.

```
Water at position i = min(maxLeft[i], maxRight[i]) - height[i]
```

**Key insight for two-pointer approach**: We don't need to know both max values at each position. We only need to know that one side is "safe" (definitely higher than current water level).

If `height[left] < height[right]`, then:
- Water at `left` is bounded by `leftMax` (the smaller side)
- We don't care about exact `rightMax` because we know `height[right] >= height[left]`
- So water at `left` = `leftMax - height[left]` (if positive)

## Approach

### Approach 1: Two Pointers (Optimal - O(1) space)

```
1. Initialize left = 0, right = n-1
2. Track leftMax and rightMax
3. While left < right:
   a. If height[left] < height[right]:
      - Water at left is determined by leftMax
      - Add leftMax - height[left] if positive
      - Update leftMax
      - Move left++
   b. Else:
      - Water at right is determined by rightMax
      - Add rightMax - height[right] if positive
      - Update rightMax
      - Move right--
```

### Approach 2: Prefix/Suffix Arrays (O(n) space)

```
1. Precompute leftMax[i] = max height from 0 to i
2. Precompute rightMax[i] = max height from i to n-1
3. For each i: water += min(leftMax[i], rightMax[i]) - height[i]
```

### Approach 3: Monotonic Stack (O(n) space)

```
1. Use stack to track bars in decreasing order
2. When finding a taller bar, calculate horizontal "layers" of water
```

## Visual Walkthrough

### Example: height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]

```
Visual representation:
       #
   #~~~#~#~#
 #~##~####~#
0120101321 21

Water trapped:
       #
   #WWW#W#W#
 #W##W####W#
0120101321 21

W = water (total = 6)
```

### Two-Pointer Walkthrough

```
height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
          ↑                             ↑
        left=0                       right=11
        leftMax=0                    rightMax=0

Step 1: height[0]=0 < height[11]=1
        leftMax = max(0, 0) = 0
        water += 0 - 0 = 0
        left = 1

Step 2: height[1]=1 < height[11]=1
        leftMax = max(0, 1) = 1
        water += 0 (new max, no water)
        left = 2

Step 3: height[2]=0 < height[11]=1
        leftMax = 1
        water += 1 - 0 = 1 ✓
        left = 3

Step 4: height[3]=2 >= height[11]=1
        rightMax = max(0, 1) = 1
        water += 0 (new max, no water)
        right = 10

Step 5: height[3]=2 > height[10]=2
        rightMax = max(1, 2) = 2
        water += 0 (new max)
        right = 9

Step 6: height[3]=2 > height[9]=1
        water += 2 - 1 = 1 ✓
        right = 8

... continue ...

Total water = 6
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty array | `[]` | `0` | No bars |
| Single element | `[5]` | `0` | Need 2 sides to trap |
| Two elements | `[5, 4]` | `0` | No middle to trap in |
| No valleys | `[1, 2, 3]` | `0` | Water flows off |
| Decreasing | `[3, 2, 1]` | `0` | Water flows off |
| Simple valley | `[2, 0, 2]` | `2` | Basic trapping |
| All zeros | `[0, 0, 0]` | `0` | No height to trap |
| All same | `[3, 3, 3]` | `0` | No valley |

## Complexity Analysis

### Two Pointers
- **Time Complexity**: O(n)
  - Single pass through array
  
- **Space Complexity**: O(1)
  - Only a few variables

### Prefix/Suffix Arrays
- **Time Complexity**: O(n)
  - Three passes: build leftMax, build rightMax, calculate water
  
- **Space Complexity**: O(n)
  - Two arrays of size n

### Monotonic Stack
- **Time Complexity**: O(n)
  - Each element pushed and popped at most once
  
- **Space Complexity**: O(n)
  - Stack can hold up to n elements

## Common Mistakes

1. **Forgetting to update max**: Must track running maximum
2. **Wrong formula**: `water = min(leftMax, rightMax) - height`, not just one max
3. **Including current height in max**: leftMax[i] should include height[i]
4. **Off-by-one**: Careful with array indices
5. **Negative water**: Only add if `min(maxes) > height[i]`

## Related Problems

- [Container With Most Water](04_container_with_most_water_EXPLAINED.md) - Similar two-pointer
- [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) - Stack approach
- [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/) - 3D version

## Key Takeaways

1. **Water at position i**: `min(leftMax, rightMax) - height[i]`
2. **Two-pointer insight**: We only need the smaller side's max
3. **Move smaller side**: Similar to Container With Most Water
4. **Three approaches**: Arrays (intuitive), Two-pointer (optimal), Stack (row-by-row)
5. **Classic hard problem**: Appears frequently in FAANG interviews

