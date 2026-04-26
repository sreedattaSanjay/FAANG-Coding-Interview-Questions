# Permutation in String (LeetCode #567)

## Problem Statement

Given two strings `s1` and `s2`, return `true` if `s2` contains a **permutation** of `s1`, or `false` otherwise.

In other words, return `true` if one of `s1`'s permutations is a substring of `s2`.

### Examples

```
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains "ba" which is a permutation of "ab".

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
```

### Constraints
- 1 <= s1.length, s2.length <= 10^4
- s1 and s2 consist of lowercase English letters

## Intuition

A permutation of `s1` has the **same characters with the same frequencies** as `s1`. We need to find a **substring** (contiguous) of `s2` that matches this criteria.

**Key insight**: Use a **fixed-size sliding window** of length `len(s1)`. At each position, compare the character frequencies of the window with `s1`.

**Optimization**: Instead of comparing all 26 characters each time, track how many characters currently have matching counts (0 to 26 matches needed).

## Approach

### Approach 1: Fixed Window with Frequency Comparison

```
1. If len(s1) > len(s2): return false
2. Build frequency count for s1
3. Build frequency count for first window in s2
4. Compare counts; if equal, return true
5. Slide window:
   a. Add new character
   b. Remove old character
   c. Compare counts
```

### Approach 2: Match Counting (Optimized)

```
1. Use difference array: count[c] = need[c] - have[c]
2. Track how many characters have count[c] = 0 (matches)
3. When all 26 match, we found a permutation
4. Update matches incrementally when sliding
```

## Visual Walkthrough

### Example: s1 = "ab", s2 = "eidbaooo"

**Fixed Window Approach:**

```
s1 = "ab" → count1 = {a:1, b:1}

Window 1: "ei" → count2 = {e:1, i:1}
          count1 != count2

Window 2: "id" → count2 = {i:1, d:1}
          count1 != count2

Window 3: "db" → count2 = {d:1, b:1}
          count1 != count2

Window 4: "ba" → count2 = {b:1, a:1}
          count1 == count2 ✓

Found permutation at position 3!
```

**Match Counting Approach:**

```
s1 = "ab", s2 = "eidbaooo"
Initial: count = [need - have for each char]

count[a] = 1-0 = 1  (need 1 'a')
count[b] = 1-0 = 1  (need 1 'b')
count[e] = 0-1 = -1 (have extra 'e')
count[i] = 0-1 = -1 (have extra 'i')
... other chars = 0

matches = count of chars where count[c] = 0
Initial matches = 22 (24 unused chars + 0 for a, b)

Slide window:
Remove 'e': count[e] was -1, becomes 0 → matches 22 → 23
Add 'd':    count[d] was 0, becomes -1 → matches 23 → 22

... continue sliding ...

When matches = 26 → found permutation!
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| s1 longer than s2 | `s1="abc", s2="ab"` | `false` | Can't fit |
| Exact match | `s1="ab", s2="ab"` | `true` | Trivial case |
| Single char | `s1="a", s2="b"` | `false` | Single char comparison |
| At beginning | `s1="ab", s2="abxyz"` | `true` | First window |
| At end | `s1="ab", s2="xyzab"` | `true` | Last window |
| Repeated chars | `s1="aab", s2="baa"` | `true` | Frequency matters |
| No match | `s1="abc", s2="defgh"` | `false` | Different chars |

## Complexity Analysis

### Approach 1 (Compare Arrays)
- **Time Complexity**: O(26 × n) = O(n)
  - n windows, each comparison is O(26)
  
- **Space Complexity**: O(1)
  - Two arrays of size 26

### Approach 2 (Match Counting)
- **Time Complexity**: O(n)
  - Each slide is O(1) work
  
- **Space Complexity**: O(1)
  - One array of size 26 + counter

## Common Mistakes

1. **Not handling s1 longer than s2**: Must check this first
2. **Off-by-one in window**: Window size is `len(s1)`, not `len(s1) - 1`
3. **Comparing wrong way**: Check `count1 == count2`, not sorted strings
4. **Not deleting zero counts**: In Python Counter, delete keys with 0 value
5. **Wrong index for old character**: It's `s2[i - k]`, not `s2[i - k + 1]`

## Match Counting Logic Explained

```python
# When adding a character:
if count[c] == 0:      # Was matching, now won't be
    matches -= 1
count[c] -= 1          # We have one more of this char
if count[c] == 0:      # Now matching
    matches += 1

# When removing a character:
if count[c] == 0:      # Was matching, now won't be
    matches -= 1
count[c] += 1          # We have one less of this char
if count[c] == 0:      # Now matching
    matches += 1
```

## Related Problems

- [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) - Find ALL permutations
- [Valid Anagram](../01_Arrays_Hashing/02_valid_anagram_EXPLAINED.md) - Check if two strings are anagrams
- [Minimum Window Substring](05_minimum_window_substring_EXPLAINED.md) - Variable window version

## Key Takeaways

1. **Fixed-size sliding window**: Window size = pattern length
2. **Frequency comparison for permutation**: Same chars = same frequencies
3. **Match counting optimization**: O(1) per slide instead of O(26)
4. **Incremental updates**: Only update affected characters when sliding
5. **Counter in Python**: Use `Counter` for elegant frequency comparison

