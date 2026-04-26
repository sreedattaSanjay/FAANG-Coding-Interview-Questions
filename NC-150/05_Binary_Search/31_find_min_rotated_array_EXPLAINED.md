# Find Minimum in Rotated Sorted Array (LeetCode #153)

## Problem Statement

Given a sorted array that has been rotated between 1 and n times, find the minimum element.

### Example

```
Original: [0,1,2,4,5,6,7]
Rotated 4 times: [4,5,6,7,0,1,2]
Minimum: 0
```

## Intuition

In a rotated sorted array:
- One part is larger elements, one part is smaller
- The minimum is where the "break" occurs

**Key insight**: Compare `nums[mid]` with `nums[right]`:
- If `nums[mid] > nums[right]`: minimum is in right half
- If `nums[mid] <= nums[right]`: minimum is in left half (including mid)

## Approach

```
while left < right:
    mid = (left + right) / 2
    if nums[mid] > nums[right]:
        left = mid + 1  # Min is to the right
    else:
        right = mid  # Min could be mid or to the left
return nums[left]
```

## Visual Example

```
[4, 5, 6, 7, 0, 1, 2]
          ↑
       rotation point

nums[mid] = 7 > nums[right] = 2
→ Minimum is in right half [0, 1, 2]
```

## Complexity

- **Time**: O(log n)
- **Space**: O(1)

## Key Takeaways

1. Compare mid with RIGHT endpoint, not left
2. `left < right` loop (not `<=`)
3. Minimum is at the rotation point

