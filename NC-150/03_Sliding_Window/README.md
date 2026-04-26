# Sliding Window

## Pattern Overview

The Sliding Window technique maintains a "window" that slides through an array/string to solve problems involving contiguous subarrays or substrings. It's particularly useful for problems that would otherwise require O(n²) nested loops.

## When to Use This Pattern

- **Find min/max subarray/substring of size k** → Fixed-size window
- **Longest/shortest subarray satisfying condition** → Variable-size window
- **Subarray sum/product constraints** → Expand/contract window
- **Anagram/permutation finding** → Fixed-size window with frequency map
- **String matching patterns** → Variable window with character counts

## Types of Sliding Windows

### 1. Fixed-Size Window
```python
# Window always has exactly k elements
for i in range(len(arr) - k + 1):
    window = arr[i:i+k]  # Conceptual - don't actually slice
```

### 2. Variable-Size Window
```python
# Window expands/contracts based on condition
left = 0
for right in range(len(arr)):
    # Add arr[right] to window
    while window_invalid():
        # Remove arr[left] from window
        left += 1
    # Process valid window
```

## Problems in This Section

| # | Problem | Difficulty | Window Type |
|---|---------|------------|-------------|
| 1 | [Best Time to Buy and Sell Stock](01_best_time_buy_sell_stock_EXPLAINED.md) | Easy | Variable (conceptually) |
| 2 | [Longest Substring Without Repeating Characters](02_longest_substring_no_repeat_EXPLAINED.md) | Medium | Variable |
| 3 | [Longest Repeating Character Replacement](03_longest_repeating_char_replacement_EXPLAINED.md) | Medium | Variable |
| 4 | [Permutation in String](04_permutation_in_string_EXPLAINED.md) | Medium | Fixed |
| 5 | [Minimum Window Substring](05_minimum_window_substring_EXPLAINED.md) | Hard | Variable |
| 6 | [Sliding Window Maximum](06_sliding_window_maximum_EXPLAINED.md) | Hard | Fixed + Deque |

## Suggested Study Order

1. **Best Time to Buy and Sell Stock** - Simple sliding logic
2. **Longest Substring Without Repeating Characters** - Classic variable window
3. **Permutation in String** - Fixed window with frequency matching
4. **Longest Repeating Character Replacement** - Variable window with constraint
5. **Minimum Window Substring** - Advanced variable window
6. **Sliding Window Maximum** - Monotonic deque technique

## Key Templates

### Fixed-Size Window Template

```python
def fixed_window(arr, k):
    # Initialize window with first k elements
    window_sum = sum(arr[:k])
    result = window_sum
    
    for i in range(k, len(arr)):
        # Slide: remove left element, add right element
        window_sum += arr[i] - arr[i - k]
        result = max(result, window_sum)
    
    return result
```

### Variable-Size Window Template

```python
def variable_window(arr):
    left = 0
    result = 0
    
    for right in range(len(arr)):
        # Expand window by including arr[right]
        
        while window_is_invalid():
            # Contract window by removing arr[left]
            left += 1
        
        # Update result with current valid window
        result = max(result, right - left + 1)
    
    return result
```

### Character Frequency Window Template

```python
from collections import Counter

def freq_window(s, t):
    need = Counter(t)
    have = Counter()
    required = len(need)
    formed = 0
    left = 0
    
    for right in range(len(s)):
        char = s[right]
        have[char] += 1
        
        if char in need and have[char] == need[char]:
            formed += 1
        
        while formed == required:
            # Valid window found, try to minimize
            # Process window [left, right]
            
            char = s[left]
            have[char] -= 1
            if char in need and have[char] < need[char]:
                formed -= 1
            left += 1
```

## Common Techniques

### 1. Frequency Map for Characters
Track character counts in current window for substring problems.

### 2. Monotonic Deque for Maximum/Minimum
Maintain elements in sorted order to get window max/min in O(1).

### 3. Two Pointers for Window Bounds
Left pointer contracts, right pointer expands.

### 4. "At Most K" to "Exactly K"
```
exactly(k) = atMost(k) - atMost(k-1)
```

## Time Complexity

| Approach | Time | When to Use |
|----------|------|-------------|
| Brute Force | O(n²) or O(n³) | Never in interviews |
| Fixed Window | O(n) | Window size is constant |
| Variable Window | O(n) | Each element added/removed once |
| Window + Map | O(n) | Need frequency tracking |

## Common Mistakes to Avoid

1. **Forgetting to shrink window**: Always check if window needs contraction
2. **Off-by-one in window size**: Window length is `right - left + 1`
3. **Not handling empty input**: Check for edge cases first
4. **Modifying structure while iterating**: Use indices, not iterators
5. **Wrong initialization**: Initialize window state before main loop

