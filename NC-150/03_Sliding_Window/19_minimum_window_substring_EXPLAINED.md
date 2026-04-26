# Minimum Window Substring (LeetCode #76)

## Problem Statement

Given two strings `s` and `t` of lengths `m` and `n` respectively, return the **minimum window substring** of `s` such that every character in `t` (**including duplicates**) is included in the window. If there is no such substring, return the empty string `""`.

### Examples

```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: "BANC" includes 'A', 'B', and 'C' from t.

Input: s = "a", t = "a"
Output: "a"

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be in window, but s only has one.
```

### Constraints
- m == s.length
- n == t.length
- 1 <= m, n <= 10^5
- s and t consist of uppercase and lowercase English letters

## Intuition

We need to find the **smallest window** in `s` that contains all characters from `t`. This is a classic **variable-size sliding window** problem.

**Key insight**: 
1. Expand window (move right) until window contains all chars from t
2. Contract window (move left) to find minimum size while still valid
3. Track the best (minimum) valid window found

We use two maps:
- `need`: characters required from t and their counts
- `have`: characters we currently have in our window

## Approach

### Algorithm: Two Pointers with Character Counting

```
1. Build frequency map for t (need)
2. Track:
   - required: unique chars we need
   - formed: unique chars we have in sufficient quantity
3. Expand right pointer:
   - Add char to window (have)
   - If have[char] == need[char]: formed++
4. Contract left pointer while formed == required:
   - Update minimum window if smaller
   - Remove left char from window
   - If have[char] < need[char]: formed--
```

## Visual Walkthrough

### Example: s = "ADOBECODEBANC", t = "ABC"

```
need = {A:1, B:1, C:1}, required = 3

Step 1: Expand until valid
        "ADOBEC"
         ↑    ↑
         L    R
         have = {A:1, D:1, O:1, B:1, E:1, C:1}
         formed = 3 (A, B, C all satisfied)
         Window valid! Try to minimize.

Step 2: Contract
        "DOBEC"
          ↑   ↑
          L   R
          have = {D:1, O:1, B:1, E:1, C:1}
          formed = 2 (lost A)
          
Step 3: Expand again
        "DOBECODEBA"
          ↑        ↑
          L        R
          ... eventually find smaller window

Step 4: Find "BANC"
                 "BANC"
                  ↑  ↑
                  L  R
                  have = {B:1, A:1, N:1, C:1}
                  formed = 3, length = 4 (minimum!)

Result: "BANC"
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| t longer than s | `s="a", t="aa"` | `""` | Need 2 'a's, only have 1 |
| Exact match | `s="abc", t="abc"` | `"abc"` | Whole string |
| Single char | `s="a", t="a"` | `"a"` | Trivial |
| No match | `s="xyz", t="abc"` | `""` | No common chars |
| Duplicates in t | `s="aa", t="aa"` | `"aa"` | Need both 'a's |
| Case sensitive | `s="Aa", t="a"` | `"a"` | 'A' != 'a' |
| Window at end | `s="xxabc", t="abc"` | `"abc"` | Last 3 chars |

## Complexity Analysis

- **Time Complexity**: O(m + n)
  - O(n) to build need map
  - O(m) for sliding window (each char added/removed once)
  
- **Space Complexity**: O(m + n)
  - O(n) for need map
  - O(m) for have map (in worst case, all unique chars)

## Common Mistakes

1. **Not counting duplicates**: `t = "aa"` needs TWO 'a's
2. **Wrong formed counting**: Increment only when `have[c] == need[c]`, not before
3. **Not handling empty t**: Return "" if t is empty
4. **Off-by-one in substring**: Use `s[start:start+length]` or `s.substr(start, length)`
5. **Comparing count wrong way**: `<` vs `<=` matters when decrementing

## Two Approaches to Track "Valid Window"

### Approach 1: Track Unique Characters Satisfied

```python
formed = 0  # How many unique chars have count >= required
required = len(need)  # Total unique chars needed

# When we get enough of char c:
if have[c] == need[c]:
    formed += 1

# Window is valid when:
if formed == required:
    ...
```

### Approach 2: Track Total Characters Missing

```python
missing = len(t)  # Total chars still needed

# When we add a needed char:
if need[c] > 0:
    missing -= 1
need[c] -= 1

# Window is valid when:
if missing == 0:
    ...
```

## Related Problems

- [Permutation in String](04_permutation_in_string_EXPLAINED.md) - Fixed-size version
- [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
- [Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

## Key Takeaways

1. **Variable window for minimum**: Expand to satisfy, contract to minimize
2. **Two frequency maps**: need (target) and have (current window)
3. **Track formed vs required**: Efficient way to check window validity
4. **Contract inside loop**: Keep contracting while window is valid
5. **This is a hard problem**: Classic FAANG interview question

