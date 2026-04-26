# Reverse Linked List - Detailed Explanation

## Problem Statement
Given the head of a singly linked list, reverse the list, and return the reversed list.

## Examples
- Input: `[1,2,3,4,5]` → Output: `[5,4,3,2,1]`
- Input: `[1,2]` → Output: `[2,1]`
- Input: `[]` → Output: `[]`

## Approach 1: Iterative (Recommended)

### Intuition
We need to reverse the direction of all links. Instead of each node pointing to its next node, we want it to point to its previous node.

### Algorithm
1. Initialize three pointers: `prev = null`, `curr = head`
2. Iterate through the list:
   - Save `curr.next` before modifying it
   - Reverse the link: `curr.next = prev`
   - Move `prev` and `curr` forward
3. Return `prev` (the new head)

### Visual Walkthrough
```
Original: 1 -> 2 -> 3 -> null

Step 1: prev=null, curr=1
        null <- 1    2 -> 3 -> null
        
Step 2: prev=1, curr=2
        null <- 1 <- 2    3 -> null
        
Step 3: prev=2, curr=3
        null <- 1 <- 2 <- 3    null
        
Step 4: prev=3, curr=null
        Return prev (which is 3, the new head)
```

### Complexity
- **Time**: O(n) - single pass
- **Space**: O(1) - only three pointers

## Approach 2: Recursive

### Intuition
Trust that the recursive call reverses everything after the current node. Then, we just need to:
1. Make the next node point back to us
2. Remove our forward link

### Algorithm
1. Base case: if `head` is null or has no next, return `head`
2. Recursively reverse the rest: `newHead = reverse(head.next)`
3. Fix the links: `head.next.next = head` and `head.next = null`
4. Return `newHead`

### Visual Walkthrough
```
reverse(1 -> 2 -> 3 -> null)

Recurse down to base case:
reverse(1) calls reverse(2) calls reverse(3)
reverse(3) returns 3 (base case: only one node)

Unwind:
- At node 2: 2.next.next = 2 means 3.next = 2
            2.next = null
            List: 3 -> 2 -> null
            
- At node 1: 1.next.next = 1 means 2.next = 1
            1.next = null
            List: 3 -> 2 -> 1 -> null
```

### Complexity
- **Time**: O(n) - visit each node once
- **Space**: O(n) - recursion stack depth

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty list | `null` | `null` | Both solutions handle this |
| Single node | `[1]` | `[1]` | No change needed |
| Two nodes | `[1,2]` | `[2,1]` | Simplest reversal case |
| Long list | `[1,2,...,n]` | `[n,...,2,1]` | Standard case |

## Common Mistakes

1. **Losing the next pointer**: Always save `curr.next` before modifying it
2. **Wrong return value**: Return `prev`, not `curr` (which is null at the end)
3. **Not handling null**: Check for empty list at the start

## Interview Tips

1. **Start simple**: Draw the linked list and trace through a few steps
2. **Use clear variable names**: `prev`, `curr`, `nextTemp` are standard
3. **Edge cases first**: Mention empty list and single node cases upfront
4. **Tradeoffs**: Discuss iterative (O(1) space) vs recursive (cleaner code but O(n) space)

## Related Problems
- Reverse Linked List II (reverse portion of list)
- Palindrome Linked List (uses reversal)
- Reverse Nodes in k-Group (extends this concept)
