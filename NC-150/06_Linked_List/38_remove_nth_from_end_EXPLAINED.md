# Remove Nth Node From End of List - Detailed Explanation

## Problem Statement
Given the head of a linked list, remove the nth node from the end of the list and return its head.

## Examples
- Input: `head = [1,2,3,4,5], n = 2` → Output: `[1,2,3,5]`
- Input: `head = [1], n = 1` → Output: `[]`
- Input: `head = [1,2], n = 2` → Output: `[2]`

## Approach: Two Pointers with Gap (Recommended)

### Key Insight
If we maintain a gap of `n` nodes between two pointers, when the fast pointer reaches the end, the slow pointer will be exactly at the node before the one we want to remove.

### Algorithm
1. Create a dummy node pointing to head (handles edge case)
2. Move fast pointer `n + 1` steps ahead
3. Move both pointers until fast reaches null
4. Remove slow.next
5. Return dummy.next

### Why n + 1 Steps?
We want slow to stop **one before** the target node so we can modify `slow.next`.

### Visual Walkthrough
```
List: 1 -> 2 -> 3 -> 4 -> 5, n = 2

Step 1: Create dummy
        D -> 1 -> 2 -> 3 -> 4 -> 5
        ↑
      fast,slow

Step 2: Move fast n+1 = 3 steps
        D -> 1 -> 2 -> 3 -> 4 -> 5
        ↑              ↑
       slow          fast

Step 3: Move both until fast is null
        D -> 1 -> 2 -> 3 -> 4 -> 5 -> null
                       ↑              ↑
                     slow           fast

Step 4: Remove slow.next (which is 4)
        D -> 1 -> 2 -> 3 -> 5

Result: 1 -> 2 -> 3 -> 5
```

### Why Dummy Node?
Handles the edge case of removing the head:
```
List: 1 -> 2, n = 2 (remove the head)

Without dummy: Need special handling for head
With dummy: D -> 1 -> 2, slow ends at D, remove D.next normally
```

## Complexity Analysis
- **Time**: O(n) - single pass through the list
- **Space**: O(1) - only using pointers

## Alternative: Two-Pass Approach

### Algorithm
1. First pass: count total nodes (length L)
2. Find the node at position `L - n - 1` (one before target)
3. Remove the next node

### Trade-off
- Simpler to understand
- Two passes instead of one (still O(n))

## Edge Cases

| Case | Input | n | Output | Challenge |
|------|-------|---|--------|-----------|
| Single node | `[1]` | 1 | `[]` | Remove the only node |
| Remove head | `[1,2]` | 2 | `[2]` | Remove first element |
| Remove last | `[1,2]` | 1 | `[1]` | Remove last element |
| Long list | `[1,2,3,4,5]` | 2 | `[1,2,3,5]` | Standard case |

## Common Mistakes

1. **Off-by-one errors**: Moving fast `n` steps instead of `n+1`
2. **Forgetting dummy**: Makes removing head complex
3. **Not handling single node**: Results in null pointer issues
4. **Wrong pointer updates**: Skipping the wrong node

## Interview Tips

1. **Clarify constraints**: Is n always valid? (Usually yes in interviews)
2. **Mention the gap technique**: It's a classic linked list pattern
3. **Explain dummy node**: Shows understanding of edge cases
4. **One-pass advantage**: Mention it's more efficient if asked about optimization

## Follow-up Questions

**Q: Can you do this in one pass?**
A: Yes, the two-pointer approach with a gap of n is a one-pass solution.

**Q: What if n could be invalid (larger than list length)?**
A: Add a check after moving fast pointer:
```cpp
if (fast == nullptr) {
    // n equals list length, remove head
    return head->next;
}
```

## Related Problems
- Delete Node in a Linked List
- Remove Linked List Elements
- Middle of the Linked List (similar two-pointer technique)

