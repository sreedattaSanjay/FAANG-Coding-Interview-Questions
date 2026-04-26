"""
LeetCode 572: Subtree of Another Tree
https://leetcode.com/problems/subtree-of-another-tree/

Given the roots of two binary trees root and subRoot, return true if there 
is a subtree of root with the same structure and node values of subRoot 
and false otherwise.

Time Complexity: O(m * n) where m and n are sizes of root and subRoot trees
Space Complexity: O(h) recursion stack where h is height of root tree
"""

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        # Empty subRoot is always a subtree
        if not subRoot:
            return True
        # Empty root cannot contain a non-empty subtree
        if not root:
            return False
        
        # Check if trees match at current position
        if self.isSameTree(root, subRoot):
            return True
        
        # Check left and right subtrees
        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)
    
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if not p and not q:
            return True
        if not p or not q:
            return False
        if p.val != q.val:
            return False
        
        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)


class SolutionStringMatch:
    """Alternative solution using string serialization"""
    
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        root_str = self.serialize(root)
        sub_str = self.serialize(subRoot)
        
        return sub_str in root_str
    
    def serialize(self, node: Optional[TreeNode]) -> str:
        if not node:
            return ",#"
        
        # Use comma prefix to avoid false matches (e.g., 12 vs 2)
        return f",{node.val}" + self.serialize(node.left) + self.serialize(node.right)


# Test
if __name__ == "__main__":
    # Test case 1: root = [3,4,5,1,2], subRoot = [4,1,2] -> true
    root1 = TreeNode(3)
    root1.left = TreeNode(4)
    root1.right = TreeNode(5)
    root1.left.left = TreeNode(1)
    root1.left.right = TreeNode(2)
    
    sub1 = TreeNode(4)
    sub1.left = TreeNode(1)
    sub1.right = TreeNode(2)
    
    # Test case 2: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2] -> false
    root2 = TreeNode(3)
    root2.left = TreeNode(4)
    root2.right = TreeNode(5)
    root2.left.left = TreeNode(1)
    root2.left.right = TreeNode(2)
    root2.left.right.left = TreeNode(0)  # Extra node makes it different
    
    sol = Solution()
    print(f"Test 1: {sol.isSubtree(root1, sub1)}")  # True
    print(f"Test 2: {sol.isSubtree(root2, sub1)}")  # False
    
    sol2 = SolutionStringMatch()
    print(f"Test 1 (String): {sol2.isSubtree(root1, sub1)}")  # True

