"""
Problem: Balanced Binary Tree (LeetCode 110)

Given a binary tree, determine if it is height-balanced.
A height-balanced binary tree is defined as a tree in which the
depth of the two subtrees of every node never differs by more than one.

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
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        """
        Optimal O(n) solution.
        Returns -1 if unbalanced, otherwise returns height.
        """
        def check_height(node):
            if not node:
                return 0
            
            left_height = check_height(node.left)
            if left_height == -1:
                return -1  # Left subtree is unbalanced
            
            right_height = check_height(node.right)
            if right_height == -1:
                return -1  # Right subtree is unbalanced
            
            # Check if current node is balanced
            if abs(left_height - right_height) > 1:
                return -1  # Current node is unbalanced
            
            return 1 + max(left_height, right_height)
        
        return check_height(root) != -1
    
    def isBalancedNaive(self, root: Optional[TreeNode]) -> bool:
        """
        Naive O(n^2) solution - easier to understand.
        """
        def height(node):
            if not node:
                return 0
            return 1 + max(height(node.left), height(node.right))
        
        if not root:
            return True
        
        left_height = height(root.left)
        right_height = height(root.right)
        
        return (abs(left_height - right_height) <= 1 
                and self.isBalancedNaive(root.left) 
                and self.isBalancedNaive(root.right))

# Helper function
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
    
    # Test case 1: [3,9,20,null,null,15,7] -> true
    root1 = build_tree([3, 9, 20, None, None, 15, 7])
    print(f"Tree [3,9,20,null,null,15,7]")
    print(f"Is balanced: {sol.isBalanced(root1)} (expected: True)")
    assert sol.isBalanced(root1) == True
    
    # Test case 2: Unbalanced tree -> false
    root2 = TreeNode(1)
    root2.left = TreeNode(2)
    root2.right = TreeNode(2)
    root2.left.left = TreeNode(3)
    root2.left.right = TreeNode(3)
    root2.left.left.left = TreeNode(4)
    root2.left.left.right = TreeNode(4)
    print(f"\nTree [1,2,2,3,3,null,null,4,4]")
    print(f"Is balanced: {sol.isBalanced(root2)} (expected: False)")
    assert sol.isBalanced(root2) == False
    
    # Test case 3: Empty tree -> true
    root3 = None
    print(f"\nEmpty tree")
    print(f"Is balanced: {sol.isBalanced(root3)} (expected: True)")
    assert sol.isBalanced(root3) == True
    
    # Test case 4: Single node -> true
    root4 = TreeNode(1)
    print(f"\nSingle node")
    print(f"Is balanced: {sol.isBalanced(root4)} (expected: True)")
    assert sol.isBalanced(root4) == True
    
    # Test case 5: Perfectly balanced
    root5 = build_tree([1, 2, 3, 4, 5, 6, 7])
    print(f"\nPerfectly balanced [1,2,3,4,5,6,7]")
    print(f"Is balanced: {sol.isBalanced(root5)} (expected: True)")
    assert sol.isBalanced(root5) == True
    
    # Test case 6: Left skewed by 2 levels
    root6 = TreeNode(1, TreeNode(2, TreeNode(3)))
    print(f"\nLeft skewed [1,2,null,3]")
    print(f"Is balanced: {sol.isBalanced(root6)} (expected: False)")
    assert sol.isBalanced(root6) == False
    
    # Test naive solution
    print(f"\nNaive solution on case 1: {sol.isBalancedNaive(root1)}")
    
    print("\nAll test cases passed!")

