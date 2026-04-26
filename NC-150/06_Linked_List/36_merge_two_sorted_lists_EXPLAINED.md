# Merge Two Sorted Lists - Detailed Explanation

## Problem Statement
Merge two sorted linked lists and return it as a sorted list. The list should be made by splicing together the nodes of the first two lists.

## Examples
- Input: `list1 = [1,2,4]`, `list2 = [1,3,4]` → Output: `[1,1,2,3,4,4]`
- Input: `list1 = []`, `list2 = []` → Output: `[]`
- Input: `list1 = []`, `list2 = [0]` → Output: `[0]`

## Approach 1: Iterative with Dummy Node (Recommended)

### Intuition
Use a dummy node to avoid edge cases with the head. Compare values from both lists, always picking the smaller one to add to the result.

### Algorithm
1. Create a dummy node and a tail pointer
2. While both lists have nodes:
   - Compare current nodes of both lists
   - Attach the smaller one to tail
   - Advance that list's pointer
   - Advance tail
3. Attach the remaining nodes from non-empty list
4. Return dummy.next

### Visual Walkthrough
```
list1: 1 -> 2 -> 4
list2: 1 -> 3 -> 4
dummy: D -> ?

Step 1: Compare 1 vs 1, attach list1's 1
        D -> 1
        list1: 2 -> 4, list2: 1 -> 3 -> 4

Step 2: Compare 2 vs 1, attach list2's 1
        D -> 1 -> 1
        list1: 2 -> 4, list2: 3 -> 4

Step 3: Compare 2 vs 3, attach list1's 2
        D -> 1 -> 1 -> 2
        list1: 4, list2: 3 -> 4

Step 4: Compare 4 vs 3, attach list2's 3
        D -> 1 -> 1 -> 2 -> 3
        list1: 4, list2: 4

Step 5: Compare 4 vs 4, attach list1's 4
        D -> 1 -> 1 -> 2 -> 3 -> 4
        list1: null, list2: 4

Step 6: list1 is null, attach remaining list2
        D -> 1 -> 1 -> 2 -> 3 -> 4 -> 4

Return D.next = 1 -> 1 -> 2 -> 3 -> 4 -> 4
```

### Complexity
- **Time**: O(n + m) - visit each node once
- **Space**: O(1) - only using pointers

### Why Dummy Node?
Without dummy, we'd need special handling for the first node:
```cpp
// Without dummy (more complex)
ListNode* head = nullptr;
if (list1->val <= list2->val) {
    head = list1;
    list1 = list1->next;
} else { ... }
// Then continue with the loop
```

## Approach 2: Recursive

### Intuition
Choose the smaller head as the first element, then recursively merge the rest.

### Algorithm
1. Base case: if either list is empty, return the other
2. If list1's value ≤ list2's value:
   - list1's next = merge(list1.next, list2)
   - return list1
3. Else:
   - list2's next = merge(list1, list2.next)
   - return list2

### Complexity
- **Time**: O(n + m) - one call per node
- **Space**: O(n + m) - recursion stack

## Edge Cases

| Case | list1 | list2 | Output | Notes |
|------|-------|-------|--------|-------|
| Both empty | `[]` | `[]` | `[]` | Handle null |
| One empty | `[]` | `[1]` | `[1]` | Return non-empty |
| Single nodes | `[1]` | `[2]` | `[1,2]` | Simplest merge |
| No overlap | `[1,2]` | `[3,4]` | `[1,2,3,4]` | One finishes first |
| Equal values | `[1,1]` | `[1,1]` | `[1,1,1,1]` | Handle ties |

## Common Mistakes

1. **Forgetting remaining nodes**: After the loop, one list may still have nodes
2. **Wrong condition**: Use `<=` (stable sort) not `<`
3. **Not using dummy**: Makes head handling complex
4. **Memory issues**: Don't create new nodes unnecessarily

## Interview Tips

1. **Clarify**: Ask if in-place modification is okay
2. **Dummy node pattern**: Mention it's a common technique
3. **Edge cases first**: Discuss empty lists upfront
4. **Optimize**: Point out O(1) space advantage of iterative

## Related Problems
- Merge k Sorted Lists (extends this problem)
- Sort List (uses merge sort with this as merge step)
- Merge Sorted Array (similar concept with arrays)

