# Same Tree - Detailed Explanation

## Problem Statement
Given the roots of two binary trees `p` and `q`, check if they are the same. Two trees are the same if they are structurally identical and have the same node values.

## Examples
```
p:    1         q:    1
     / \             / \
    2   3           2   3
                          
Same: true

p:    1         q:    1
     /               \
    2                 2
                          
Same: false (different structure)

p:    1         q:    1
     / \             / \
    2   1           1   2
                          
Same: false (different values)
```

## Approach: Recursive DFS (Recommended)

### Key Insight
Two trees are the same if:
1. Both roots are null, OR
2. Both roots have the same value AND
   - Left subtrees are the same AND
   - Right subtrees are the same

### Algorithm
```python
def isSameTree(p, q):
    # Both null
    if not p and not q:
        return True
    
    # One null
    if not p or not q:
        return False
    
    # Both non-null
    if p.val != q.val:
        return False
    
    return isSameTree(p.left, q.left) and isSameTree(p.right, q.right)
```

### Visual Walkthrough
```
p:    1         q:    1
     / \             / \
    2   3           2   3

isSameTree(1, 1):
  p.val == q.val? 1 == 1 ✓
  
  isSameTree(2, 2):
    p.val == q.val? 2 == 2 ✓
    isSameTree(null, null): true
    isSameTree(null, null): true
    return true
  
  isSameTree(3, 3):
    p.val == q.val? 3 == 3 ✓
    isSameTree(null, null): true
    isSameTree(null, null): true
    return true
  
  return true && true = true
```

### Complexity
- **Time**: O(n) where n is the smaller tree's size
- **Space**: O(h) for recursion stack, where h is tree height

## Iterative Solutions

### BFS (Level Order)
```python
def isSameTree(p, q):
    queue = deque([(p, q)])
    
    while queue:
        node1, node2 = queue.popleft()
        
        if not node1 and not node2:
            continue
        if not node1 or not node2:
            return False
        if node1.val != node2.val:
            return False
        
        queue.append((node1.left, node2.left))
        queue.append((node1.right, node2.right))
    
    return True
```

### DFS (Stack)
```python
def isSameTree(p, q):
    stack = [(p, q)]
    
    while stack:
        node1, node2 = stack.pop()
        
        if not node1 and not node2:
            continue
        if not node1 or not node2:
            return False
        if node1.val != node2.val:
            return False
        
        stack.append((node1.left, node2.left))
        stack.append((node1.right, node2.right))
    
    return True
```

## Edge Cases

| Case | p | q | Output | Notes |
|------|---|---|--------|-------|
| Both empty | null | null | true | Base case |
| One empty | [1] | null | false | Different structure |
| Same single | [1] | [1] | true | Single node |
| Different values | [1] | [2] | false | Same structure, different values |
| Mirror trees | [1,2,3] | [1,3,2] | false | Not same (mirrored) |

## Common Mistakes

1. **Checking null incorrectly**: Handle both-null, one-null, and both-non-null cases separately
2. **Forgetting structure**: Trees with same values but different structure are not same
3. **Confusing with symmetric**: Same tree ≠ Symmetric tree

## One-Liner Solution
```python
def isSameTree(p, q):
    return (not p and not q) or (
        p and q and 
        p.val == q.val and 
        isSameTree(p.left, q.left) and 
        isSameTree(p.right, q.right)
    )
```

## Interview Tips

1. **Start with base cases**: Null handling is crucial
2. **Draw examples**: Show same structure and different values cases
3. **Mention all approaches**: Recursive, BFS, DFS
4. **Compare to related problems**: Symmetric Tree, Subtree of Another Tree

## Related Problems
- Symmetric Tree (is tree a mirror of itself)
- Subtree of Another Tree (uses this as a helper)
- Invert Binary Tree (creates a mirrored tree)

## Extension: Compare with Tolerance

What if values could differ by some epsilon?

```python
def isSameTreeWithTolerance(p, q, epsilon=0.001):
    if not p and not q:
        return True
    if not p or not q:
        return False
    
    if abs(p.val - q.val) > epsilon:
        return False
    
    return (isSameTreeWithTolerance(p.left, q.left, epsilon) and 
            isSameTreeWithTolerance(p.right, q.right, epsilon))
```

