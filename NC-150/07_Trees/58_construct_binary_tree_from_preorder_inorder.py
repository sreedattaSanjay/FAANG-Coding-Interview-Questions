"""
LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Given two integer arrays preorder and inorder where preorder is the preorder 
traversal of a binary tree and inorder is the inorder traversal of the same tree, 
construct and return the binary tree.

Key Insight:
- Preorder: [root, left subtree, right subtree]
- Inorder: [left subtree, root, right subtree]
- First element in preorder is always the root
- Find root in inorder to split left and right subtrees

Time Complexity: O(n) with hashmap for inorder lookup
Space Complexity: O(n) for hashmap and recursion stack
"""

from typing import Optional, List
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        # Build hashmap for O(1) lookup of inorder indices
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        self.pre_idx = 0
        
        def build(in_left: int, in_right: int) -> Optional[TreeNode]:
            if in_left > in_right:
                return None
            
            # Pick the current root from preorder
            root_val = preorder[self.pre_idx]
            self.pre_idx += 1
            root = TreeNode(root_val)
            
            # Find root position in inorder
            mid = inorder_map[root_val]
            
            # Build left subtree first (preorder is root-left-right)
            root.left = build(in_left, mid - 1)
            root.right = build(mid + 1, in_right)
            
            return root
        
        return build(0, len(inorder) - 1)


class SolutionIterator:
    """Alternative using iterator instead of index tracking"""
    
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        preorder_iter = iter(preorder)
        
        def build(in_left: int, in_right: int) -> Optional[TreeNode]:
            if in_left > in_right:
                return None
            
            root_val = next(preorder_iter)
            root = TreeNode(root_val)
            
            mid = inorder_map[root_val]
            
            root.left = build(in_left, mid - 1)
            root.right = build(mid + 1, in_right)
            
            return root
        
        return build(0, len(inorder) - 1)


def print_level_order(root):
    """Helper to print tree level order"""
    if not root:
        print("[]")
        return
    
    result = []
    queue = deque([root])
    
    while queue:
        node = queue.popleft()
        if node:
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
    
    # Remove trailing None values
    while result and result[-1] is None:
        result.pop()
    
    print(result)


# Test
if __name__ == "__main__":
    # Test case: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    # Expected output: [3,9,20,null,null,15,7]
    preorder = [3, 9, 20, 15, 7]
    inorder = [9, 3, 15, 20, 7]
    
    sol = Solution()
    root = sol.buildTree(preorder, inorder)
    
    print("Constructed tree: ", end="")
    print_level_order(root)  # [3, 9, 20, 15, 7]

