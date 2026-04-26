  0# Tree Problems - Detailed Explanations
## Complete Guide for Interview Preparation

This document provides in-depth explanations for 14 essential tree problems commonly asked in FAANG and top tech company interviews.

---

## Table of Contents

| # | Problem | Difficulty |
|---|---------|------------|
| 1 | [Maximum Depth of Binary Tree](#1-maximum-depth-of-binary-tree-leetcode-104) | 🟢 Easy |
| 2 | [Same Tree](#2-same-tree-leetcode-100) | 🟢 Easy |
| 3 | [Invert Binary Tree](#3-invert-binary-tree-leetcode-226) | 🟢 Easy |
| 4 | [Binary Tree Maximum Path Sum](#4-binary-tree-maximum-path-sum-leetcode-124) | 🔴 Hard |
| 5 | [Binary Tree Level Order Traversal](#5-binary-tree-level-order-traversal-leetcode-102) | 🟡 Medium |
| 6 | [Serialize and Deserialize Binary Tree](#6-serialize-and-deserialize-binary-tree-leetcode-297) | 🔴 Hard |
| 7 | [Subtree of Another Tree](#7-subtree-of-another-tree-leetcode-572) | 🟢 Easy |
| 8 | [Construct Binary Tree from Preorder and Inorder](#8-construct-binary-tree-from-preorder-and-inorder-leetcode-105) | 🟡 Medium |
| 9 | [Validate Binary Search Tree](#9-validate-binary-search-tree-leetcode-98) | 🟡 Medium |
| 10 | [Kth Smallest Element in BST](#10-kth-smallest-element-in-bst-leetcode-230) | 🟡 Medium |
| 11 | [Lowest Common Ancestor of BST](#11-lowest-common-ancestor-of-bst-leetcode-235) | 🟡 Medium |
| 12 | [Implement Trie (Prefix Tree)](#12-implement-trie-leetcode-208) | 🟡 Medium |
| 13 | [Add and Search Word](#13-add-and-search-word-leetcode-211) | 🟡 Medium |
| 14 | [Word Search II](#14-word-search-ii-leetcode-212) | 🔴 Hard |

---

## 1. Maximum Depth of Binary Tree (LeetCode 104)

### Problem Statement
Given the root of a binary tree, return its maximum depth. The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

**Example:**
```
Input:     3
          / \
         9  20
           /  \
          15   7
Output: 3 (root -> 20 -> 15 or root -> 20 -> 7)
```

### Key Insight
The depth of a tree is `1 + max(depth of left subtree, depth of right subtree)`. This naturally leads to a recursive solution. An empty tree has depth 0.

### Approach 1: Recursive DFS (Recommended)

**Algorithm:**
1. Base case: If node is null, return 0
2. Recursively find depth of left subtree
3. Recursively find depth of right subtree
4. Return `1 + max(left_depth, right_depth)`

**Why it works:**
- Each call processes one node and delegates subtrees to recursive calls
- The maximum of the two subtree depths gives the longest path from current node
- Adding 1 accounts for the current node

### Approach 2: Iterative BFS (Level Order)

**Algorithm:**
1. Use a queue to traverse level by level
2. For each level, process all nodes at that level
3. Increment depth counter after processing each level
4. When queue is empty, return the depth counter

**Why it works:**
- BFS naturally processes nodes level by level
- The number of levels equals the maximum depth

### Visual Walkthrough

```
Tree:
            3          ← Level 1 (depth = 1)
           / \
          9  20        ← Level 2 (depth = 2)
            /  \
           15   7      ← Level 3 (depth = 3)
```

**Step-by-step execution:**

```
┌─────────────────────────────────────────────────────────────────────┐
│ INITIALIZATION                                                      │
│ Queue: [3]                                                          │
│ Depth: 0                                                            │
└─────────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────────┐
│ LEVEL 1 PROCESSING                                                  │
│ Level size = 1 (queue has 1 node)                                   │
│ Depth: 0 → 1                                                        │
│                                                                     │
│   Process node 3:                                                   │
│   ┌───┐                                                             │
│   │ 3 │ ← Dequeue                                                   │
│   └───┘                                                             │
│     ↓                                                               │
│   Add children [9, 20] to queue                                     │
│                                                                     │
│ Queue after: [9, 20]                                                │
│ Depth: 1                                                            │
└─────────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────────┐
│ LEVEL 2 PROCESSING                                                  │
│ Level size = 2 (queue has 2 nodes)                                  │
│ Depth: 1 → 2                                                        │
│                                                                     │
│   Process node 9:           Process node 20:                        │
│   ┌───┐                     ┌────┐                                  │
│   │ 9 │ ← Dequeue           │ 20 │ ← Dequeue                        │
│   └───┘                     └────┘                                  │
│     ↓                          ↓                                    │
│   No children               Add children [15, 7] to queue           │
│                                                                     │
│ Queue after: [15, 7]                                                │
│ Depth: 2                                                            │
└─────────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────────┐
│ LEVEL 3 PROCESSING                                                  │
│ Level size = 2 (queue has 2 nodes)                                  │
│ Depth: 2 → 3                                                        │
│                                                                     │
│   Process node 15:          Process node 7:                         │
│   ┌────┐                    ┌───┐                                   │
│   │ 15 │ ← Dequeue          │ 7 │ ← Dequeue                         │
│   └────┘                    └───┘                                   │
│     ↓                          ↓                                    │
│   No children               No children                             │
│                                                                     │
│ Queue after: [] (empty!)                                            │
│ Depth: 3                                                            │
└─────────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────────┐
│ TERMINATION                                                         │
│ Queue is empty → Exit loop                                          │
│ Return depth = 3  ✓                                                 │
└─────────────────────────────────────────────────────────────────────┘
```

### Key Insight: Why we track "level size"

Before processing each level, we capture `queue.size()`:

```
Queue: [9, 20]     ← Level size = 2
       ↑    ↑
     These 2 nodes are BOTH at the same level!
```

When we process these 2 nodes, we add their children:

```
Queue: [15, 7]     ← These are NEXT level's nodes!
```

By knowing level size BEFORE processing, we know exactly where current level ends and next level begins.

**WITHOUT level size tracking (WRONG):**
- We'd mix nodes from different levels
- Can't tell when a level is complete
- Depth count would be incorrect

### Approach 3: Iterative DFS (Using Stack)

**Algorithm:**
1. Use a stack storing (node, depth) pairs
2. For each node, track its depth
3. Update max_depth whenever we visit a node
4. Push children with depth + 1

### Complexity Analysis
- **Time:** O(n) - visit each node exactly once
- **Space:** O(h) for recursion/stack where h is height
  - Best case (balanced): O(log n)
  - Worst case (skewed): O(n)

### Common Mistakes
- Forgetting base case (null check)
- Off-by-one errors (forgetting to add 1 for current node)

### Interview Tips
- Start with recursive solution (cleaner)
- Mention iterative if asked for alternatives
- Discuss space complexity difference between BFS and DFS

---

## 2. Same Tree (LeetCode 100)

### Problem Statement
Given the roots of two binary trees p and q, check if they are structurally identical with the same node values.

**Example:**
```
p:    1        q:    1
     / \           / \
    2   3         2   3
Output: true
```

### Key Insight
Two trees are the same if:
1. Both roots are null (empty trees are same), OR
2. Both roots exist AND have same value AND left subtrees are same AND right subtrees are same

### Approach: Recursive Comparison

**Algorithm:**
1. If both nodes are null → return true
2. If one is null and other isn't → return false
3. If values don't match → return false
4. Recursively check left AND right subtrees

**Why it works:**
- We check structural identity (both null or both exist)
- We check value equality
- We recursively verify subtrees

### Approach 2: Iterative BFS

**Algorithm:**
1. Use a queue of node pairs
2. For each pair, apply same checks as recursive
3. Add corresponding children as pairs
4. If any mismatch found, return false

### Complexity Analysis
- **Time:** O(min(m, n)) where m, n are tree sizes - We stop as soon as we find a mismatch
- **Space:** O(min(h1, h2)) for recursion stack

### Common Patterns
- This pattern of "check root + recurse on children" is fundamental
- Same logic appears in: Symmetric Tree, Subtree problems

### Interview Tips
- Clarify: Is null == null? (Yes, both empty trees are same)
- Mention short-circuit evaluation in recursion

---

## 3. Invert Binary Tree (LeetCode 226)

### Problem Statement
Given the root of a binary tree, invert it and return the root. (Mirror the tree - swap all left and right children)

**Example:**
```
Input:      4              Output:     4
           / \                        / \
          2   7                      7   2
         / \ / \                    / \ / \
        1  3 6  9                  9  6 3  1
```

### Key Insight
Inverting a tree = swap left and right children of EVERY node. The order in which we do swaps doesn't matter (pre/post/in-order all work).

### Approach 1: Recursive (Pre-order)

**Algorithm:**
1. If node is null, return null
2. Swap left and right children of current node
3. Recursively invert left subtree
4. Recursively invert right subtree
5. Return root

**Why it works:**
- Each node's children get swapped
- Recursive calls ensure all descendants are also inverted
- Order doesn't matter because we swap at every node

### Approach 2: Iterative BFS

**Algorithm:**
1. Use queue starting with root
2. For each node, swap its children
3. Add non-null children to queue
4. Continue until queue is empty

### Approach 3: Iterative DFS (Stack)
Same logic as BFS but using stack (LIFO vs FIFO)

### Complexity Analysis
- **Time:** O(n) - visit each node once
- **Space:** O(h) for recursion, O(n) for BFS worst case

### Fun Fact
This problem became famous when Max Howell (creator of Homebrew) tweeted that he failed his Google interview because he couldn't solve it on a whiteboard. It's actually quite simple once you see the pattern!

### Interview Tips
- Recognize that swapping is done at EVERY node, not just once
- Can be done in-place (modify original tree)

---

## 4. Binary Tree Maximum Path Sum (LeetCode 124)

### Problem Statement
Find the maximum path sum in a binary tree. A path can start and end at any node (doesn't need to pass through root). Path must be contiguous.

**Example:**
```
Input:     -10
           /  \
          9   20
             /  \
            15   7
Output: 42 (path: 15 -> 20 -> 7)
```

### Key Insight
For any node, we have two different questions:
1. What's the max path sum THROUGH this node? (could be the global answer)
2. What's the max path sum we can CONTRIBUTE going up? (for parent's calculation)

These are different! A path through a node can use both children. But contribution to parent can only use ONE side (path can't fork).

### Approach: Post-Order DFS with Global Tracking

**Algorithm:**
1. For each node, calculate max "gain" from left and right subtrees
2. If gain is negative, don't include it (take 0 instead)
3. Calculate path sum THROUGH this node: `node.val + leftGain + rightGain`
4. Update global maximum if this path is better
5. Return contribution to parent: `node.val + max(leftGain, rightGain)`

**Why we take max with 0:**
- Negative subtrees would decrease our sum
- Better to not include them at all

**Why we return only one direction:**
- A valid path can't split - it must be contiguous
- Parent can only extend path in one direction from this node

### Visual Example
```
             -10
            /   \
           9    20
               /  \
              15   7
```

**At node 20:**
- leftGain = 15, rightGain = 7
- Path through 20: 20 + 15 + 7 = 42 (potential answer!)
- Contribution to parent: 20 + max(15, 7) = 35

**At node -10:**
- leftGain = max(0, 9) = 9
- rightGain = max(0, 35) = 35
- Path through -10: -10 + 9 + 35 = 34 (less than 42)

**Global max = 42**

### Complexity Analysis
- **Time:** O(n) - visit each node once
- **Space:** O(h) - recursion stack

### Common Mistakes
- Forgetting that path doesn't need to include root
- Not handling negative values correctly
- Confusing "max contribution" with "max path through node"

### Interview Tips
- Draw out the example to visualize
- Clearly explain the two different values we track
- This is a HARD problem - expect follow-up questions

---

## 5. Binary Tree Level Order Traversal (LeetCode 102)

### Problem Statement
Return the level order traversal of a binary tree (left to right, level by level).

**Example:**
```
Input:      3
           / \
          9  20
            /  \
           15   7
Output: [[3], [9, 20], [15, 7]]
```

### Key Insight
BFS naturally processes nodes level by level. The key is knowing how many nodes belong to the current level before processing them.

### Approach 1: BFS with Level Tracking

**Algorithm:**
1. Initialize queue with root
2. While queue is not empty:
   - Get current level size (`queue.size()`)
   - Process exactly that many nodes (they're all in current level)
   - Add their children to queue (for next level)
   - Add current level's values to result

**Why we track level size:**
- When we start processing a level, queue contains only that level's nodes
- Children we add during processing belong to NEXT level
- By counting before processing, we know where current level ends

### Approach 2: DFS with Level Parameter

**Algorithm:**
1. Use DFS but pass current level as parameter
2. If result doesn't have a list for this level, create one
3. Add current node's value to its level's list
4. Recurse on children with level + 1

**Why it works:**
- DFS visits nodes in different order than BFS
- But by tracking level, we can place values in correct sub-lists
- Result is same as BFS, just built differently

### Complexity Analysis
- **Time:** O(n) - visit each node once
- **Space:** O(n) - queue can hold up to n/2 nodes (last level of complete tree)

### Variations
- Level Order Traversal II (bottom to top): Just reverse result
- Zigzag Level Order: Alternate direction each level
- Right Side View: Take last element of each level

### Interview Tips
- This is a fundamental pattern - know it well!
- Be ready to adapt for variations
- BFS is more intuitive for this problem

---

## 6. Serialize and Deserialize Binary Tree (LeetCode 297)

### Problem Statement
Design an algorithm to serialize (convert tree to string) and deserialize (convert string back to tree) a binary tree.

### Key Insight
We need to encode:
1. Node values
2. Structure (where are the null children)

Both preorder DFS and level-order BFS work, as long as we mark null nodes.

### Approach 1: Preorder DFS

**Serialize:**
1. Visit node: add value (or "null" for null nodes)
2. Recurse left, then right
3. Use delimiter (comma) between values

**Deserialize:**
1. Split string by delimiter
2. Use iterator/index to consume values one by one
3. For each value: create node or return null
4. Recursively build left then right subtrees

**Example:**
```
Tree:    1
        / \
       2   3
          / \
         4   5

Serialized: "1,2,null,null,3,4,null,null,5,null,null"
```

**Why preorder works:**
- First value is always root
- We know exactly when to recurse (after processing current node)
- Nulls mark where subtrees end

### Approach 2: Level Order BFS

**Serialize:**
1. BFS traversal, adding values level by level
2. Include nulls to mark missing children
3. Can optionally trim trailing nulls

**Deserialize:**
1. First value is root
2. Use queue to track which node's children to fill next
3. Values come in pairs (left child, right child)

### Complexity Analysis
- **Time:** O(n) for both operations
- **Space:** O(n) for string storage

### Interview Tips
- Clarify: What format is acceptable? (Usually flexible)
- DFS is often cleaner to implement
- Consider edge cases: empty tree, single node, negative values

---

## 7. Subtree of Another Tree (LeetCode 572)

### Problem Statement
Given roots of two trees, check if subRoot is a subtree of root. A subtree must have EXACT same structure and values.

**Example:**
```
root:       3           subRoot:    4
           / \                     / \
          4   5                   1   2
         / \
        1   2
Output: true (subtree at node 4 matches)
```

### Key Insight
For every node in root tree, check if the tree starting there matches subRoot. This combines tree traversal with tree comparison (isSameTree).

### Approach 1: DFS + Same Tree Check

**Algorithm:**
1. If subRoot is null → return true (empty tree is subtree of anything)
2. If root is null → return false (non-empty can't be subtree of empty)
3. If current node matches subRoot (isSameTree) → return true
4. Otherwise, check if subRoot is subtree of left OR right child

**isSameTree helper:** Same as Problem 2 (Same Tree)

**Why it works:**
- We try every possible starting point in root tree
- For each starting point, we check complete match
- Short-circuits on first match

### Approach 2: String Serialization

**Algorithm:**
1. Serialize both trees to strings (with markers for structure)
2. Check if subRoot's string is substring of root's string

**Why we need careful serialization:**
- Must include null markers
- Must have delimiters to avoid false matches
  - Example: "12" contains "2" but tree [12] doesn't contain tree [2]
  - With delimiters: ",12," doesn't contain ",2,"

### Complexity Analysis
**Approach 1:**
- **Time:** O(m * n) - for each of n nodes in root, compare m nodes of subRoot
- **Space:** O(h) - recursion stack

**Approach 2:**
- **Time:** O(m + n) with KMP/Rabin-Karp, O(m * n) with naive substring
- **Space:** O(m + n) for serialized strings

### Interview Tips
- Start with straightforward approach (DFS + Same Tree)
- Mention string approach as optimization if asked

---

## 8. Construct Binary Tree from Preorder and Inorder (LeetCode 105)

### Problem Statement
Given preorder and inorder traversal arrays, construct the original binary tree.

**Example:**
```
preorder = [3, 9, 20, 15, 7]
inorder  = [9, 3, 15, 20, 7]

Output:     3
           / \
          9  20
            /  \
           15   7
```

### Key Insight
Understanding what these traversals tell us:
- **Preorder:** `[ROOT, ...left subtree..., ...right subtree...]`
- **Inorder:** `[...left subtree..., ROOT, ...right subtree...]`

So:
1. First element of preorder is ALWAYS the root
2. Find that root in inorder - everything left is left subtree, right is right subtree
3. We now know the SIZE of left subtree
4. Use that to split preorder into left and right portions
5. Recurse!

### Approach: Recursive with HashMap

**Algorithm:**
1. Build hashmap: inorder value → index (for O(1) lookup)
2. Maintain pointer to current position in preorder
3. Recursive function takes inorder range (left, right):
   - If left > right: return null (empty subtree)
   - Get root value from `preorder[preorder_index++]`
   - Create root node
   - Find root in inorder using hashmap
   - Build left subtree (inorder range: left to mid-1)
   - Build right subtree (inorder range: mid+1 to right)
   - Return root

**Why we process LEFT subtree first:**
- Preorder is: root, LEFT, right
- So after root, next elements are left subtree nodes
- We must process left before right to consume preorder correctly

### Visual Walkthrough
```
preorder = [3, 9, 20, 15, 7]
              ^
inorder  = [9, 3, 15, 20, 7]
            L  ^  ----R----
```

**Step 1:** Root = 3, found at index 1 in inorder
- Left subtree: inorder[0:0] = [9]
- Right subtree: inorder[2:4] = [15, 20, 7]

**Step 2:** Process left (preorder now at 9)
- Root = 9, no children (single element)

**Step 3:** Process right (preorder now at 20)
- Root = 20, left=[15], right=[7]
- ... and so on

### Complexity Analysis
- **Time:** O(n) - each node processed once, hashmap gives O(1) lookup
- **Space:** O(n) - hashmap + recursion stack

**WITHOUT HASHMAP:**
- Would need to search inorder array each time: O(n²) total time

### Interview Tips
- Draw the example and trace through
- Hashmap optimization is expected
- Related: Construct from Inorder + Postorder (similar logic, process right first)

---

## 9. Validate Binary Search Tree (LeetCode 98)

### Problem Statement
Determine if a binary tree is a valid BST. Valid BST: `left subtree values < node value < right subtree values` (at every node)

**Example:**
```
Valid:      2          Invalid:    5
           / \                    / \
          1   3                  1   4
                                    / \
                                   3   6
(4 is in right subtree of 5 but 4 < 5 - INVALID!)
```

### Key Insight
**Common mistake:** Only checking immediate children. Must ensure ALL nodes in left subtree are less, ALL in right are greater.

**Solution:** Pass valid range (min, max) down the tree.

### Approach 1: Recursive with Range

**Algorithm:**
1. Each node has a valid range (min, max)
2. Root's range: (-∞, +∞)
3. For left child: range becomes (min, parent's value)
4. For right child: range becomes (parent's value, max)
5. If node's value violates its range → invalid

**Why it works:**
- Range narrows as we go down
- Left child must be less than parent AND less than all ancestors on path
- Range naturally captures this constraint

### Approach 2: Inorder Traversal

**Key insight:** Inorder traversal of BST produces SORTED sequence!

**Algorithm:**
1. Do inorder traversal
2. Track previous value
3. If current value ≤ previous value → invalid

**Why it works:**
- Inorder: Left, Root, Right
- In BST: all left < root < all right
- So inorder should be strictly increasing

### Complexity Analysis
- **Time:** O(n) - visit each node once
- **Space:** O(h) - recursion stack

### Edge Cases
- Empty tree → valid
- Single node → valid
- Duplicate values → typically considered invalid (problem-specific)
- Integer overflow: use long or pointers instead of INT_MIN/MAX

### Interview Tips
- Explain why checking only children is insufficient
- Be careful with equality (usually must be strictly less/greater)
- Inorder approach is elegant but range approach is more intuitive

---

## 10. Kth Smallest Element in BST (LeetCode 230)

### Problem Statement
Find the kth smallest element in a BST (1-indexed).

**Example:**
```
Tree:      3             k=1 → 1
          / \            k=2 → 2
         1   4           k=3 → 3
          \
           2
```

### Key Insight
Inorder traversal of BST visits nodes in SORTED ORDER (ascending). So kth element in inorder traversal = kth smallest.

### Approach 1: Iterative Inorder (Optimal)

**Algorithm:**
1. Use stack for iterative inorder
2. Count nodes as we visit them
3. When count reaches k, return current node's value

**Why iterative is better:**
- We can STOP as soon as we find kth element
- Don't need to traverse entire tree
- O(H + k) time instead of O(n)

**Iterative Inorder Pattern:**
```cpp
while (root or stack not empty):
    while (root):           // Go left as far as possible
        stack.push(root)
        root = root.left
    
    root = stack.pop()      // Visit node
    // PROCESS NODE HERE
    root = root.right       // Go right
```

### Approach 2: Recursive with Early Termination

**Algorithm:**
1. Track count and result as instance variables
2. Inorder traversal with early return when count = k
3. After visiting a node, check if we found answer

### Approach 3: Build Sorted List

**Algorithm:**
1. Full inorder traversal to build sorted list
2. Return `list[k-1]`

Less efficient (O(n)) but simpler to implement.

### Complexity Analysis
**Approach 1 & 2:**
- **Time:** O(H + k) - go down to leftmost, then visit k nodes
- **Space:** O(H) - stack/recursion

**Approach 3:**
- **Time:** O(n)
- **Space:** O(n)

### Follow-up: Frequent Queries
If kthSmallest is called frequently:
- Store count of nodes in each subtree
- Binary search to find kth element in O(H) time
- Or use order statistics tree (augmented BST)

### Interview Tips
- Immediately mention inorder property of BST
- Iterative is preferred (early termination)
- Discuss follow-up optimization if time permits

---

## 11. Lowest Common Ancestor of BST (LeetCode 235)

### Problem Statement
Find the lowest (deepest) node that is an ancestor of both p and q in a BST. (A node is an ancestor of itself)

**Example:**
```
Tree:       6
           / \
          2   8
         / \ / \
        0  4 7  9
          / \
         3   5

LCA(2, 8) = 6
LCA(2, 4) = 2
```

### Key Insight
In BST, we can use values to determine where to search!
- If both p and q are less than current → LCA is in left subtree
- If both p and q are greater than current → LCA is in right subtree
- Otherwise (split point) → current node IS the LCA

**Why split point is LCA:**
- One node is on left, one is on right (or one is current)
- Any ancestor above would have both in same subtree
- So current is the LOWEST common ancestor

### Approach 1: Iterative (Optimal)

**Algorithm:**
1. Start at root
2. While not at LCA:
   - If `p.val < root.val AND q.val < root.val` → go left
   - Elif `p.val > root.val AND q.val > root.val` → go right
   - Else → found LCA, return root

### Approach 2: Recursive

Same logic in recursive form:
```cpp
if (p.val < root.val && q.val < root.val)
    return LCA(root.left, p, q)
if (p.val > root.val && q.val > root.val)
    return LCA(root.right, p, q)
return root
```

### Complexity Analysis
- **Time:** O(H) - follow one path down
- **Space:** O(1) iterative, O(H) recursive

### Comparison with General Binary Tree LCA

**General tree (not BST):**
- Can't use values to guide search
- Must search both subtrees
- O(n) time required

**BST advantage:**
- Values guide us directly
- O(H) time - much better for balanced trees

### Interview Tips
- Emphasize using BST property (not just treating as regular tree)
- Iterative solution is cleaner and more space-efficient
- Don't forget: node can be ancestor of itself

---

## 12. Implement Trie (LeetCode 208)

### Problem Statement
Implement a trie with insert, search, and startsWith operations.

**Example:**
```
trie.insert("apple")
trie.search("apple")   → true
trie.search("app")     → false
trie.startsWith("app") → true
```

### Key Insight
A Trie (prefix tree) is a tree where:
- Each node represents a character
- Path from root to node represents a prefix
- Special marker indicates end of complete word

**Structure:**
```
          root
         / | \
        a  b  c
       /
      p
     /
    p
   /
  l
 /
e (marked as end-of-word)
```

### Trie Node Structure
Each node contains:
1. **children:** map/array of child nodes (one per character)
2. **isEndOfWord:** boolean flag

**Two implementation choices:**
- Array of size 26 (for lowercase letters only) - faster
- HashMap (for any characters) - more flexible

### Operations

**INSERT(word):**
1. Start at root
2. For each character in word:
   - If child doesn't exist, create it
   - Move to child
3. Mark final node as end-of-word

**SEARCH(word):**
1. Traverse trie following characters
2. If any character not found → false
3. If all found but final node not marked as word → false
4. Return true

**STARTSWITH(prefix):**
1. Same as search, but don't check end-of-word flag
2. If we can traverse all characters → true

### Complexity Analysis
- **Insert:** O(m) time, O(m) space for new word of length m
- **Search:** O(m) time
- **StartsWith:** O(m) time
- **Space:** O(ALPHABET_SIZE * n * m) worst case - n words of average length m

### Why Use Trie?
- Prefix queries: O(m) vs O(n*m) with hash set
- Autocomplete functionality
- Spell checking
- IP routing (longest prefix match)

### Interview Tips
- Clarify character set (lowercase? all ASCII?)
- Array vs HashMap tradeoff
- Discuss space optimization (compressed trie) if asked

---

## 13. Add and Search Word (LeetCode 211)

### Problem Statement
Design a data structure supporting:
- `addWord(word)`: Add word to dictionary
- `search(word)`: Search with '.' as wildcard (matches any character)

**Example:**
```
addWord("bad")
addWord("dad")
search("pad")  → false
search(".ad")  → true (matches "bad" and "dad")
search("b..")  → true
```

### Key Insight
This is Trie + DFS for wildcard handling.
- Normal characters: follow standard trie path
- Wildcard '.': must try ALL children

### Approach: Trie with Recursive Search

**addWord:** Standard trie insertion

**search:** Recursive DFS
```cpp
function search(word, index, node):
    if index == word.length:
        return node.isEndOfWord
    
    char = word[index]
    
    if char == '.':
        // Try all children
        for each child in node.children:
            if child exists AND search(word, index+1, child):
                return true
        return false
    else:
        // Normal character
        child = node.children[char]
        if child not exists:
            return false
        return search(word, index+1, child)
```

### Complexity Analysis
- **addWord:** O(m) time
- **search without wildcards:** O(m) time
- **search with wildcards:** O(26^m) worst case
  - Example: "..." with 26 children at each level
  - In practice, much better due to pruning

### Optimization
- Early termination when match found
- Trie structure naturally prunes many paths

### Interview Tips
- Start with Trie implementation
- Add wildcard handling with DFS
- Discuss worst-case complexity honestly

---

## 14. Word Search II (LeetCode 212)

### Problem Statement
Given an m×n board of characters and a list of words, find all words that can be formed by sequentially adjacent cells (horizontal/vertical). Each cell can only be used once per word.

**Example:**
```
board = [['o','a','a','n'],
         ['e','t','a','e'],
         ['i','h','k','r'],
         ['i','f','l','v']]
words = ["oath","pea","eat","rain"]

Output: ["eat","oath"]
```

### Key Insight
**Naive approach:** For each word, do word search (backtracking) on board.
Time: O(words * board * 4^wordLength) - too slow!

**Better:** Build Trie from words, then single DFS on board using Trie for pruning.
- Trie tells us if current path is a prefix of ANY word
- If not a prefix, we can prune immediately
- If it's a complete word, add to result

### Approach: Trie + Backtracking

**Build Phase:**
1. Insert all words into Trie
2. Store complete word at end node (for easy retrieval)

**Search Phase:**
1. For each cell in board, start DFS
2. At each step:
   - Check if current character is in Trie path
   - If not → return (prune)
   - If we're at a complete word → add to result
   - Mark cell as visited
   - Explore 4 neighbors
   - Restore cell (backtrack)

### Why Trie Helps
- Without Trie: Check each word separately
- With Trie: Check all words simultaneously
- Prune when current path matches NO word prefix

### Optimizations
1. Store word at end node (avoid rebuilding path string)
2. Mark found words as null (avoid duplicates)
3. Prune empty Trie branches (after finding words)

### Pseudocode
```cpp
function findWords(board, words):
    Build trie from words
    result = []
    
    for each cell (i, j) in board:
        dfs(board, i, j, trie.root, result)
    
    return result

function dfs(board, row, col, node, result):
    if out of bounds or visited:
        return
    
    char = board[row][col]
    if char not in node.children:
        return  // Prune!
    
    node = node.children[char]
    
    if node.word is not null:
        result.add(node.word)
        node.word = null  // Avoid duplicates
    
    board[row][col] = '#'  // Mark visited
    
    for each direction (up, down, left, right):
        dfs(board, newRow, newCol, node, result)
    
    board[row][col] = char  // Restore
```

### Complexity Analysis
- **Time:** O(m * n * 4^L) where L is max word length
  - But Trie pruning makes it much faster in practice
- **Space:** O(N * L) for Trie (N words, L average length)

### Interview Tips
- Explain why Trie is crucial for efficiency
- Walk through example with pruning
- Mention optimizations (deduplication, branch pruning)
- This is a HARD problem - take your time!

---

## Summary: Key Patterns and Techniques

### Tree Traversals
- **Preorder** (root, left, right): Good for copying/serializing trees
- **Inorder** (left, root, right): BST → sorted order
- **Postorder** (left, right, root): Good for deletion/bottom-up processing
- **Level Order** (BFS): Level-by-level processing

### Common Patterns
1. **Recursive DFS:** Most tree problems use this
2. **Iterative with Stack:** DFS without recursion
3. **BFS with Queue:** Level-order problems
4. **Range passing:** BST validation
5. **Global variable for result:** Maximum path sum type problems

### BST Properties
- Inorder = sorted order
- Can use values to guide search (O(log n) for balanced)
- Validate using ranges, not just immediate children

### Trie Applications
- Prefix matching
- Autocomplete
- Word search with wildcards
- Multiple string pattern matching

### Time Complexities to Remember
- Tree traversal: O(n)
- BST search/insert (balanced): O(log n)
- BST search/insert (worst): O(n)
- Trie operations: O(word length)

---

*End of Document*

