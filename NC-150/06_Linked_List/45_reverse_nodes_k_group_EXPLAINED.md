# Reverse Nodes in k-Group - Detailed Explanation

## Problem Statement
Given a linked list, reverse the nodes k at a time. If remaining nodes are fewer than k, leave them as-is.

## Examples
- Input: `[1,2,3,4,5]`, k=2 → Output: `[2,1,4,3,5]`
- Input: `[1,2,3,4,5]`, k=3 → Output: `[3,2,1,4,5]`

## Approach: Group by Group Reversal

### Key Insight
Process the list in groups of k:
1. Check if k nodes exist
2. Reverse those k nodes
3. Connect the reversed group with previous and next parts
4. Move to the next group

### Algorithm Steps
1. Use a dummy node before head
2. Track `prevGroupEnd` (end of previous reversed group)
3. For each group:
   - Find the k-th node (if doesn't exist, we're done)
   - Mark `groupStart` and `nextGroupStart`
   - Reverse nodes from `groupStart` to k-th node
   - Connect: `prevGroupEnd.next = kthNode`, `groupStart.next = nextGroupStart`
   - Update `prevGroupEnd = groupStart`

### Visual Walkthrough
```
List: 1 -> 2 -> 3 -> 4 -> 5, k=2

Initial:
  D -> 1 -> 2 -> 3 -> 4 -> 5
  ↑
prevGroupEnd

Group 1 (1,2):
  kthNode = 2, groupStart = 1, nextGroupStart = 3
  
  Reverse 1,2:
  D    2 -> 1    3 -> 4 -> 5
  
  Connect:
  D -> 2 -> 1 -> 3 -> 4 -> 5
            ↑
       prevGroupEnd (now 1)

Group 2 (3,4):
  kthNode = 4, groupStart = 3, nextGroupStart = 5
  
  Reverse 3,4:
  D -> 2 -> 1    4 -> 3    5
  
  Connect:
  D -> 2 -> 1 -> 4 -> 3 -> 5
                      ↑
                 prevGroupEnd (now 3)

Group 3 (5):
  kthNode = null (only 1 node, k=2 needed)
  Stop.

Result: 2 -> 1 -> 4 -> 3 -> 5
```

## Helper Functions

### getKthNode
```python
def get_kth_node(current, k):
    while current and k > 0:
        current = current.next
        k -= 1
    return current
```
Returns the k-th node from `current`, or None if fewer than k nodes exist.

### reverseList
```python
def reverse_list(start, end):
    prev = None
    curr = start
    stop = end.next
    
    while curr != stop:
        next = curr.next
        curr.next = prev
        prev = curr
        curr = next
```
Reverses nodes from `start` to `end` (inclusive).

## Complexity Analysis
- **Time**: O(n) - each node is visited twice (once to count, once to reverse)
- **Space**: O(1) - only using pointers

## Edge Cases

| Case | Input | k | Output | Notes |
|------|-------|---|--------|-------|
| k = 1 | `[1,2,3]` | 1 | `[1,2,3]` | No change needed |
| k = n | `[1,2,3]` | 3 | `[3,2,1]` | Reverse entire list |
| k > n | `[1,2,3]` | 5 | `[1,2,3]` | No change |
| Single node | `[1]` | 1 | `[1]` | No change |
| Exact multiple | `[1,2,3,4]` | 2 | `[2,1,4,3]` | All groups reversed |

## Common Mistakes

1. **Not tracking connections**: Easy to lose pointers when reversing
2. **Off-by-one in counting**: Make sure to count exactly k nodes
3. **Forgetting dummy node**: Head can change, dummy simplifies this
4. **Wrong stop condition**: Stop when fewer than k nodes remain

## Code Template

```python
def reverseKGroup(head, k):
    dummy = ListNode(0)
    dummy.next = head
    prev_group_end = dummy
    
    while True:
        kth = get_kth_node(prev_group_end, k)
        if not kth:
            break
        
        group_start = prev_group_end.next
        next_group_start = kth.next
        
        # Reverse group
        reverse(group_start, kth)
        
        # Reconnect
        prev_group_end.next = kth
        group_start.next = next_group_start
        
        # Move to next group
        prev_group_end = group_start
    
    return dummy.next
```

## Interview Tips

1. **Draw the connections**: This problem is all about pointer manipulation
2. **Explain the invariants**: What does `prevGroupEnd` always point to?
3. **Test edge cases**: k=1, k=n, k>n
4. **Mention complexity**: O(n) time, O(1) space

## Follow-up Questions

**Q: What if we want to reverse from the end instead?**
A: Count total nodes first, then adjust group boundaries.

**Q: What about recursive solution?**
A: Possible, but uses O(n/k) stack space.

## Related Problems
- Reverse Linked List (building block)
- Swap Nodes in Pairs (k=2 special case)
- Reverse Linked List II (reverse between positions)

