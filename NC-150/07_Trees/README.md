# Trees Problems

This folder contains solutions to the **Trees** category from NeetCode 150.

## Problem List

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Invert Binary Tree](01_invert_binary_tree.cpp) | Easy | DFS/BFS |
| 2 | [Maximum Depth of Binary Tree](02_maximum_depth_binary_tree.cpp) | Easy | DFS/BFS |
| 3 | [Diameter of Binary Tree](03_diameter_binary_tree.cpp) | Easy | DFS |
| 4 | [Balanced Binary Tree](04_balanced_binary_tree.cpp) | Easy | DFS |
| 5 | [Same Tree](05_same_tree.cpp) | Easy | DFS/BFS |

## TreeNode Definition
```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

## Key Concepts

### Tree Traversal Patterns

**Depth-First Search (DFS)**
- Preorder: Node → Left → Right
- Inorder: Left → Node → Right
- Postorder: Left → Right → Node

**Breadth-First Search (BFS)**
- Level by level traversal
- Uses a queue

### Common Patterns

1. **Recursive DFS**
   - Base case: null node
   - Combine results from left and right subtrees

2. **Iterative DFS**
   - Use a stack
   - Similar to recursion but explicit stack management

3. **BFS with Queue**
   - Process level by level
   - Good for level-order operations

4. **Tree Height/Depth**
   - Height: Distance from node to deepest leaf
   - Depth: Distance from root to node

## Time/Space Complexity Patterns

| Operation | Time | Space |
|-----------|------|-------|
| DFS Traversal | O(n) | O(h) |
| BFS Traversal | O(n) | O(w) |
| Search in BST | O(h) | O(h) |
| Insert in BST | O(h) | O(h) |

Where:
- n = number of nodes
- h = height of tree (log n for balanced, n for skewed)
- w = maximum width of tree

