# Valid Anagram (LeetCode #242)

## Problem Statement

Given two strings `s` and `t`, return `true` if `t` is an **anagram** of `s`, and `false` otherwise.

An **Anagram** is a word formed by rearranging the letters of a different word, using all the original letters exactly once.

### Examples

```
Input: s = "anagram", t = "nagaram"
Output: true

Input: s = "rat", t = "car"
Output: false
```

### Constraints
- 1 <= s.length, t.length <= 5 * 10^4
- s and t consist of lowercase English letters

## Intuition

Two strings are anagrams if they contain the **same characters with the same frequencies**. 

Key insight: Instead of rearranging letters (which is expensive), we can simply **count the frequency** of each character and compare.

## Approach

### Approach 1: Character Count Array (Optimal)

```
1. If lengths differ → not anagram
2. Create count array of size 26 (for a-z)
3. For each position i:
   - Increment count[s[i]]
   - Decrement count[t[i]]
4. If all counts are 0 → anagram
```

### Approach 2: Hash Map

```
1. If lengths differ → not anagram
2. Count characters in s using hash map
3. For each char in t, decrement count
4. If any count goes negative → not anagram
```

### Approach 3: Sorting

```
1. Sort both strings
2. Compare sorted strings
```

## Visual Walkthrough

### Example: s = "anagram", t = "nagaram"

```
Using count array (index = char - 'a'):

Initial:  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
           a b c d e f g h i j k l m n o p q r s t u v w x y z

After processing 'a' from s, 'n' from t:
          [1,0,0,0,0,0,0,0,0,0,0,0,0,-1,...]
           a                         n

After processing 'n' from s, 'a' from t:
          [0,0,0,0,0,0,0,0,0,0,0,0,0,0,...]

... continue for all characters ...

Final:    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
          All zeros → TRUE (is anagram)
```

### Counter Visualization

```
s = "anagram"
Counter(s) = {'a': 3, 'n': 1, 'g': 1, 'r': 1, 'm': 1}

t = "nagaram"  
Counter(t) = {'n': 1, 'a': 3, 'g': 1, 'r': 1, 'm': 1}

Counter(s) == Counter(t) → True
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty strings | `"", ""` | `true` | Both empty = same characters |
| Single char same | `"a", "a"` | `true` | Minimal valid case |
| Single char diff | `"a", "b"` | `false` | Different characters |
| Different lengths | `"ab", "a"` | `false` | Must check length first |
| Same letters, diff freq | `"aab", "abb"` | `false` | Frequency matters |
| Repeated characters | `"aa", "aa"` | `true` | Handle duplicates |
| Long identical | `"abc...xyz", "abc...xyz"` | `true` | Same string is anagram of itself |

## Complexity Analysis

### Count Array Approach
- **Time Complexity**: O(n)
  - Single pass through both strings simultaneously
  - Final check of 26 elements is O(1)
  
- **Space Complexity**: O(1)
  - Fixed array of 26 integers regardless of input size

### Hash Map Approach
- **Time Complexity**: O(n)
  - Two passes through strings
  
- **Space Complexity**: O(k)
  - Where k is the number of unique characters (at most 26 for lowercase)

### Sorting Approach
- **Time Complexity**: O(n log n)
  - Dominated by sorting
  
- **Space Complexity**: O(n)
  - Depends on sorting implementation

## Common Mistakes

1. **Forgetting length check**: Different length strings can't be anagrams
2. **Case sensitivity**: "Ab" vs "ba" - problem says lowercase, but always clarify
3. **Unicode handling**: Count array only works for limited character sets
4. **Modifying input**: Sorting modifies the original strings

## Related Problems

- [Group Anagrams](04_group_anagrams_EXPLAINED.md) - Group strings that are anagrams
- [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) - Sliding window + anagram check
- [Permutation in String](https://leetcode.com/problems/permutation-in-string/) - Similar concept with substrings

## Key Takeaways

1. **Counting pattern**: Many string problems reduce to character counting
2. **Fixed-size array optimization**: When alphabet is limited, arrays beat hash maps
3. **Early termination**: Check length first to fail fast
4. **Python Counter**: `Counter(s) == Counter(t)` is elegant and readable
5. **Follow-up**: For Unicode, use hash map instead of fixed array

