# Stack

## Pattern Overview

A Stack is a LIFO (Last-In-First-Out) data structure. It's essential for problems involving:
- Matching pairs (parentheses, tags)
- Tracking "most recent" elements
- Monotonic sequences
- Expression evaluation
- Backtracking simulation

## When to Use This Pattern

- **Matching brackets/parentheses** → Push open, pop on close
- **Expression evaluation** → Operand stack for RPN
- **Next greater/smaller element** → Monotonic stack
- **Valid sequence generation** → Backtracking with stack state
- **Undo operations** → Stack to track history
- **Call stack simulation** → Recursive to iterative conversion

## Types of Stack Problems

### 1. Matching/Balancing
```python
stack = []
for char in s:
    if is_open(char):
        stack.append(char)
    elif is_close(char):
        if not stack or not matches(stack.pop(), char):
            return False
return len(stack) == 0
```

### 2. Monotonic Stack
```python
# Find next greater element
stack = []  # Stores indices
for i in range(len(arr)):
    while stack and arr[stack[-1]] < arr[i]:
        # arr[i] is next greater for arr[stack.pop()]
        result[stack.pop()] = arr[i]
    stack.append(i)
```

### 3. Expression Evaluation
```python
stack = []  # Operand stack
for token in tokens:
    if is_number(token):
        stack.append(int(token))
    else:
        b, a = stack.pop(), stack.pop()
        stack.append(apply(token, a, b))
```

## Problems in This Section

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Valid Parentheses](01_valid_parentheses_EXPLAINED.md) | Easy | Stack Matching |
| 2 | [Min Stack](02_min_stack_EXPLAINED.md) | Medium | Auxiliary Min Tracking |
| 3 | [Evaluate Reverse Polish Notation](03_evaluate_reverse_polish_EXPLAINED.md) | Medium | Operand Stack |
| 4 | [Generate Parentheses](04_generate_parentheses_EXPLAINED.md) | Medium | Backtracking |
| 5 | [Daily Temperatures](05_daily_temperatures_EXPLAINED.md) | Medium | Monotonic Stack |
| 6 | [Car Fleet](06_car_fleet_EXPLAINED.md) | Medium | Stack + Sorting |
| 7 | [Largest Rectangle in Histogram](07_largest_rectangle_histogram_EXPLAINED.md) | Hard | Monotonic Stack |

## Suggested Study Order

1. **Valid Parentheses** - Basic stack matching
2. **Min Stack** - Stack with auxiliary tracking
3. **Evaluate Reverse Polish Notation** - Expression evaluation
4. **Generate Parentheses** - Backtracking (uses implicit stack)
5. **Daily Temperatures** - Introduction to monotonic stack
6. **Car Fleet** - Monotonic stack with sorting
7. **Largest Rectangle in Histogram** - Advanced monotonic stack

## Key Concepts

### Monotonic Stack

A stack that maintains elements in sorted (increasing or decreasing) order.

**Monotonic Decreasing Stack** (for next greater):
```
Push elements, pop when current > top
The popped element's "next greater" is current
```

**Monotonic Increasing Stack** (for next smaller):
```
Push elements, pop when current < top
The popped element's "next smaller" is current
```

### When to Use Which Type?

| Find | Stack Type | Condition to Pop |
|------|------------|------------------|
| Next Greater | Decreasing | current > top |
| Next Smaller | Increasing | current < top |
| Previous Greater | Decreasing | Iterate right to left |
| Previous Smaller | Increasing | Iterate right to left |

## Time Complexity

| Operation | Stack |
|-----------|-------|
| Push | O(1) |
| Pop | O(1) |
| Peek | O(1) |
| Search | O(n) |

For monotonic stack problems:
- Each element pushed once, popped at most once
- Total time: O(n)

## Common Mistakes to Avoid

1. **Not checking if stack is empty before pop/peek**
2. **Wrong order for matching**: `(` matches `)`, not vice versa
3. **Forgetting to handle remaining stack elements** after iteration
4. **Using wrong monotonic type**: Increasing vs decreasing
5. **Off-by-one in indices**: Store indices, not values, for position-based problems

