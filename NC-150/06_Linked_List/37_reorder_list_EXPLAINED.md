# Reorder List - Detailed Explanation

## Problem Statement
Given a singly linked list: `L0 → L1 → … → Ln-1 → Ln`
Reorder it to: `L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …`

You must modify nodes in-place without changing values.

## Examples
- Input: `[1,2,3,4]` → Output: `[1,4,2,3]`
- Input: `[1,2,3,4,5]` → Output: `[1,5,2,4,3]`

## Approach: Three-Step Process

### Key Insight
The result is formed by:
1. Taking from the front
2. Taking from the back
3. Alternating between them

To efficiently access the back, we reverse the second half.

### Algorithm
1. **Find the middle** using slow-fast pointers
2. **Reverse the second half** of the list
3. **Merge alternately** the two halves

### Visual Walkthrough
```
Original: 1 -> 2 -> 3 -> 4 -> 5

Step 1: Find middle (slow ends at 3)
        First half:  1 -> 2 -> 3
        Second half: 4 -> 5

Step 2: Reverse second half
        First half:  1 -> 2 -> 3
        Second half: 5 -> 4

Step 3: Merge alternately
        1 -> 5 -> 2 -> 4 -> 3 (middle stays at end)
```

### Why This Works for Odd/Even Length
- **Even length** (1,2,3,4): First half has 2, second half has 2
- **Odd length** (1,2,3,4,5): First half has 3, second half has 2
  - The middle element stays at the end

### Detailed Code Walkthrough

#### Step 1: Find Middle
```cpp
slow = head, fast = head
while (fast.next && fast.next.next):
    slow = slow.next
    fast = fast.next.next
// slow is now at the middle
```

For `[1,2,3,4,5]`:
- Initial: slow=1, fast=1
- After 1st: slow=2, fast=3
- After 2nd: slow=3, fast=5 (fast.next.next is null, stop)
- slow is at 3 (middle)

#### Step 2: Reverse Second Half
```cpp
secondHalf = reverse(slow.next)  // Reverse from 4 onwards
slow.next = null  // Cut: 1->2->3 becomes separate
```

#### Step 3: Merge
```cpp
while (secondHalf):
    temp1 = first.next   // Save next nodes
    temp2 = second.next
    
    first.next = second  // Link first to second
    second.next = temp1  // Link second to first's old next
    
    first = temp1        // Move pointers
    second = temp2
```

## Complexity Analysis
- **Time**: O(n) - Three passes: find middle, reverse, merge
- **Space**: O(1) - Only using pointers

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty | `null` | `null` | Early return |
| Single | `[1]` | `[1]` | No change needed |
| Two nodes | `[1,2]` | `[1,2]` | No change needed |
| Three nodes | `[1,2,3]` | `[1,3,2]` | Odd length |
| Four nodes | `[1,2,3,4]` | `[1,4,2,3]` | Even length |

## Alternative Approaches

### 1. Using Stack (O(n) space)
```python
# Push second half onto stack, then interleave
stack = []
slow, fast = head, head
while fast and fast.next:
    slow = slow.next
    fast = fast.next.next
    
while slow:
    stack.append(slow)
    slow = slow.next
    
# Pop from stack to interleave
```

### 2. Using Array (O(n) space)
```python
# Store all nodes in array, use two pointers
nodes = []
curr = head
while curr:
    nodes.append(curr)
    curr = curr.next
    
# Relink using indices
```

These are simpler but use extra space.

## Common Mistakes

1. **Off-by-one in middle finding**: The condition matters for odd/even handling
2. **Not cutting the list**: Must set `slow.next = null` to separate halves
3. **Wrong merge order**: Be careful with the alternating pattern

## Interview Tips

1. **Break down the problem**: Explain the three-step approach clearly
2. **Draw examples**: Show both odd and even length cases
3. **Mention alternatives**: Show you know simpler O(n) space solutions
4. **Edge cases**: Handle empty, single, and two-node cases

## Related Problems
- Palindrome Linked List (uses same find-middle and reverse pattern)
- Middle of the Linked List (Step 1 of this problem)
- Reverse Linked List (Step 2 of this problem)

