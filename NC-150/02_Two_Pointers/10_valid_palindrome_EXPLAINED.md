# Valid Palindrome (LeetCode #125)

## Problem Statement

A phrase is a **palindrome** if, after converting all uppercase letters to lowercase and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

### Examples

```
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Input: s = " "
Output: true
Explanation: After removing non-alphanumeric, s is "". 
             An empty string is a palindrome.
```

### Constraints
- 1 <= s.length <= 2 * 10^5
- s consists only of printable ASCII characters

## Intuition

A palindrome reads the same forwards and backwards. The classic approach is to use **two pointers** starting from opposite ends, moving toward the center while comparing characters.

Key considerations:
1. **Skip non-alphanumeric**: Only compare letters and digits
2. **Case-insensitive**: 'A' and 'a' are the same
3. **Stop when pointers meet**: We've compared all pairs

## Approach

### Approach 1: Two Pointers (Optimal - O(1) space)

```
1. Initialize left = 0, right = len(s) - 1
2. While left < right:
   a. Skip non-alphanumeric from left
   b. Skip non-alphanumeric from right
   c. If lowercase(s[left]) != lowercase(s[right]): return false
   d. Move both pointers inward
3. Return true
```

### Approach 2: Clean and Compare

```
1. Build cleaned string (only alphanumeric, lowercase)
2. Compare cleaned with its reverse
```

## Visual Walkthrough

### Example: "A man, a plan, a canal: Panama"

```
Original: "A man, a plan, a canal: Panama"
           ↑                           ↑
          left                       right

Step 1: s[left]='A', s[right]='a' (alphanumeric)
        Compare: 'a' == 'a' ✓
        Move pointers

"A man, a plan, a canal: Panama"
    ↑                       ↑
   left                   right

Step 2: s[left]=' ' (not alphanumeric) → skip
        s[left]='m', s[right]='m' 
        Compare: 'm' == 'm' ✓

... continue ...

Final: Pointers meet in middle
       All pairs matched → return True
```

### Example: "race a car"

```
"race a car"
 ↑        ↑
left    right

Step 1: 'r' vs 'r' ✓
Step 2: 'a' vs 'a' ✓
Step 3: 'c' vs 'c' ✓
Step 4: 'e' vs ' ' → skip space → 'e' vs 'a'
        'e' != 'a' → return False
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty after cleaning | `" "` | `true` | Empty = palindrome |
| Single character | `"a"` | `true` | Trivially palindrome |
| Only non-alphanumeric | `".,!?"` | `true` | Empty after cleaning |
| Numbers | `"12321"` | `true` | Numbers are alphanumeric |
| Mixed case | `"Aa"` | `true` | Case-insensitive |
| Number vs letter | `"0P"` | `false` | '0' != 'p' |
| All same char | `"aaa"` | `true` | Valid palindrome |
| Long with spaces | `"a b a"` | `true` | "aba" is palindrome |

## Complexity Analysis

### Two Pointers Approach
- **Time Complexity**: O(n)
  - Each character visited at most once
  
- **Space Complexity**: O(1)
  - Only using two pointers

### Clean and Compare Approach
- **Time Complexity**: O(n)
  - One pass to clean, one to compare
  
- **Space Complexity**: O(n)
  - Storing cleaned string

## Common Mistakes

1. **Not skipping non-alphanumeric**: Must check `isalnum()` before comparing
2. **Case sensitivity**: Must convert to same case before comparing
3. **Wrong loop condition**: Use `while left < right`, not `<=`
4. **Boundary check in skip loop**: Must check `left < right` while skipping
5. **Forgetting about numbers**: '0'-'9' are alphanumeric too

## Related Problems

- [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) - Same concept on linked list
- [Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/) - Can delete one character
- [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) - Find palindrome in string

## Key Takeaways

1. **Two pointers from ends**: Classic pattern for palindrome checking
2. **Skip invalid characters**: While loop within while loop
3. **Case normalization**: Convert both to lowercase before comparing
4. **Empty is palindrome**: An empty string satisfies the definition
5. **Python one-liner**: `s.isalnum()` and slicing make it elegant

