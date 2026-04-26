# Min Stack (LeetCode #155)

## Problem Statement

Design a stack that supports push, pop, top, and retrieving the minimum element in **constant time**.

Implement the `MinStack` class:
- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element val onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

You must implement a solution with **O(1) time complexity** for each function.

### Examples

```
Input:
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output: [null,null,null,null,-3,null,0,-2]

Explanation:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```

### Constraints
- -2^31 <= val <= 2^31 - 1
- Methods pop, top, getMin will always be called on non-empty stacks
- At most 3 * 10^4 calls will be made

## Intuition

The challenge is `getMin()` in O(1). We can't just scan the stack each time (O(n)).

**Key insight**: Track the minimum at each stack level. When we push, we know the minimum is either the new value or the previous minimum.

Two approaches:
1. **Two stacks**: One for values, one for minimums
2. **Single stack with pairs**: Store (value, min_at_this_point)

## Approach

### Approach 1: Two Stacks

```
mainStack: stores all values
minStack:  stores minimums (only push when new value <= current min)

push(val):
  - Push to mainStack
  - If val <= minStack.top() (or minStack is empty): push to minStack

pop():
  - If mainStack.top() == minStack.top(): pop from minStack
  - Pop from mainStack

getMin():
  - Return minStack.top()
```

### Approach 2: Single Stack with Pairs

```
stack: stores (value, min_at_this_level)

push(val):
  - new_min = min(val, current_min) or val if empty
  - Push (val, new_min)

pop():
  - Pop from stack

getMin():
  - Return stack.top().second
```

## Visual Walkthrough

### push(-2), push(0), push(-3)

**Two Stacks Approach:**

```
After push(-2):
mainStack: [-2]
minStack:  [-2]     ← -2 is minimum

After push(0):
mainStack: [-2, 0]
minStack:  [-2]     ← 0 > -2, don't push

After push(-3):
mainStack: [-2, 0, -3]
minStack:  [-2, -3] ← -3 <= -2, push

getMin() → -3 ✓
```

**Pairs Approach:**

```
After push(-2):
stack: [(-2, -2)]

After push(0):
stack: [(-2, -2), (0, -2)]

After push(-3):
stack: [(-2, -2), (0, -2), (-3, -3)]

getMin() → stack[-1][1] = -3 ✓
```

## Edge Cases Analysis

| Edge Case | Operations | Expected | Why It's Tricky |
|-----------|------------|----------|-----------------|
| Single element | push(5), getMin() | 5 | Min of one element |
| Duplicate mins | push(1), push(1), pop() | getMin()=1 | Must keep both 1s in minStack |
| All same | push(5), push(5), push(5) | getMin()=5 | All are minimum |
| Decreasing | push(3), push(2), push(1) | getMin()=1 | Min always changes |
| Increasing | push(1), push(2), push(3) | getMin()=1 | Min never changes |

## Complexity Analysis

### Both Approaches
- **Time Complexity**: O(1) for all operations
  - push: O(1)
  - pop: O(1)
  - top: O(1)
  - getMin: O(1)
  
- **Space Complexity**: O(n)
  - Two stacks: up to 2n elements
  - Pairs: n pairs = 2n values

## Common Mistakes

1. **Using `<` instead of `<=` for minStack**: Must push duplicates
2. **Forgetting to pop from minStack**: When popped value equals min
3. **Not handling empty stack**: Though problem guarantees non-empty

## Why `<=` not `<`?

```
push(1), push(1), pop()

With <=:
minStack: [1, 1] → after pop: [1] → getMin()=1 ✓

With < only:
minStack: [1] → after pop: [] → getMin() fails!
```

## Related Problems

- [Max Stack](https://leetcode.com/problems/max-stack/) - Same but for maximum
- [Min Queue](https://leetcode.com/problems/min-queue/) - Similar for queue

## Key Takeaways

1. **Track state at each level**: Store min alongside each element
2. **Two stacks vs pairs**: Trade-off between space and simplicity
3. **Careful with duplicates**: Use `<=` to handle repeated minimums
4. **O(1) requires preprocessing**: Can't compute on the fly

