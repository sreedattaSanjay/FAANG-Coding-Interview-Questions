# Valid Parentheses (LeetCode #20)

## Problem Statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:
1. Open brackets must be closed by the **same type** of brackets.
2. Open brackets must be closed in the **correct order**.
3. Every close bracket has a corresponding open bracket of the same type.

### Examples

```
Input: s = "()"
Output: true

Input: s = "()[]{}"
Output: true

Input: s = "(]"
Output: false

Input: s = "([)]"
Output: false

Input: s = "{[]}"
Output: true
```

### Constraints
- 1 <= s.length <= 10^4
- s consists of parentheses only: '()[]{}'

## Intuition

This is the classic stack problem. The key insight is:
- **Opening brackets** are pushed onto the stack
- **Closing brackets** must match the most recent opening bracket (top of stack)

If at any point a closing bracket doesn't match, or there's nothing to match, the string is invalid.

## Approach

### Algorithm: Stack Matching

```
1. Create a stack for opening brackets
2. For each character:
   a. If opening bracket: push to stack
   b. If closing bracket:
      - If stack empty: return false
      - If top doesn't match: return false
      - Otherwise: pop from stack
3. Return true if stack is empty
```

## Visual Walkthrough

### Example 1: s = "{[]}"

```
Step 1: '{' → Push
        Stack: ['{']

Step 2: '[' → Push
        Stack: ['{', '[']

Step 3: ']' → Matches '[' → Pop
        Stack: ['{']

Step 4: '}' → Matches '{' → Pop
        Stack: []

Stack empty → VALID ✓
```

### Example 2: s = "([)]"

```
Step 1: '(' → Push
        Stack: ['(']

Step 2: '[' → Push
        Stack: ['(', '[']

Step 3: ')' → Should match '[' at top
        '[' ≠ '(' → INVALID ✗
```

### Example 3: s = "((("

```
Step 1-3: Push all
        Stack: ['(', '(', '(']

End of string, stack not empty → INVALID ✗
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty string | `""` | `true` | No brackets = valid |
| Single open | `"("` | `false` | Unmatched opening |
| Single close | `")"` | `false` | Nothing to match |
| Simple pair | `"()"` | `true` | Basic case |
| Wrong type | `"(]"` | `false` | Type mismatch |
| Wrong order | `"([)]"` | `false` | Interleaved incorrectly |
| Deeply nested | `"{{[[]]}}"` | `true` | Multiple levels |
| All same type | `"(((())))"` | `true` | Repeated brackets |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Single pass through the string
  - Each character is pushed/popped at most once
  
- **Space Complexity**: O(n)
  - In worst case (all opening brackets), stack has n/2 elements
  - Or n elements if string is all opening brackets

## Common Mistakes

1. **Not checking if stack is empty before pop**: Causes runtime error
2. **Wrong matching logic**: `(` matches `)`, not `(`
3. **Forgetting final empty check**: Stack must be empty at end
4. **Not handling all bracket types**: Must handle `()`, `{}`, `[]`

## Alternative Approaches

### Replace Method (Less Efficient)
```python
while '()' in s or '{}' in s or '[]' in s:
    s = s.replace('()', '').replace('{}', '').replace('[]', '')
return s == ''
```
- Time: O(n²) due to repeated string operations
- Space: O(n) for string copies

## Related Problems

- [Generate Parentheses](04_generate_parentheses_EXPLAINED.md) - Generate all valid combinations
- [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) - DP/Stack
- [Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/) - BFS

## Key Takeaways

1. **Stack for matching**: Perfect for "most recent" matching problems
2. **HashMap for pairs**: Clean way to map closing to opening brackets
3. **Two conditions for valid**: Matching during iteration AND empty stack at end
4. **Classic interview problem**: Must know this one cold!

