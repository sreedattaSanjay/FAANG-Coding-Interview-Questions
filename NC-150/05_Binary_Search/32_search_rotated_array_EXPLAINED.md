# Search in Rotated Sorted Array (LeetCode #33)

## Problem Statement

Search for a target value in a rotated sorted array with unique elements.

## Intuition

At any point, at least one half of the array is sorted. We can:
1. Determine which half is sorted
2. Check if target is in the sorted half
3. Search accordingly

## Approach

```
if nums[left] <= nums[mid]:  # Left half sorted
    if target in [nums[left], nums[mid]):
        search left
    else:
        search right
else:  # Right half sorted
    if target in (nums[mid], nums[right]]:
        search right
    else:
        search left
```

## Visual Example

```
[4, 5, 6, 7, 0, 1, 2], target = 0

mid = 3, nums[mid] = 7
nums[left]=4 <= nums[mid]=7 → Left half [4,5,6,7] is sorted
target=0 not in [4,7) → search right half [0,1,2]
```

## Complexity

- **Time**: O(log n)
- **Space**: O(1)

## Key Takeaways

1. At least one half is always sorted
2. Use sorted half to decide search direction
3. Careful with boundary conditions (<=, <)

