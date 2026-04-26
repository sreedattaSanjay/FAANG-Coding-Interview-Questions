# Two Pointers

## Pattern Overview

The Two Pointers technique uses two pointers to iterate through data structures in a coordinated way. This often reduces time complexity from O(n²) to O(n) by avoiding nested loops.

## When to Use This Pattern

- **Sorted array operations** → Two pointers from opposite ends
- **Finding pairs with target sum** → Left and right pointers
- **Palindrome checking** → Compare from both ends
- **Removing duplicates in-place** → Read and write pointers
- **Merging sorted arrays** → One pointer per array
- **Linked list operations** → Fast and slow pointers

## Types of Two Pointer Techniques

### 1. Opposite Direction (Left-Right)
```
[1, 2, 3, 4, 5]
 ↑           ↑
left       right
```
Move pointers toward each other based on conditions.

### 2. Same Direction (Fast-Slow)
```
[1, 2, 3, 4, 5]
 ↑  ↑
slow fast
```
Fast pointer explores ahead, slow pointer tracks result.

### 3. Sliding Window (Special Case)
```
[1, 2, 3, 4, 5]
 ↑     ↑
left  right
```
Window expands/contracts based on conditions.

## Problems in This Section

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Valid Palindrome](01_valid_palindrome_EXPLAINED.md) | Easy | Left-Right Pointers |
| 2 | [Two Sum II](02_two_sum_ii_EXPLAINED.md) | Medium | Left-Right on Sorted Array |
| 3 | [3Sum](03_three_sum_EXPLAINED.md) | Medium | Fix One + Two Pointers |
| 4 | [Container With Most Water](04_container_with_most_water_EXPLAINED.md) | Medium | Greedy Two Pointers |
| 5 | [Trapping Rain Water](05_trapping_rain_water_EXPLAINED.md) | Hard | Two Pointers with Max Tracking |

## Suggested Study Order

1. **Valid Palindrome** - Basic two-pointer comparison
2. **Two Sum II** - Two pointers on sorted array
3. **Container With Most Water** - Greedy pointer movement
4. **3Sum** - Combining sorting with two pointers
5. **Trapping Rain Water** - Advanced two-pointer logic

## Key Insights

### When to Move Which Pointer?

**For target sum on sorted array:**
- Sum too small → Move left pointer right (increase sum)
- Sum too large → Move right pointer left (decrease sum)
- Found target → Record and move appropriately

**For max area/container problems:**
- Move the pointer with smaller value (potential for improvement)
- Keep the pointer with larger value (greedy choice)

### Common Two Pointer Patterns

```python
# Pattern 1: Two ends moving inward
left, right = 0, len(arr) - 1
while left < right:
    # Process arr[left] and arr[right]
    if condition:
        left += 1
    else:
        right -= 1

# Pattern 2: Fast-slow for in-place modification
slow = 0
for fast in range(len(arr)):
    if condition:
        arr[slow] = arr[fast]
        slow += 1

# Pattern 3: Skip duplicates
while left < right and arr[left] == arr[left - 1]:
    left += 1
```

## Time Complexity Comparison

| Approach | Time | Space | When to Use |
|----------|------|-------|-------------|
| Brute Force (nested loops) | O(n²) | O(1) | Never in interviews |
| Two Pointers | O(n) | O(1) | Sorted arrays, pairs |
| Hash Map | O(n) | O(n) | Unsorted arrays |
| Sorting + Two Pointers | O(n log n) | O(1) | When sorting is acceptable |

## Common Mistakes to Avoid

1. **Forgetting to skip duplicates**: In 3Sum, skipping is essential
2. **Off-by-one in while condition**: Usually `left < right`, not `<=`
3. **Not handling equal elements**: Think about what happens when `arr[left] == arr[right]`
4. **Modifying input when not allowed**: Some problems require preserving original array
5. **Infinite loops**: Ensure pointers always make progress

