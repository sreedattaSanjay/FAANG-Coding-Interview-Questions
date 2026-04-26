# Linked List Cycle - Detailed Explanation

## Problem Statement
Given the head of a linked list, determine if the linked list has a cycle. A cycle exists if some node can be reached again by continuously following the `next` pointer.

## Examples
- Input: `[3,2,0,-4]` with tail connected to index 1 → Output: `true`
- Input: `[1,2]` with tail connected to index 0 → Output: `true`
- Input: `[1]` with no cycle → Output: `false`

## Approach 1: Floyd's Cycle Detection (Recommended)

### The Algorithm
Also known as "Tortoise and Hare":
1. Use two pointers: slow (moves 1 step) and fast (moves 2 steps)
2. If there's a cycle, they will eventually meet
3. If no cycle, fast will reach the end

### Why Do They Meet?
Imagine slow and fast are on a circular track:
- Fast gains 1 step per iteration relative to slow
- Eventually, fast will "lap" slow and they'll be at the same position

### Mathematical Proof
- Let the cycle have length `C`
- When slow enters the cycle, fast is already some distance ahead
- Each iteration, the gap decreases by 1 (since fast gains 1 step but we measure relative distance)
- After at most `C` iterations, the gap becomes 0 (they meet)

### Visual Walkthrough
```
List: 1 -> 2 -> 3 -> 4
           ↑         ↓
           ←----←----

Initial: slow=1, fast=1
Step 1:  slow=2, fast=3
Step 2:  slow=3, fast=2 (fast wraps around via 4->2)
Step 3:  slow=4, fast=4 ✓ Meet!

Cycle detected!
```

### No Cycle Case
```
List: 1 -> 2 -> 3 -> null

Initial: slow=1, fast=1
Step 1:  slow=2, fast=3
Step 2:  fast.next is null, exit loop

No cycle.
```

## Complexity Analysis
- **Time**: O(n) - In the worst case, we traverse the list
- **Space**: O(1) - Only two pointers

### Why O(n) Time?
- If no cycle: fast reaches end in n/2 iterations
- If cycle: Once slow enters cycle, they meet within C iterations (C ≤ n)

## Approach 2: Hash Set

### Algorithm
1. Traverse the list
2. For each node, check if we've seen it before
3. If yes, there's a cycle; if we reach null, no cycle

### Complexity
- **Time**: O(n)
- **Space**: O(n) - stores all visited nodes

### Trade-off
Simpler to understand but uses O(n) extra space.

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty list | `null` | `false` | Handle null check |
| Single node, no cycle | `[1]` | `false` | One node, points to null |
| Single node, self-cycle | `[1]` → 1 | `true` | Points to itself |
| Two nodes, cycle | `[1,2]` → 1 | `true` | Minimal cycle |
| No cycle | `[1,2,3]` | `false` | Standard case |

## Bonus: Finding Cycle Start

### Algorithm
After slow and fast meet:
1. Reset slow to head
2. Move both one step at a time
3. They meet at the cycle start

### Why Does This Work?
```
Distance from head to cycle start: a
Distance from cycle start to meeting point: b
Cycle length: C

When they meet:
- slow traveled: a + b
- fast traveled: a + b + kC (for some k ≥ 1)

Since fast travels 2x slow:
2(a + b) = a + b + kC
a + b = kC
a = kC - b

This means: traveling 'a' steps from head lands at the same 
position as traveling 'a' steps from meeting point!
```

### Code
```python
def detectCycle(head):
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            slow = head
            while slow != fast:
                slow = slow.next
                fast = fast.next
            return slow  # Cycle start
    return None
```

## Common Mistakes

1. **Wrong initial position**: Both pointers should start at head
2. **Missing null checks**: Check `fast.next` before accessing `fast.next.next`
3. **Return wrong value**: Return boolean, not the meeting point

## Interview Tips

1. **Explain the algorithm**: Use the tortoise and hare analogy
2. **Draw the cycle**: Visual representation helps
3. **Mention O(1) space**: It's the key advantage over hash set
4. **Know the math**: Be ready to explain why they meet

## Related Problems
- Linked List Cycle II (find cycle start)
- Find the Duplicate Number (uses same technique)
- Happy Number (cycle detection in different context)

