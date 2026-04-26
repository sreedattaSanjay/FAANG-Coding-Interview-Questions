# Add Two Numbers - Detailed Explanation

## Problem Statement
You are given two non-empty linked lists representing non-negative integers. The digits are stored in **reverse order**, and each node contains a single digit. Add the two numbers and return the sum as a linked list.

## Examples
- Input: `l1 = [2,4,3]`, `l2 = [5,6,4]`
- Numbers: 342 + 465 = 807
- Output: `[7,0,8]`

## Why Reverse Order?
The reverse order is actually **convenient**! When we add numbers by hand, we start from the rightmost digit (ones place). In this representation, the ones place is at the head of the list, so we can simply iterate from head to tail.

## Approach: Elementary Math Simulation

### Key Insight
Simulate how we add numbers by hand:
1. Add corresponding digits
2. Handle carry for sums ≥ 10
3. Continue until both lists and carry are exhausted

### Algorithm
1. Create a dummy node to build result
2. Initialize carry = 0
3. While either list has nodes OR carry exists:
   - sum = carry + l1.val (if exists) + l2.val (if exists)
   - carry = sum / 10
   - Create new node with sum % 10
   - Advance pointers
4. Return dummy.next

### Visual Walkthrough
```
l1: 2 -> 4 -> 3     (342)
l2: 5 -> 6 -> 4     (465)

Step 1: 2 + 5 + 0 = 7
        result: 7
        carry: 0

Step 2: 4 + 6 + 0 = 10
        result: 7 -> 0
        carry: 1

Step 3: 3 + 4 + 1 = 8
        result: 7 -> 0 -> 8
        carry: 0

Final: 7 -> 0 -> 8 (807)
```

### Different Lengths
```
l1: 9 -> 9         (99)
l2: 1              (1)

Step 1: 9 + 1 = 10
        result: 0
        carry: 1

Step 2: 9 + 0 + 1 = 10
        result: 0 -> 0
        carry: 1

Step 3: 0 + 0 + 1 = 1 (just carry)
        result: 0 -> 0 -> 1
        carry: 0

Final: 0 -> 0 -> 1 (100)
```

## Complexity Analysis
- **Time**: O(max(n, m)) - process all nodes once
- **Space**: O(max(n, m)) - result list size

## Edge Cases

| Case | l1 | l2 | Output | Notes |
|------|----|----|--------|-------|
| Both zero | `[0]` | `[0]` | `[0]` | Simple case |
| Different lengths | `[1,2,3]` | `[4,5]` | `[5,7,3]` | Handle missing nodes |
| Carry at end | `[9,9]` | `[1]` | `[0,0,1]` | Extra digit needed |
| Large carry chain | `[9,9,9]` | `[1]` | `[0,0,0,1]` | Multiple carries |

## Common Mistakes

1. **Forgetting final carry**: After processing both lists, carry might still be 1
2. **Not handling different lengths**: Check both lists in loop condition
3. **Off-by-one with digits**: sum % 10 for digit, sum / 10 for carry

## Code Template
```python
def addTwoNumbers(l1, l2):
    dummy = ListNode(0)
    curr = dummy
    carry = 0
    
    while l1 or l2 or carry:
        sum = carry
        if l1:
            sum += l1.val
            l1 = l1.next
        if l2:
            sum += l2.val
            l2 = l2.next
        
        carry = sum // 10
        curr.next = ListNode(sum % 10)
        curr = curr.next
    
    return dummy.next
```

## Interview Tips

1. **Clarify direction**: Confirm digits are in reverse order
2. **Mention carry**: Show you understand multi-digit addition
3. **Handle edge cases**: Empty lists, different lengths, large numbers
4. **Dummy node**: Explain why it simplifies the code

## Follow-up Questions

**Q: What if digits are in forward order?**
A: Options include:
1. Reverse both lists, add, reverse result
2. Use a stack to access digits in reverse
3. Pad shorter list with leading zeros

**Q: Can we do it without extra space for result?**
A: Not really - we need to store the result somewhere

## Related Problems
- Add Two Numbers II (forward order - use stacks)
- Plus One (add 1 to number represented as array)
- Multiply Strings (similar digit-by-digit arithmetic)

