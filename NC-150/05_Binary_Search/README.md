# Binary Search

## Pattern Overview

Binary Search is a divide-and-conquer algorithm that efficiently finds elements or conditions in sorted data. It achieves O(log n) time by eliminating half of the search space with each comparison.

## When to Use This Pattern

- **Sorted array search** → Classic binary search
- **Finding boundaries** → First/last occurrence
- **Search on answer** → Binary search on result space
- **Rotated array problems** → Modified binary search
- **Matrix search** → Treat as 1D or use 2D binary search
- **Minimizing/Maximizing** → Search for optimal value

## Key Templates

### Template 1: Basic Binary Search

```python
def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

### Template 2: Left Boundary (First Occurrence)

```python
def left_bound(arr, target):
    left, right = 0, len(arr)
    while left < right:
        mid = left + (right - left) // 2
        if arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    return left
```

### Template 3: Right Boundary (Last Occurrence)

```python
def right_bound(arr, target):
    left, right = 0, len(arr)
    while left < right:
        mid = left + (right - left) // 2
        if arr[mid] <= target:
            left = mid + 1
        else:
            right = mid
    return left - 1
```

### Template 4: Binary Search on Answer

```python
def binary_search_answer(low, high, is_valid):
    while low < high:
        mid = low + (high - low) // 2
        if is_valid(mid):
            high = mid  # or low = mid + 1 for maximum
        else:
            low = mid + 1  # or high = mid for maximum
    return low
```

## Problems in This Section

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Binary Search](01_binary_search_EXPLAINED.md) | Easy | Basic Template |
| 2 | [Search a 2D Matrix](02_search_2d_matrix_EXPLAINED.md) | Medium | 2D as 1D |
| 3 | [Koko Eating Bananas](03_koko_eating_bananas_EXPLAINED.md) | Medium | Search on Answer |
| 4 | [Find Minimum in Rotated Sorted Array](04_find_min_rotated_array_EXPLAINED.md) | Medium | Modified Binary Search |
| 5 | [Search in Rotated Sorted Array](05_search_rotated_array_EXPLAINED.md) | Medium | Two-part Search |
| 6 | [Time Based Key-Value Store](06_time_based_key_value_EXPLAINED.md) | Medium | Binary Search + Design |
| 7 | [Median of Two Sorted Arrays](07_median_two_sorted_arrays_EXPLAINED.md) | Hard | Partition Binary Search |

## Suggested Study Order

1. **Binary Search** - Master the basic template
2. **Search a 2D Matrix** - Apply to 2D data
3. **Find Minimum in Rotated Sorted Array** - Modified conditions
4. **Search in Rotated Sorted Array** - Combined conditions
5. **Koko Eating Bananas** - Search on answer space
6. **Time Based Key-Value Store** - Design with binary search
7. **Median of Two Sorted Arrays** - Advanced partitioning

## Common Pitfalls

### 1. Integer Overflow
```python
# Bad: mid = (left + right) // 2  # Can overflow
# Good: mid = left + (right - left) // 2
```

### 2. Infinite Loops
```python
# When using left < right and left = mid
# mid might equal left, causing infinite loop
# Solution: use mid = left + (right - left + 1) // 2
```

### 3. Off-by-One Errors
- `left <= right` vs `left < right`
- `left = mid + 1` vs `left = mid`
- `right = mid - 1` vs `right = mid`

## Choosing the Right Template

| Scenario | Condition | Update |
|----------|-----------|--------|
| Find exact | `left <= right` | `left = mid + 1` or `right = mid - 1` |
| Find first ≥ | `left < right` | `right = mid` or `left = mid + 1` |
| Find last ≤ | `left < right` | `left = mid` or `right = mid - 1` |
| Search on answer | `left < right` | Based on condition |

## Time Complexity

| Operation | Time |
|-----------|------|
| Binary Search | O(log n) |
| Linear Search | O(n) |

Binary search is O(log n) because:
- Each iteration halves search space
- After k iterations: n/2^k elements remain
- When n/2^k = 1: k = log₂(n)

## Common Mistakes to Avoid

1. **Not handling empty array**: Check `if not arr` first
2. **Wrong invariant**: Be clear what `left` and `right` represent
3. **Comparing wrong values**: Mid is an index, not a value
4. **Not returning correct result**: `-1` for not found, or boundary index

