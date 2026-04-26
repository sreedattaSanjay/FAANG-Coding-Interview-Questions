"""
Problem: Maximum Depth of Binary Tree (LeetCode 104)

Given the root of a binary tree, return its maximum depth.
Maximum depth is the number of nodes along the longest path from root to leaf.

Time Complexity: O(n) - visit every node once
Space Complexity: O(h) - recursion stack, where h is height
"""

from typing import Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        """Recursive DFS approach"""
        if not root:
            return 0
        
        left_depth = self.maxDepth(root.left)
        right_depth = self.maxDepth(root.right)
        
        return 1 + max(left_depth, right_depth)
    
    def maxDepthBFS(self, root: Optional[TreeNode]) -> int:
        """Iterative BFS approach - count levels"""
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
    
    def maxDepthDFS(self, root: Optional[TreeNode]) -> int:
        """Iterative DFS approach using stack"""
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

# Helper function to build tree
def build_tree(values):
    if not values or values[0] is None:
        return None
    
    root = TreeNode(values[0])
    queue = deque([root])
    i = 1
    
    while queue and i < len(values):
        node = queue.popleft()
        
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1
        
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1
    
    return root

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [3,9,20,null,null,15,7] -> 3
    root1 = build_tree([3, 9, 20, None, None, 15, 7])
    print(f"Tree [3,9,20,null,null,15,7]")
    print(f"Max depth: {sol.maxDepth(root1)} (expected: 3)")
    assert sol.maxDepth(root1) == 3
    
    # Test case 2: [1,null,2] -> 2
    root2 = TreeNode(1)
    root2.right = TreeNode(2)
    print(f"\nTree [1,null,2]")
    print(f"Max depth: {sol.maxDepth(root2)} (expected: 2)")
    assert sol.maxDepth(root2) == 2
    
    # Test case 3: Empty tree -> 0
    root3 = None
    print(f"\nEmpty tree")
    print(f"Max depth: {sol.maxDepth(root3)} (expected: 0)")
    assert sol.maxDepth(root3) == 0
    
    # Test case 4: Single node -> 1
    root4 = TreeNode(1)
    print(f"\nSingle node")
    print(f"Max depth: {sol.maxDepth(root4)} (expected: 1)")
    assert sol.maxDepth(root4) == 1
    
    # Test case 5: Skewed tree -> 4
    root5 = TreeNode(1, TreeNode(2, TreeNode(3, TreeNode(4))))
    print(f"\nSkewed tree (left only)")
    print(f"Max depth: {sol.maxDepth(root5)} (expected: 4)")
    assert sol.maxDepth(root5) == 4
    
    # Test BFS solution
    root6 = build_tree([3, 9, 20, None, None, 15, 7])
    print(f"\nBFS solution: {sol.maxDepthBFS(root6)} (expected: 3)")
    assert sol.maxDepthBFS(root6) == 3
    
    # Test DFS solution
    print(f"DFS solution: {sol.maxDepthDFS(root6)} (expected: 3)")
    assert sol.maxDepthDFS(root6) == 3
    
    print("\nAll test cases passed!")

