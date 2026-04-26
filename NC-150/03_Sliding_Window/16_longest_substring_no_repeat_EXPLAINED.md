# Longest Substring Without Repeating Characters (LeetCode #3)

## Problem Statement

Given a string `s`, find the length of the **longest substring** without repeating characters.

### Examples

```
Input: s = "abcabcbb"
Output: 3
Explanation: The longest substring is "abc" with length 3.

Input: s = "bbbbb"
Output: 1
Explanation: The longest substring is "b" with length 1.

Input: s = "pwwkew"
Output: 3
Explanation: The longest substring is "wke" with length 3.
Note: "pwke" is a subsequence, not a substring.
```

### Constraints
- 0 <= s.length <= 5 * 10^4
- s consists of English letters, digits, symbols and spaces

## Intuition

We need a **window** that contains only unique characters. When we encounter a duplicate, we shrink the window from the left until the duplicate is removed.

**Key insight**: Use a set to track characters in the current window. When adding a new character, if it's already in the set, remove characters from the left until the duplicate is gone.

**Optimization**: Instead of incrementally removing characters, we can use a hashmap to store the last index of each character. When we find a duplicate, we jump `left` directly to `lastIndex + 1`.

## Approach

### Approach 1: Sliding Window with Set

```
1. Maintain a set of characters in current window
2. For each right pointer:
   a. While current char is in set:
      - Remove s[left] from set
      - Move left++
   b. Add s[right] to set
   c. Update max length
```

### Approach 2: Sliding Window with HashMap (Optimized)

```
1. Maintain a map: char → last seen index
2. For each right pointer:
   a. If s[right] in map and last index >= left:
      - Jump left to lastIndex[s[right]] + 1
   b. Update lastIndex[s[right]] = right
   c. Update max length
```

## Visual Walkthrough

### Example: s = "abcabcbb"

**Set Approach:**

```
s = "abcabcbb"
     ↑
     L,R    set = {a}    maxLen = 1

s = "abcabcbb"
     ↑↑
     L R    set = {a,b}  maxLen = 2

s = "abcabcbb"
     ↑ ↑
     L  R   set = {a,b,c} maxLen = 3

s = "abcabcbb"
     ↑  ↑
     L   R  'a' in set! Remove 'a', move L

s = "abcabcbb"
      ↑ ↑
      L  R  set = {b,c,a} maxLen = 3

... continue ...

Final maxLen = 3
```

**HashMap Approach:**

```
s = "abcabcbb"
     ↑  ↑
     L   R   lastIndex = {a:0, b:1, c:2}
             s[R] = 'a', lastIndex['a'] = 0 >= L = 0
             → L = 0 + 1 = 1
             lastIndex = {a:3, b:1, c:2}

Key insight: We jump L directly to position 1 instead of 
incrementally removing characters!
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty string | `""` | `0` | No characters |
| Single char | `"a"` | `1` | Trivial case |
| All same | `"aaaa"` | `1` | Window size always 1 |
| All unique | `"abcd"` | `4` | Whole string is answer |
| Repeat at end | `"abca"` | `3` | Don't miss last window |
| Spaces | `" "` | `1` | Space is a character |
| Special chars | `"a@b@"` | `3` | Handle non-alphanumeric |
| Tricky: "abba" | `"abba"` | `2` | Old duplicate outside window |

### Tricky Case: "abba"

```
HashMap Approach:
s = "abba"

R=0: lastIndex = {a:0}, L=0, maxLen=1
R=1: lastIndex = {a:0, b:1}, L=0, maxLen=2
R=2: 'b' at index 1 >= L=0, so L=2
     lastIndex = {a:0, b:2}, maxLen=2
R=3: 'a' at index 0 < L=2, so DON'T move L!
     lastIndex = {a:3, b:2}, maxLen=2

The condition "lastIndex[char] >= left" is crucial!
Without it, we'd incorrectly consider the old 'a' at index 0.
```

## Complexity Analysis

### Set Approach
- **Time Complexity**: O(2n) = O(n)
  - Each character is added to set once, removed at most once
  - Amortized O(1) per character
  
- **Space Complexity**: O(min(m, n))
  - Where m is charset size (26 for lowercase, 128 for ASCII)
  - At most min(string length, charset size) characters in set

### HashMap Approach
- **Time Complexity**: O(n)
  - Single pass, O(1) per character
  
- **Space Complexity**: O(min(m, n))
  - Same as set approach

## Common Mistakes

1. **Not checking if duplicate is in current window**: For hashmap approach, must verify `lastIndex >= left`
2. **Off-by-one in window length**: Length is `right - left + 1`
3. **Not handling empty string**: Return 0 for empty input
4. **Forgetting spaces/special chars**: They count as characters too
5. **Updating max before adding char**: Must add char first in set approach

## Related Problems

- [Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)
- [Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/)
- [Minimum Window Substring](05_minimum_window_substring_EXPLAINED.md)

## Key Takeaways

1. **Variable-size sliding window**: Expand right, contract left when invalid
2. **Set for uniqueness**: O(1) lookup for duplicates
3. **HashMap for jump optimization**: Store last index to skip incremental removals
4. **Window validity condition**: Must check if old duplicate is still in current window
5. **Classic interview problem**: Very frequently asked at FAANG

