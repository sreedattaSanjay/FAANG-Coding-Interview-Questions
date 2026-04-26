"""
LeetCode 102: Binary Tree Level Order Traversal
https://leetcode.com/problems/binary-tree-level-order-traversal/

Given the root of a binary tree, return the level order traversal of its 
nodes' values. (i.e., from left to right, level by level).

Time Complexity: O(n) - visit each node once
Space Complexity: O(n) - queue can hold at most n/2 nodes
"""

from typing import Optional, List
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # Solution 1: Iterative BFS
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        result = []
        queue = deque([root])
        
        while queue:
            level_size = len(queue)
            current_level = []
            
            for _ in range(level_size):
                node = queue.popleft()
                current_level.append(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(current_level)
        
        return result
    
    # Solution 2: Recursive DFS
    def levelOrderDFS(self, root: Optional[TreeNode]) -> List[List[int]]:
        result = []
        
        def dfs(node: Optional[TreeNode], level: int):
            if not node:
                return
            
            # Add new level if needed
            if level >= len(result):
                result.append([])
            
            result[level].append(node.val)
            
            dfs(node.left, level + 1)
            dfs(node.right, level + 1)
        
        dfs(root, 0)
        return result


# Test
if __name__ == "__main__":
    # Test case: [3,9,20,null,null,15,7]
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)
    
    sol = Solution()
    print(f"BFS: {sol.levelOrder(root)}")      # Expected: [[3],[9,20],[15,7]]
    print(f"DFS: {sol.levelOrderDFS(root)}")   # Expected: [[3],[9,20],[15,7]]

