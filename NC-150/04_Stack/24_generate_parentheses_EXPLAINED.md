# Generate Parentheses (LeetCode #22)

## Problem Statement

Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

### Examples

```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Input: n = 1
Output: ["()"]
```

### Constraints
- 1 <= n <= 8

## Intuition

This is a classic **backtracking** problem. At each step, we can either add `(` or `)`, but with constraints:

1. Can add `(` if we haven't used all n open parentheses
2. Can add `)` only if there are unmatched open parentheses (close < open)

By following these rules, every generated string is guaranteed to be valid.

## Approach

### Backtracking Algorithm

```
backtrack(current, open, close):
    if length == 2n:
        add to result
        return
    
    if open < n:
        backtrack(current + "(", open + 1, close)
    
    if close < open:
        backtrack(current + ")", open, close + 1)
```

## Visual Walkthrough

### Example: n = 2

```
Decision Tree:
                    ""
                    |
                   "("
                 /     \
            "(("        "()"
            /  \          |
        "(()"  INVALID   "()()"
          |
       "(())" 

Valid results: ["(())", "()()"]
```

### Step by Step for n = 3

```
Start: current="", open=0, close=0

Can add '(': open=0 < n=3 ✓
→ current="(", open=1, close=0

  Can add '(': open=1 < 3 ✓
  → current="((", open=2, close=0
  
    Can add '(': open=2 < 3 ✓
    → current="(((", open=3, close=0
    
      Can add '(': open=3 < 3 ✗
      Can add ')': close=0 < open=3 ✓
      → current="((()...) → eventually "((()))"

... and so on for all branches
```

## Edge Cases Analysis

| n | Number of Results | Notes |
|---|-------------------|-------|
| 1 | 1 | Just "()" |
| 2 | 2 | "(())", "()()" |
| 3 | 5 | See example |
| 4 | 14 | Catalan numbers |
| 5 | 42 | |

The count follows **Catalan numbers**: C(n) = (2n)! / ((n+1)! * n!)

## Complexity Analysis

- **Time Complexity**: O(4^n / √n)
  - This is related to the nth Catalan number
  - We generate each valid sequence exactly once
  
- **Space Complexity**: O(n)
  - Recursion depth is 2n
  - Each level uses O(1) extra space

## Common Mistakes

1. **Not tracking open vs close separately**: Both counts are needed
2. **Wrong condition for close**: It's `close < open`, not `close < n`
3. **Forgetting base case**: Stop when length == 2n
4. **String vs list**: String concatenation in loop can be slow

## Why This Works

At any valid state:
- `open`: number of `(` used
- `close`: number of `)` used

Invariants:
- `close <= open` (can't have more `)` than `(`)
- `open <= n` (can't use more than n open parens)
- `close <= n` (can't use more than n close parens)

These invariants ensure every path leads to a valid string.

## Related Problems

- [Valid Parentheses](01_valid_parentheses_EXPLAINED.md) - Check if valid
- [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) - DP
- [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) - Similar backtracking

## Key Takeaways

1. **Backtracking with constraints**: Only explore valid branches
2. **Track state (open, close)**: Know what's available
3. **Catalan numbers**: Count of valid parentheses sequences
4. **No explicit stack needed**: Recursion handles it implicitly

