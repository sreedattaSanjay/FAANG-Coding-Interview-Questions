# Evaluate Reverse Polish Notation (LeetCode #150)

## Problem Statement

You are given an array of strings `tokens` that represents an arithmetic expression in Reverse Polish Notation (RPN).

Evaluate the expression. Return an integer that represents the value of the expression.

Note:
- Valid operators are '+', '-', '*', and '/'.
- Division between two integers should **truncate toward zero**.
- The expression is always valid.

### Examples

```
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
```

### Constraints
- 1 <= tokens.length <= 10^4
- tokens[i] is an operator or an integer in range [-200, 200]

## Intuition

**Reverse Polish Notation (RPN)** = Postfix notation
- Operators come AFTER operands
- No parentheses needed
- Evaluated left to right with stack

**Algorithm**: 
- Numbers go on the stack
- Operators pop two operands, compute, push result
- Final answer is the only element left on stack

## Approach

```
1. Create stack for operands
2. For each token:
   a. If number: push to stack
   b. If operator:
      - Pop two operands (b, then a)
      - Compute a OP b
      - Push result
3. Return stack top
```

## Visual Walkthrough

### Example: tokens = ["2", "1", "+", "3", "*"]

```
Token '2': Stack = [2]
Token '1': Stack = [2, 1]
Token '+': Pop 1, pop 2, push 2+1=3
           Stack = [3]
Token '3': Stack = [3, 3]
Token '*': Pop 3, pop 3, push 3*3=9
           Stack = [9]

Result: 9
```

### Example: tokens = ["4", "13", "5", "/", "+"]

```
Token '4':  Stack = [4]
Token '13': Stack = [4, 13]
Token '5':  Stack = [4, 13, 5]
Token '/':  Pop 5, pop 13, push 13/5=2
            Stack = [4, 2]
Token '+':  Pop 2, pop 4, push 4+2=6
            Stack = [6]

Result: 6
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Single number | `["42"]` | `42` | No operators |
| Negative operand | `["-2","3","*"]` | `-6` | Parse negative |
| Division truncation | `["7","-3","/"]` | `-2` | Truncate toward 0 |
| Subtraction order | `["3","4","-"]` | `-1` | a - b, not b - a |
| Division order | `["10","3","/"]` | `3` | 10/3, not 3/10 |

## Division: Truncate Toward Zero

```
Python's // truncates toward -∞:
7 // -3 = -3  (wrong for this problem)

Correct (truncate toward 0):
int(7 / -3) = int(-2.33) = -2 ✓
```

## Complexity Analysis

- **Time Complexity**: O(n)
  - Each token processed once
  
- **Space Complexity**: O(n)
  - Stack holds at most (n+1)/2 operands

## Common Mistakes

1. **Wrong operand order**: Second pop is first operand (a OP b)
2. **Python division**: Use `int(a/b)` not `a//b` for truncation toward zero
3. **Not handling negative numbers**: "-2" is valid operand
4. **Confusing operator check**: "-" is operator, "-2" is number

## Related Problems

- [Basic Calculator](https://leetcode.com/problems/basic-calculator/) - Infix notation
- [Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)

## Key Takeaways

1. **Stack for expression evaluation**: Classic use case
2. **Postfix = no parentheses**: Order of operations is implicit
3. **Operand order matters**: a OP b, where a is popped second
4. **Truncation toward zero**: `int(a/b)` in Python

