"""
LeetCode 230: Kth Smallest Element in a BST
https://leetcode.com/problems/kth-smallest-element-in-a-bst/

Given the root of a binary search tree, and an integer k, return the kth 
smallest value (1-indexed) of all the values of the nodes in the tree.

Key Insight: Inorder traversal of BST gives elements in sorted order

Time Complexity: O(H + k) where H is tree height
Space Complexity: O(H) for recursion/stack
"""

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # Solution 1: Iterative Inorder Traversal (Optimal - stops early)
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        stack = []
        
        while root or stack:
            # Go to leftmost node
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            
            # Found kth smallest
            k -= 1
            if k == 0:
                return root.val
            
            root = root.right
        
        return -1  # k is larger than tree size
    
    # Solution 2: Recursive with generator (Pythonic and efficient)
    def kthSmallestGenerator(self, root: Optional[TreeNode], k: int) -> int:
        def inorder(node):
            if node:
                yield from inorder(node.left)
                yield node.val
                yield from inorder(node.right)
        
        gen = inorder(root)
        for _ in range(k):
            result = next(gen)
        return result
    
    # Solution 3: Recursive collecting all elements
    def kthSmallestRecursive(self, root: Optional[TreeNode], k: int) -> int:
        def inorder(node):
            if not node:
                return []
            return inorder(node.left) + [node.val] + inorder(node.right)
        
        return inorder(root)[k - 1]
    
    # Solution 4: Optimized recursive (stops early)
    def kthSmallestOptimized(self, root: Optional[TreeNode], k: int) -> int:
        self.count = 0
        self.result = 0
        
        def inorder(node):
            if not node or self.count >= k:
                return
            
            inorder(node.left)
            
            self.count += 1
            if self.count == k:
                self.result = node.val
                return
            
            inorder(node.right)
        
        inorder(root)
        return self.result


# Test
if __name__ == "__main__":
    # Test case 1: [3,1,4,null,2], k = 1 -> 1
    root1 = TreeNode(3)
    root1.left = TreeNode(1)
    root1.right = TreeNode(4)
    root1.left.right = TreeNode(2)
    
    # Test case 2: [5,3,6,2,4,null,null,1], k = 3 -> 3
    root2 = TreeNode(5)
    root2.left = TreeNode(3)
    root2.right = TreeNode(6)
    root2.left.left = TreeNode(2)
    root2.left.right = TreeNode(4)
    root2.left.left.left = TreeNode(1)
    
    sol = Solution()
    print(f"Test 1 (k=1): {sol.kthSmallest(root1, 1)}")           # 1
    print(f"Test 2 (k=3): {sol.kthSmallest(root2, 3)}")           # 3
    print(f"Test 2 (k=3, Generator): {sol.kthSmallestGenerator(root2, 3)}")  # 3
    print(f"Test 2 (k=3, Optimized): {sol.kthSmallestOptimized(root2, 3)}")  # 3

