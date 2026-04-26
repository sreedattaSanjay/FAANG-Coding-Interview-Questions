# Balanced Binary Tree - Detailed Explanation

## Problem Statement
Given a binary tree, determine if it is height-balanced. A tree is height-balanced if the depth of the two subtrees of **every node** never differs by more than one.

## Examples
```
Input:     3           Output: true
          / \
         9  20         Heights: 9→1, 20→2
           / \         Difference at 3: |1-2| = 1 ≤ 1 ✓
          15  7
```

```
Input:       1         Output: false
            / \
           2   2       At node 2: left=2, right=0
          / \          Difference: |2-0| = 2 > 1 ✗
         3   3
        / \
       4   4
```

## Key Insight

We need to check **every** node, not just the root. The tree could be balanced at the root but unbalanced somewhere in a subtree.

## Approach 1: Optimal O(n) Solution

### Algorithm
Combine height calculation with balance checking in a single traversal:
1. Return -1 if subtree is unbalanced
2. Otherwise return the height
3. At each node, check if |leftHeight - rightHeight| > 1

### Code
```python
def isBalanced(root):
    def check_height(node):
        if not node:
            return 0
        
        left_height = check_height(node.left)
        if left_height == -1:
            return -1  # Already unbalanced
        
        right_height = check_height(node.right)
        if right_height == -1:
            return -1  # Already unbalanced
        
        if abs(left_height - right_height) > 1:
            return -1  # Current node unbalanced
        
        return 1 + max(left_height, right_height)
    
    return check_height(root) != -1
```

### Visual Walkthrough
```
        1
       / \
      2   2
     / \
    3   3
   / \
  4   4

check_height(4_left): 0
check_height(4_right): 0
check_height(3_left): |0-0|=0 ≤ 1, return 1
check_height(3_right): |0-0|=0 ≤ 1, return 1
check_height(2_left): |1-1|=0 ≤ 1, return 2
check_height(2_right): |0-0|=0 ≤ 1, return 1
check_height(1): |2-1|=1 ≤ 1, return 3

But wait! We missed something. Let's trace again...

check_height(2_left):
  left = check_height(3_left) = 1
  right = check_height(3_right) = 1
  |1-1| = 0 ≤ 1, return 2

check_height(2_right):
  left = 0, right = 0
  return 1

check_height(1):
  left = 2, right = 2
  |2-2| = 0 ≤ 1... 

Hmm, the example shows [1,2,2,3,3,null,null,4,4]
Let me re-read: node 2's right child is null!

Actually checking node 2_left:
  left = 2 (from 3->4)
  right = 0 (null)
  |2-0| = 2 > 1, return -1 ✓
```

### Complexity
- **Time**: O(n) - visit each node once
- **Space**: O(h) - recursion stack

## Approach 2: Naive O(n²) Solution

### Algorithm
For each node:
1. Calculate height of left subtree
2. Calculate height of right subtree
3. Check if difference > 1
4. Recursively check if subtrees are balanced

### Code
```python
def isBalanced(root):
    def height(node):
        if not node:
            return 0
        return 1 + max(height(node.left), height(node.right))
    
    if not root:
        return True
    
    left_h = height(root.left)
    right_h = height(root.right)
    
    return (abs(left_h - right_h) <= 1 
            and isBalanced(root.left) 
            and isBalanced(root.right))
```

### Why O(n²)?
- For each of n nodes, we calculate height: O(n)
- Total: O(n × n) = O(n²)

In a skewed tree, this is very inefficient.

## Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Optimal | O(n) | O(h) | Single traversal |
| Naive | O(n²) | O(h) | Repeated work |

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty tree | `null` | true | By definition |
| Single node | `[1]` | true | No children to compare |
| Two nodes | `[1,2]` | true | Height diff = 1 |
| Three levels left | `[1,2,null,3]` | false | Height diff = 2 |

## Common Mistakes

1. **Only checking root**: Must check every node
2. **Wrong height calculation**: Base case should return 0, not -1
3. **Short-circuit failure**: In optimal solution, return -1 immediately when unbalanced

## Interview Tips

1. **Start with naive**: Show you understand the problem
2. **Optimize**: Explain why naive is O(n²) and how to improve
3. **Use -1 as sentinel**: Clever trick to combine height and balance check
4. **Discuss trade-offs**: Mention the O(n²) vs O(n) difference

## Definition Variations

Some definitions use:
- "Number of levels" instead of height
- Different thresholds (AVL uses exactly ≤1)

Always clarify what "balanced" means in the interview!

## Related Problems
- Maximum Depth of Binary Tree (simpler height calculation)
- AVL Tree operations (maintains balance)
- Diameter of Binary Tree (similar DFS pattern)

