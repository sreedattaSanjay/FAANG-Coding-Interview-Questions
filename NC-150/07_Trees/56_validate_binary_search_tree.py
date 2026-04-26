"""
LeetCode 98: Validate Binary Search Tree
https://leetcode.com/problems/validate-binary-search-tree/

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:
- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

Time Complexity: O(n) - visit each node once
Space Complexity: O(h) - recursion stack, where h is tree height
"""

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # Solution 1: Recursive with range validation
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def validate(node: Optional[TreeNode], min_val: float, max_val: float) -> bool:
            if not node:
                return True
            
            # Current node must be within valid range
            if node.val <= min_val or node.val >= max_val:
                return False
            
            # Left subtree must be less than current, right must be greater
            return (validate(node.left, min_val, node.val) and
                    validate(node.right, node.val, max_val))
        
        return validate(root, float('-inf'), float('inf'))
    
    # Solution 2: Inorder traversal (should be strictly increasing)
    def isValidBSTInorder(self, root: Optional[TreeNode]) -> bool:
        stack = []
        prev = None
        
        while root or stack:
            # Go to leftmost node
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            
            # Check if current value is greater than previous
            if prev is not None and root.val <= prev:
                return False
            
            prev = root.val
            root = root.right
        
        return True
    
    # Solution 3: Recursive inorder with generator
    def isValidBSTGenerator(self, root: Optional[TreeNode]) -> bool:
        def inorder(node):
            if node:
                yield from inorder(node.left)
                yield node.val
                yield from inorder(node.right)
        
        prev = float('-inf')
        for val in inorder(root):
            if val <= prev:
                return False
            prev = val
        
        return True


# Test
if __name__ == "__main__":
    # Test case 1: [2,1,3] -> true
    root1 = TreeNode(2, TreeNode(1), TreeNode(3))
    
    # Test case 2: [5,1,4,null,null,3,6] -> false (4 is in right subtree but < 5)
    root2 = TreeNode(5)
    root2.left = TreeNode(1)
    root2.right = TreeNode(4)
    root2.right.left = TreeNode(3)
    root2.right.right = TreeNode(6)
    
    sol = Solution()
    print(f"Test 1 (Recursive): {sol.isValidBST(root1)}")        # True
    print(f"Test 1 (Inorder): {sol.isValidBSTInorder(root1)}")   # True
    print(f"Test 1 (Generator): {sol.isValidBSTGenerator(root1)}")
    print(f"Test 2 (Recursive): {sol.isValidBST(root2)}")        # False
    print(f"Test 2 (Inorder): {sol.isValidBSTInorder(root2)}")   # False

