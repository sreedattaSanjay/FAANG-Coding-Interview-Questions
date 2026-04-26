# Maximum Depth of Binary Tree - Detailed Explanation

## Problem Statement
Given the root of a binary tree, return its maximum depth. The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

## Examples
```
Input:    3           Output: 3
         / \
        9  20         Path: 3 -> 20 -> 7 (or 15)
           / \
          15  7
```

## Approach 1: Recursive DFS (Recommended)

### Key Insight
The depth of a tree is 1 plus the maximum of its subtrees' depths.

### Algorithm
1. Base case: if node is null, return 0
2. Recursively get depth of left subtree
3. Recursively get depth of right subtree
4. Return 1 + max(left_depth, right_depth)

### Code
```python
def maxDepth(root):
    if not root:
        return 0
    
    left_depth = maxDepth(root.left)
    right_depth = maxDepth(root.right)
    
    return 1 + max(left_depth, right_depth)
```

### Visual Walkthrough
```
        3
       / \
      9  20
         / \
        15  7

maxDepth(3):
  left = maxDepth(9):
    left = maxDepth(null) = 0
    right = maxDepth(null) = 0
    return 1 + max(0, 0) = 1
  
  right = maxDepth(20):
    left = maxDepth(15):
      return 1 + max(0, 0) = 1
    right = maxDepth(7):
      return 1 + max(0, 0) = 1
    return 1 + max(1, 1) = 2
  
  return 1 + max(1, 2) = 3
```

### Complexity
- **Time**: O(n) - visit each node once
- **Space**: O(h) - recursion stack, where h = height
  - Worst case (skewed): O(n)
  - Best case (balanced): O(log n)

## Approach 2: Iterative BFS

### Key Insight
BFS naturally processes level by level. Count the number of levels.

### Algorithm
1. Use a queue for level-order traversal
2. For each level, process all nodes and add their children
3. Increment depth counter after each level
4. Return final depth count

### Code
```python
def maxDepth(root):
    if not root:
        return 0
    
    queue = deque([root])
    depth = 0
    
    while queue:
        depth += 1
        level_size = len(queue)
        
        for _ in range(level_size):
            node = queue.popleft()
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
    
    return depth
```

### Complexity
- **Time**: O(n)
- **Space**: O(w) where w is maximum width of tree
  - Worst case (perfect tree): O(n/2) ≈ O(n)

## Approach 3: Iterative DFS

### Algorithm
Use a stack, tracking depth with each node.

### Code
```python
def maxDepth(root):
    if not root:
        return 0
    
    stack = [(root, 1)]
    max_depth = 0
    
    while stack:
        node, depth = stack.pop()
        max_depth = max(max_depth, depth)
        
        if node.left:
            stack.append((node.left, depth + 1))
        if node.right:
            stack.append((node.right, depth + 1))
    
    return max_depth
```

### Complexity
- **Time**: O(n)
- **Space**: O(h)

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty tree | `null` | 0 | Handle null check |
| Single node | `[1]` | 1 | Leaf is at depth 1 |
| Left skewed | `[1,2,null,3]` | 3 | All nodes on left |
| Right skewed | `[1,null,2,null,3]` | 3 | All nodes on right |
| Balanced | `[1,2,3,4,5,6,7]` | 3 | Symmetric tree |

## Approach Comparison

| Approach | Time | Space | Best For |
|----------|------|-------|----------|
| Recursive DFS | O(n) | O(h) | Simple, clean code |
| BFS | O(n) | O(w) | Level-order intuition |
| Iterative DFS | O(n) | O(h) | Avoiding recursion |

## Common Mistakes

1. **Off-by-one errors**: Counting edges vs nodes (we count nodes)
2. **Not handling null**: Always check for empty tree
3. **Confusing depth and height**: They're the same for this problem

## Interview Tips

1. **Clarify the definition**: Depth = number of nodes, not edges
2. **Start with recursion**: It's the most intuitive
3. **Mention alternatives**: Show you know BFS and iterative approaches
4. **Discuss trade-offs**: Space complexity differs between approaches

## One-Liner Solution
```python
def maxDepth(root):
    return 0 if not root else 1 + max(maxDepth(root.left), maxDepth(root.right))
```

Elegant but harder to debug. Use in interviews only if you're confident.

## Related Problems
- Minimum Depth of Binary Tree
- Balanced Binary Tree (uses depth calculation)
- Diameter of Binary Tree

