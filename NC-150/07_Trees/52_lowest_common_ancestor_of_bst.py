"""
LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

Given a binary search tree (BST), find the lowest common ancestor (LCA) 
node of two given nodes in the BST.

Key Insight: In a BST, we can use the BST property to efficiently find LCA:
- If both p and q are less than root, LCA is in left subtree
- If both p and q are greater than root, LCA is in right subtree
- Otherwise, current node is the LCA (split point)

Time Complexity: O(h) where h is tree height
Space Complexity: O(1) for iterative, O(h) for recursive
"""

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # Solution 1: Iterative (Optimal)
    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        while root:
            if p.val < root.val and q.val < root.val:
                # Both nodes in left subtree
                root = root.left
            elif p.val > root.val and q.val > root.val:
                # Both nodes in right subtree
                root = root.right
            else:
                # Found the split point (LCA)
                return root
        return None
    
    # Solution 2: Recursive
    def lowestCommonAncestorRecursive(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        if not root:
            return None
        
        if p.val < root.val and q.val < root.val:
            return self.lowestCommonAncestorRecursive(root.left, p, q)
        if p.val > root.val and q.val > root.val:
            return self.lowestCommonAncestorRecursive(root.right, p, q)
        
        return root


# Test
if __name__ == "__main__":
    # Test case: [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8 -> 6
    root = TreeNode(6)
    root.left = TreeNode(2)
    root.right = TreeNode(8)
    root.left.left = TreeNode(0)
    root.left.right = TreeNode(4)
    root.right.left = TreeNode(7)
    root.right.right = TreeNode(9)
    root.left.right.left = TreeNode(3)
    root.left.right.right = TreeNode(5)
    
    p1 = root.left         # node 2
    q1 = root.right        # node 8
    p2 = root.left         # node 2
    q2 = root.left.right   # node 4
    
    sol = Solution()
    
    lca1 = sol.lowestCommonAncestor(root, p1, q1)
    print(f"LCA(2,8): {lca1.val}")  # Expected: 6
    
    lca2 = sol.lowestCommonAncestor(root, p2, q2)
    print(f"LCA(2,4): {lca2.val}")  # Expected: 2

