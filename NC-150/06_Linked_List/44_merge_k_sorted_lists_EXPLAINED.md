# Merge k Sorted Lists - Detailed Explanation

## Problem Statement
Given an array of k sorted linked lists, merge them into one sorted list.

## Example
- Input: `[[1,4,5],[1,3,4],[2,6]]`
- Output: `[1,1,2,3,4,4,5,6]`

## Approach 1: Divide and Conquer (Recommended)

### Key Insight
Use merge sort logic: repeatedly merge pairs of lists until only one remains.

### Algorithm
1. If 0 lists, return null
2. If 1 list, return that list
3. Split lists into two halves
4. Recursively merge each half
5. Merge the two resulting lists

### Visual Walkthrough
```
Lists: [L1, L2, L3, L4]

Level 1: Split into [L1, L2] and [L3, L4]
Level 2: 
  - [L1, L2] -> merge(L1, L2) -> M1
  - [L3, L4] -> merge(L3, L4) -> M2
Level 3: merge(M1, M2) -> Final Result
```

### Why It's Efficient
- Each level has O(N) total work (processing all nodes)
- There are O(log k) levels
- Total: O(N log k)

### Code
```python
def mergeKLists(lists):
    if not lists:
        return None
    return merge_range(lists, 0, len(lists) - 1)

def merge_range(lists, left, right):
    if left == right:
        return lists[left]
    
    mid = (left + right) // 2
    left_merged = merge_range(lists, left, mid)
    right_merged = merge_range(lists, mid + 1, right)
    
    return merge_two(left_merged, right_merged)
```

### Complexity
- **Time**: O(N log k)
- **Space**: O(log k) for recursion stack

## Approach 2: Min Heap (Priority Queue)

### Key Insight
Always pick the smallest element from all k list heads. A min-heap efficiently finds the minimum.

### Algorithm
1. Add first node of each list to min-heap
2. Pop smallest, add to result
3. Push next node from that list to heap
4. Repeat until heap is empty

### Visual Walkthrough
```
Lists: [1->4->5], [1->3->4], [2->6]

Initial heap: [(1,L1), (1,L2), (2,L3)]
Pop (1,L1): result = [1], heap = [(1,L2), (2,L3), (4,L1)]
Pop (1,L2): result = [1,1], heap = [(2,L3), (4,L1), (3,L2)]
Pop (2,L3): result = [1,1,2], heap = [(3,L2), (4,L1), (6,L3)]
...continue...

Final: [1,1,2,3,4,4,5,6]
```

### Code
```python
import heapq

def mergeKLists(lists):
    heap = []
    for i, node in enumerate(lists):
        if node:
            heapq.heappush(heap, (node.val, i, node))
    
    dummy = ListNode(0)
    tail = dummy
    
    while heap:
        val, idx, node = heapq.heappop(heap)
        tail.next = node
        tail = tail.next
        
        if node.next:
            heapq.heappush(heap, (node.next.val, idx, node.next))
    
    return dummy.next
```

### Complexity
- **Time**: O(N log k) - each of N nodes is pushed/popped once
- **Space**: O(k) - heap holds at most k nodes

## Approach Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Divide & Conquer | O(N log k) | O(log k) | Elegant, less memory |
| Min Heap | O(N log k) | O(k) | Intuitive, streaming |
| One by One | O(Nk) | O(1) | Simple but slow |
| Sequential Merge | O(Nk) | O(1) | Merge all into one |

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty array | `[]` | `null` | No lists to merge |
| Single list | `[[1,2,3]]` | `[1,2,3]` | Just return it |
| Empty lists | `[[],[],[]]` | `null` | All nulls |
| Mixed | `[[],[1,2]]` | `[1,2]` | Skip empty lists |

## Common Mistakes

1. **Not handling null lists**: Filter out null entries
2. **Heap with equal values**: In Python, use (val, index, node) tuple
3. **Off-by-one in divide**: Use inclusive ranges correctly

## Interview Tips

1. **Start with brute force**: Mention O(Nk) approach first
2. **Explain the optimization**: Show how heap/D&C improves to O(N log k)
3. **Draw the divide process**: Visual helps for D&C
4. **Know both approaches**: Interviewers may ask for alternative

## Brute Force for Reference

### Merge One by One
```python
def mergeKLists(lists):
    if not lists:
        return None
    result = lists[0]
    for i in range(1, len(lists)):
        result = merge_two(result, lists[i])
    return result
```

**Time**: O(Nk) - first merge is O(n), second is O(2n), etc.
**Space**: O(1)

This is worse because each merge starts over from the beginning.

## Related Problems
- Merge Two Sorted Lists (building block)
- Sort List (merge sort on linked list)
- Ugly Number II (uses similar heap approach)

