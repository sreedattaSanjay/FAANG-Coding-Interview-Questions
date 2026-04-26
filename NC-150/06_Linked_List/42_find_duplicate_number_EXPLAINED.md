# Find the Duplicate Number - Detailed Explanation

## Problem Statement
Given an array containing `n + 1` integers where each integer is in range `[1, n]`, find the duplicate number.

**Constraints:**
- Cannot modify the array
- Must use O(1) extra space

## Examples
- Input: `[1,3,4,2,2]` → Output: `2`
- Input: `[3,1,3,4,2]` → Output: `3`

## Approach: Floyd's Cycle Detection

### Key Insight: Array as Linked List
Treat the array as a linked list where:
- Index `i` is a "node"
- `nums[i]` is the "next pointer" (points to another index)

Since values are in `[1, n]` and we have `n + 1` elements, there must be a duplicate, which creates a **cycle** in this implicit linked list.

### Why a Cycle?
```
Array: [1, 3, 4, 2, 2]
Index:  0  1  2  3  4

Following the "links":
0 -> nums[0]=1 -> nums[1]=3 -> nums[3]=2 -> nums[2]=4 -> nums[4]=2 (back to 2!)

       0 -> 1 -> 3 -> 2 -> 4
                 ↑         ↓
                 ←----←----

The duplicate (2) is the entrance to the cycle!
```

### Algorithm
Same as finding cycle start in linked list:

**Phase 1**: Find meeting point
```python
slow = nums[0]
fast = nums[0]
while True:
    slow = nums[slow]        # One step
    fast = nums[nums[fast]]  # Two steps
    if slow == fast:
        break
```

**Phase 2**: Find cycle entrance (the duplicate)
```python
slow = nums[0]
while slow != fast:
    slow = nums[slow]
    fast = nums[fast]
return slow  # This is the duplicate!
```

### Visual Walkthrough
```
Array: [1, 3, 4, 2, 2]
       0  1  2  3  4

Start at index 0:
- slow = nums[0] = 1
- fast = nums[nums[0]] = nums[1] = 3

Phase 1:
slow: 0 -> 1 -> 3 -> 2 -> 4 -> 2 -> 4 -> ...
fast: 0 -> 3 -> 4 -> 4 -> 4 -> ...

Wait, let me trace correctly:
slow = nums[0] = 1
fast = nums[nums[0]] = nums[1] = 3

Iteration 1:
  slow = nums[1] = 3
  fast = nums[nums[3]] = nums[2] = 4

Iteration 2:
  slow = nums[3] = 2
  fast = nums[nums[4]] = nums[2] = 4

Iteration 3:
  slow = nums[2] = 4
  fast = nums[nums[4]] = nums[2] = 4

slow == fast at value 4 (they're both pointing to index 4)

Phase 2:
Reset slow to nums[0] = 1
slow = 1, fast = 4

Iteration 1:
  slow = nums[1] = 3
  fast = nums[4] = 2

Iteration 2:
  slow = nums[3] = 2
  fast = nums[2] = 4

Hmm, slow = 2, fast = 4 (not equal)

Iteration 3:
  slow = nums[2] = 4
  fast = nums[4] = 2

Wait, I need to reconsider...

Actually the duplicate IS 2, and it creates a cycle because:
- nums[2] = 4, nums[4] = 2 (cycle: 2 -> 4 -> 2 -> 4 ...)

The entrance to this cycle (where we can reach it from outside) is 2.
```

### Why Does This Work?
The duplicate number appears at multiple indices. Following the "next" pointers eventually leads to a cycle, and the entrance to that cycle is precisely the duplicate value.

## Complexity Analysis
- **Time**: O(n) - at most 2n iterations
- **Space**: O(1) - only two pointers

## Alternative: Binary Search

### Idea
- Count numbers ≤ mid
- If count > mid, duplicate is in [1, mid]
- Otherwise, duplicate is in [mid+1, n]

### Why This Works
By pigeonhole principle: if we have `n` numbers in range [1, n] and count of numbers ≤ mid is greater than mid, there must be duplicates in that range.

### Complexity
- **Time**: O(n log n) - binary search with O(n) counting each iteration
- **Space**: O(1)

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Minimal | `[1,1]` | `1` | Two elements, one duplicate |
| Duplicate at end | `[1,2,3,4,4]` | `4` | Duplicate is max value |
| Duplicate at start | `[1,1,2,3,4]` | `1` | Duplicate is min value |
| Many duplicates | `[2,2,2,2,2]` | `2` | All same, still works |

## Common Mistakes

1. **Starting from index 1**: Must start from `nums[0]` to ensure we enter the "linked list"
2. **Confusing index and value**: The cycle is in values, not indices
3. **Using do-while correctly**: In Phase 1, must move first, then compare

## Interview Tips

1. **Explain the abstraction**: "I'll treat the array as a linked list"
2. **Draw the cycle**: Visual representation makes it clear
3. **Know alternatives**: Mention binary search as O(n log n) option
4. **Understand constraints**: Cannot sort (modifies array), cannot use hash (O(n) space)

## Related Problems
- Linked List Cycle (same algorithm)
- Linked List Cycle II (find cycle start)
- Missing Number (similar constraint handling)

