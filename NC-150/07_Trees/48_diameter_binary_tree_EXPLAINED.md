# Diameter of Binary Tree - Detailed Explanation

## Problem Statement
Given the root of a binary tree, return the length of the diameter. The diameter is the longest path between any two nodes (measured in number of **edges**).

**Important**: The path may or may not pass through the root!

## Examples
```
Input:      1           Output: 3
           / \
          2   3         Longest path: 4-2-1-3 or 5-2-1-3
         / \            (3 edges)
        4   5
```

## Key Insight

The diameter path through any node equals:
- **left subtree height + right subtree height**

We calculate height for each node while tracking the maximum diameter seen.

## Approach: DFS with Height Calculation

### Algorithm
1. For each node, calculate height of left and right subtrees
2. The path through this node = leftHeight + rightHeight
3. Update global maximum diameter
4. Return height of current subtree

### Why It Works
- Every node is a potential "peak" of the longest path
- The path goes down left, turns at the node, goes down right
- By checking every node, we find the true maximum

### Visual Walkthrough
```
        1
       / \
      2   3
     / \
    4   5

At node 4: leftHeight=0, rightHeight=0, path=0, height=1
At node 5: leftHeight=0, rightHeight=0, path=0, height=1
At node 2: leftHeight=1, rightHeight=1, path=2, height=2
At node 3: leftHeight=0, rightHeight=0, path=0, height=1
At node 1: leftHeight=2, rightHeight=1, path=3, height=3

Maximum diameter = 3
```

### Code
```python
def diameterOfBinaryTree(root):
    diameter = 0
    
    def height(node):
        nonlocal diameter
        if not node:
            return 0
        
        left_height = height(node.left)
        right_height = height(node.right)
        
        # Update diameter (path through this node)
        diameter = max(diameter, left_height + right_height)
        
        # Return height
        return 1 + max(left_height, right_height)
    
    height(root)
    return diameter
```

## Important: Diameter Not Through Root

```
        1
       /
      2
     / \
    3   4
   /     \
  5       6

The longest path is 5-3-2-4-6 (4 edges)
This path doesn't include the root (node 1)!
```

This is why we must check every node, not just the root.

## Complexity Analysis
- **Time**: O(n) - visit each node once
- **Space**: O(h) - recursion stack
  - Worst case (skewed): O(n)
  - Best case (balanced): O(log n)

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty tree | `null` | 0 | No edges |
| Single node | `[1]` | 0 | No edges |
| Two nodes | `[1,2]` | 1 | One edge |
| Balanced | `[1,2,3,4,5,6,7]` | 4 | Path through root |
| Skewed | `[1,2,null,3,null,4]` | 3 | Linear path |

## Common Mistakes

1. **Counting nodes instead of edges**: The answer is edges, not nodes
2. **Only checking root**: The diameter might not pass through root
3. **Returning diameter from height function**: Keep them separate

## Alternative: No Global Variable

```python
def diameterOfBinaryTree(root):
    def dfs(node):
        # Returns (height, max_diameter)
        if not node:
            return 0, 0
        
        left_h, left_d = dfs(node.left)
        right_h, right_d = dfs(node.right)
        
        current_diameter = left_h + right_h
        max_diameter = max(current_diameter, left_d, right_d)
        
        return 1 + max(left_h, right_h), max_diameter
    
    return dfs(root)[1]
```

This avoids global state but is slightly more complex.

## Interview Tips

1. **Clarify edges vs nodes**: Make sure you understand what to count
2. **Explain the insight**: Diameter through a node = sum of subtree heights
3. **Draw the example**: Show a case where diameter doesn't go through root
4. **Discuss complexity**: O(n) time, O(h) space

## Relationship to Height

| Concept | Definition | Counting |
|---------|------------|----------|
| Height | Longest path from node to leaf | Edges |
| Depth | Distance from root to node | Edges |
| Diameter | Longest path between any two nodes | Edges |

Note: LeetCode 104 (Maximum Depth) counts **nodes**, while this problem counts **edges**.

## Related Problems
- Maximum Depth of Binary Tree
- Binary Tree Maximum Path Sum (similar pattern, with values)
- Balanced Binary Tree (uses height calculation)

