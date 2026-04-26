# Invert Binary Tree - Detailed Explanation

## Problem Statement
Given the root of a binary tree, invert the tree, and return its root. Inverting means swapping left and right children at every node.

## Famous Story
This is the problem that Homebrew's creator Max Howell famously failed during a Google interview, leading to his tweet: "Google: 90% of our engineers use the software you wrote (Homebrew), but you can't invert a binary tree on a whiteboard so f*** off."

## Examples
```
Input:     4              Output:    4
         /   \                     /   \
        2     7         →        7     2
       / \   / \                / \   / \
      1   3 6   9              9   6 3   1
```

## Approach 1: Recursive DFS (Recommended)

### Key Insight
At each node, swap its children, then recursively invert subtrees.

### Algorithm
1. Base case: if node is null, return null
2. Swap left and right children
3. Recursively invert left subtree
4. Recursively invert right subtree
5. Return the node

### Code
```python
def invertTree(root):
    if not root:
        return None
    
    # Swap children
    root.left, root.right = root.right, root.left
    
    # Recursively invert subtrees
    invertTree(root.left)
    invertTree(root.right)
    
    return root
```

### Complexity
- **Time**: O(n) - visit each node once
- **Space**: O(h) - recursion stack, h = height

## Approach 2: Iterative BFS

### Algorithm
Use a queue to process level by level, swapping children at each node.

### Code
```python
def invertTree(root):
    if not root:
        return None
    
    queue = deque([root])
    
    while queue:
        node = queue.popleft()
        node.left, node.right = node.right, node.left
        
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)
    
    return root
```

### Complexity
- **Time**: O(n)
- **Space**: O(w) where w is maximum width of tree

## Approach 3: Iterative DFS

### Algorithm
Use a stack instead of queue, otherwise similar to BFS.

### Complexity
- **Time**: O(n)
- **Space**: O(h) - stack depth equals tree height

## Visual Walkthrough

```
Original:      4
             /   \
            2     7
           / \   / \
          1   3 6   9

After inverting root's children:
               4
             /   \
            7     2      (swapped 2 and 7)
           / \   / \
          6   9 1   3

After inverting 7's children:
               4
             /   \
            7     2
           / \   / \
          9   6 1   3    (swapped 6 and 9)

After inverting 2's children:
               4
             /   \
            7     2
           / \   / \
          9   6 3   1    (swapped 1 and 3)

Done!
```

## Edge Cases

| Case | Input | Output | Notes |
|------|-------|--------|-------|
| Empty tree | `null` | `null` | Handle null check |
| Single node | `[1]` | `[1]` | No children to swap |
| Only left child | `[1,2]` | `[1,null,2]` | Becomes right child |
| Balanced tree | `[4,2,7,1,3,6,9]` | `[4,7,2,9,6,3,1]` | Standard case |

## Common Mistakes

1. **Forgetting to return root**: The function should return the root
2. **Creating new nodes**: Just swap pointers, don't create new trees
3. **Order of operations**: Swap first, then recurse (or vice versa, both work)

## Interview Tips

1. **Start with recursion**: It's the most elegant solution
2. **Mention all approaches**: Show you know BFS and iterative DFS too
3. **Draw the tree**: Visual helps understand the transformation
4. **Discuss complexity**: O(n) time, O(h) or O(w) space

## Alternative Recursive Formulation

```python
def invertTree(root):
    if not root:
        return None
    
    # Could also do: invert first, then swap
    left = invertTree(root.left)
    right = invertTree(root.right)
    
    root.left = right
    root.right = left
    
    return root
```

Both formulations work because the swap and recursive calls are independent operations.

## Related Problems
- Symmetric Tree (check if tree is mirror of itself)
- Same Tree (compare two trees)
- Binary Tree Level Order Traversal (uses similar BFS pattern)

