# 53. Binary Tree Level Order Traversal

## Problem Statement
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

**LeetCode Link:** [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

---

## 🎯 How to Explain to an Interviewer

### Step 1: Clarify the Problem (30 seconds)
> "I need to traverse the tree level by level, collecting all nodes at each depth into separate lists. The result should be a list of lists, where each inner list contains values from one level, left to right."

### Step 2: Walk Through Example (1 minute)
```
Input:
        3
       / \
      9  20
        /  \
       15   7

Output: [[3], [9, 20], [15, 7]]

Level 0: [3]
Level 1: [9, 20]
Level 2: [15, 7]
```

### Step 3: Identify the Pattern
> "This is a classic BFS (Breadth-First Search) problem. BFS naturally visits nodes level by level, which is exactly what we need. The key is to track when one level ends and the next begins."

---

## 💡 Key Insights to Mention

1. **BFS = Level Order** - Queue-based BFS naturally processes nodes level by level
2. **Level Boundary Tracking** - Process exactly `queue.size()` nodes per level
3. **Alternative DFS** - Can also solve with DFS by tracking depth

---

## 🔍 Solution Approaches

### Approach 1: Iterative BFS (Primary - Recommended)
```python
def levelOrder(root):
    if not root:
        return []
    
    result = []
    queue = deque([root])
    
    while queue:
        level_size = len(queue)    # Key: snapshot current level size
        current_level = []
        
        for _ in range(level_size):  # Process exactly this many nodes
            node = queue.popleft()
            current_level.append(node.val)
            
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        
        result.append(current_level)
    
    return result
```

**The "Level Size Snapshot" Technique:**
> "The crucial insight is capturing `len(queue)` BEFORE processing. This tells us exactly how many nodes are in the current level. As we process these nodes, we add their children, but those belong to the NEXT level."

### Approach 2: Recursive DFS
```python
def levelOrder(root):
    result = []
    
    def dfs(node, level):
        if not node:
            return
        
        # Extend result if we're at a new level
        if level >= len(result):
            result.append([])
        
        result[level].append(node.val)
        
        dfs(node.left, level + 1)
        dfs(node.right, level + 1)
    
    dfs(root, 0)
    return result
```

---

## ⏱️ Complexity Analysis

| Approach | Time | Space |
|----------|------|-------|
| BFS | O(n) | O(w) where w = max width |
| DFS | O(n) | O(h) where h = height |

**Space Analysis:**
> "BFS space is O(w) for the queue - at worst, the bottom level of a complete binary tree has n/2 nodes. DFS space is O(h) for the recursion stack - O(log n) balanced, O(n) skewed."

---

## 🆚 BFS vs DFS Comparison

| Aspect | BFS (Iterative) | DFS (Recursive) |
|--------|-----------------|-----------------|
| Natural fit | ✅ Level-by-level | Needs level tracking |
| Space | Queue (width-dependent) | Stack (height-dependent) |
| Implementation | Slightly more code | Cleaner recursive |
| Interview preference | Usually preferred | Good alternative |

---

## 🚨 Edge Cases to Mention

1. **Empty tree** → Return `[]`
2. **Single node** → Return `[[root.val]]`
3. **Skewed tree (all left or right)** → Each level has one node
4. **Complete binary tree** → Last level has most nodes

---

## 🗣️ Interview Script

**Opening statement:**
> "This is a classic BFS problem. Level order traversal and BFS are essentially the same thing - we process nodes level by level using a queue.
>
> The key technique is the 'level size snapshot': before processing any nodes in a level, I capture the current queue size. This tells me exactly how many nodes belong to the current level. I then process exactly that many nodes, adding their children to the queue for the next level.
>
> Let me walk through the code..."

**While coding, explain:**
> "I use a deque for efficient O(1) operations on both ends. For each level, I:
> 1. Snapshot the queue size
> 2. Pop that many nodes, adding values to current_level
> 3. Push each node's children
> 4. Add current_level to result"

---

## 🔄 Related Problems & Follow-ups

### Variations to Mention:
| Problem | Modification |
|---------|--------------|
| **Zigzag Level Order** (LC 103) | Alternate left-to-right and right-to-left |
| **Level Order Bottom Up** (LC 107) | Reverse the final result |
| **Right Side View** (LC 199) | Take only last node of each level |
| **Average of Levels** (LC 637) | Compute average instead of list |

### Follow-up Questions:

**Q: How would you modify for zigzag traversal?**
> "I'd add a boolean flag that alternates each level. When it's true, I'd reverse the current_level before adding to result (or use appendleft/append alternately)."

**Q: What if you need to return the bottom-up level order?**
> "Simply reverse the final result, or use a deque and appendleft each level."

**Q: How would you get just the rightmost node at each level?**
> "Same BFS loop, but only keep the last node processed in each level (when i == level_size - 1)."

---

## 🎨 Visual Walkthrough

```
Tree:      3
          / \
         9  20
           /  \
          15   7

Step 1: Initialize
Queue: [3]
Result: []

Step 2: Process Level 0
level_size = 1
Process node 3, add children 9, 20
Queue: [9, 20]
Result: [[3]]

Step 3: Process Level 1
level_size = 2
Process node 9 (no children)
Process node 20, add children 15, 7
Queue: [15, 7]
Result: [[3], [9, 20]]

Step 4: Process Level 2
level_size = 2
Process node 15 (no children)
Process node 7 (no children)
Queue: []
Result: [[3], [9, 20], [15, 7]]

Step 5: Queue empty, return result
```

---

## 📝 Common Mistakes to Avoid

1. **Not capturing level size** - If you check `while queue` inside the level loop, you'll mix levels
2. **Forgetting null check** - Always check `if node.left` before adding to queue
3. **Empty tree** - Return `[]`, not `[[]]`
4. **Using list instead of deque** - `list.pop(0)` is O(n), use `deque.popleft()` for O(1)

