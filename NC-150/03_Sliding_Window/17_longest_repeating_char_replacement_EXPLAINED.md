# Longest Repeating Character Replacement (LeetCode #424)

## Problem Statement

You are given a string `s` and an integer `k`. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most `k` times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

### Examples

```
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with 'B's or vice versa.

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the middle 'B' with 'A' to form "AAAAABA".
Then the longest substring of same letters is "AAAA" with length 4.
```

### Constraints
- 1 <= s.length <= 10^5
- s consists of only uppercase English letters
- 0 <= k <= s.length

## Intuition

For any window to be valid (all same characters after at most k replacements):
```
window_size - max_frequency_in_window <= k
```

**Why?** If we have a window of size `n` and the most frequent character appears `maxFreq` times, we need to replace `n - maxFreq` characters to make all characters the same.

**Key insight**: We don't actually need to know WHICH character is most frequent - we just need the count. We can always convert the minority characters to the majority character.

## Approach

### Algorithm: Sliding Window with Max Frequency

```
1. Maintain character frequency count in current window
2. Track maximum frequency seen (maxFreq)
3. For each right pointer:
   a. Add s[right] to count, update maxFreq
   b. While windowSize - maxFreq > k: shrink from left
   c. Update maximum window length
```

**Optimization**: We don't need to decrease `maxFreq` when shrinking because:
- We're looking for the MAXIMUM valid window
- A smaller maxFreq won't give us a longer window
- If maxFreq was higher before, we already recorded that length

## Visual Walkthrough

### Example: s = "AABABBA", k = 1

```
Window validity: windowSize - maxFreq <= k

Step 1: Right = 0, s[0] = 'A'
        Window: "A"
        count = {A:1}, maxFreq = 1
        1 - 1 = 0 <= 1 ✓
        maxLen = 1

Step 2: Right = 1, s[1] = 'A'
        Window: "AA"
        count = {A:2}, maxFreq = 2
        2 - 2 = 0 <= 1 ✓
        maxLen = 2

Step 3: Right = 2, s[2] = 'B'
        Window: "AAB"
        count = {A:2, B:1}, maxFreq = 2
        3 - 2 = 1 <= 1 ✓
        maxLen = 3

Step 4: Right = 3, s[3] = 'A'
        Window: "AABA"
        count = {A:3, B:1}, maxFreq = 3
        4 - 3 = 1 <= 1 ✓
        maxLen = 4

Step 5: Right = 4, s[4] = 'B'
        Window: "AABAB"
        count = {A:3, B:2}, maxFreq = 3
        5 - 3 = 2 > 1 ✗
        Shrink: remove 'A', left = 1
        Window: "ABAB"
        count = {A:2, B:2}, maxFreq = 3 (not updated!)
        4 - 3 = 1 <= 1 ✓
        maxLen = 4

... continue ...

Final maxLen = 4
```

### Why Not Update maxFreq When Shrinking?

```
Consider: We found a window of size 5 with maxFreq=4
          (valid because 5-4=1 <= k=1)

If we shrink and maxFreq becomes 3:
          New window can be at most size 4 (since 4-3=1 <= k)
          
We already have maxLen = 5, so we don't care about smaller windows!

By not decreasing maxFreq, we:
1. Keep looking for windows at least as large as the best found
2. Skip unnecessary work
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| All same | `"AAAA", k=2` | `4` | No replacement needed |
| k >= length | `"AB", k=5` | `2` | Can replace everything |
| k = 0 | `"AABB", k=0` | `2` | Find longest repeating run |
| Single char | `"A", k=1` | `1` | Trivial case |
| Alternating | `"ABAB", k=2` | `4` | Replace all of one type |
| Empty string | `"", k=5` | `0` | No characters |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Each character is processed once (right pointer)
  - Left pointer only moves forward, total moves ≤ n
  
- **Space Complexity**: O(1)
  - Fixed array of size 26 for character counts
  - Constant extra variables

## Common Mistakes

1. **Decreasing maxFreq when shrinking**: Not necessary for correctness
2. **Using the wrong window condition**: It's `windowSize - maxFreq > k`, not `>= k`
3. **Forgetting uppercase only**: Use `s[i] - 'A'` for indexing
4. **Recalculating max each time**: Inefficient; track running max instead

## Why maxFreq Doesn't Need to Decrease

This is the subtle part of the solution:

```python
# Correct: maxFreq is never decreased
maxFreq = max(maxFreq, count[s[right]])

# Wrong: Recalculating maxFreq each time (works but slower)
maxFreq = max(count.values())
```

The optimization works because:
1. We only care about finding the LONGEST valid window
2. If maxFreq was X and we found a valid window of size Y
3. Any future window must have maxFreq >= X to be larger than Y
4. So we can keep maxFreq as a "high water mark"

## Related Problems

- [Longest Substring Without Repeating Characters](02_longest_substring_no_repeat_EXPLAINED.md)
- [Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) - Similar: flip at most k 0s to 1s
- [Minimum Window Substring](05_minimum_window_substring_EXPLAINED.md)

## Key Takeaways

1. **Window validity condition**: `windowSize - maxFreq <= k`
2. **maxFreq optimization**: Don't decrease; only larger values matter
3. **Implicit character choice**: We don't need to track which character to keep
4. **Fixed-size shrinking**: Remove one from left when window becomes invalid
5. **Count array for frequency**: O(1) space for limited charset

