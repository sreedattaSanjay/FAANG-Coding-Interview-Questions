# Copy List with Random Pointer - Detailed Explanation

## Problem Statement
A linked list is given where each node has a `next` pointer and a `random` pointer. The `random` pointer can point to any node in the list or null. Create a **deep copy** of the list.

## Examples
```
Input: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Each pair is [val, random_index]

Output: Deep copy of the same structure
```

## Approach 1: Hash Map (Easier to Understand)

### Key Insight
The challenge is mapping random pointers from the original list to the copy. A hash map solves this by storing `original_node -> copy_node` mappings.

### Algorithm
1. **First pass**: Create all copy nodes and store mappings
2. **Second pass**: Set next and random pointers using the map

### Visual Walkthrough
```
Original: 1 -> 2 -> 3
          ↓    ↓    ↓
Random:  null  1    2

First Pass - Create copies and map:
  Map: {1: 1', 2: 2', 3: 3'}

Second Pass - Set pointers:
  1'.next = map[1.next] = 2'
  1'.random = map[null] = null
  
  2'.next = map[2.next] = 3'
  2'.random = map[1] = 1'
  
  3'.next = map[null] = null
  3'.random = map[2] = 2'
```

### Complexity
- **Time**: O(n) - two passes
- **Space**: O(n) - hash map stores n entries

## Approach 2: Interweaving (O(1) Space)

### Key Insight
Instead of using a hash map, we can interleave copied nodes with originals. This way, `original.next` always points to its copy.

### Algorithm
1. **Interleave**: Create copies and insert after each original
2. **Set random**: For each original, `copy.random = original.random.next`
3. **Separate**: Extract the copy list

### Visual Walkthrough
```
Original: 1 -> 2 -> 3
          ↓        ↓
Random:   3        1

Step 1: Interweave
  1 -> 1' -> 2 -> 2' -> 3 -> 3'

Step 2: Set random pointers
  1'.random = 1.random.next = 3' (3's next is 3')
  2'.random = 2.random.next = 1' (1's next is 1')
  3'.random = null

Step 3: Separate
  Original: 1 -> 2 -> 3
  Copy:     1' -> 2' -> 3'
```

### Why It Works
- `original.next` is always the copy of that node
- `original.random.next` is the copy of the random target
- We can restore original list while extracting copies

### Complexity
- **Time**: O(n) - three passes
- **Space**: O(1) - no extra data structures

## Edge Cases

| Case | Input | Challenge | Solution |
|------|-------|-----------|----------|
| Empty | `null` | No nodes | Return null |
| Single | `[1,0]` | Self-reference | `random.next = copy` works |
| No randoms | All null | Simple case | Just copy next |
| All same random | All point to head | Many-to-one | Map handles it |

## Common Mistakes

1. **Shallow copy**: Just copying pointers instead of creating new nodes
2. **Infinite loop**: When a node's random points to itself
3. **Losing original list**: In interweave approach, not restoring properly
4. **Null handling**: Not checking if `random` is null before accessing `.next`

## Interview Tips

1. **Clarify deep copy**: Explain what deep copy means
2. **Start with hash map**: It's easier and usually acceptable
3. **Mention O(1) space**: Shows advanced knowledge
4. **Draw the interweaving**: Makes the logic clear

## Code Comparison

### Hash Map (Simpler)
```python
def copy(head):
    old_to_new = {None: None}
    curr = head
    while curr:
        old_to_new[curr] = Node(curr.val)
        curr = curr.next
    
    curr = head
    while curr:
        copy = old_to_new[curr]
        copy.next = old_to_new[curr.next]
        copy.random = old_to_new[curr.random]
        curr = curr.next
    
    return old_to_new[head]
```

### Interweaving (O(1) Space)
```python
def copy(head):
    # Step 1: Interleave
    curr = head
    while curr:
        copy = Node(curr.val, curr.next)
        curr.next = copy
        curr = copy.next
    
    # Step 2: Set random
    curr = head
    while curr:
        if curr.random:
            curr.next.random = curr.random.next
        curr = curr.next.next
    
    # Step 3: Separate
    dummy = Node(0)
    copy_tail = dummy
    curr = head
    while curr:
        copy_tail.next = curr.next
        copy_tail = copy_tail.next
        curr.next = curr.next.next
        curr = curr.next
    
    return dummy.next
```

## Related Problems
- Clone Graph (similar deep copy concept)
- Clone Binary Tree With Random Pointer
- Clone N-ary Tree

