"""
Problem: Diameter of Binary Tree (LeetCode 543)

Given the root of a binary tree, return the length of the diameter.
The diameter is the length of the longest path between any two nodes.
This path may or may not pass through the root.

Note: The length of a path is the number of EDGES between nodes.

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
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        self.diameter = 0
        
        def height(node):
            if not node:
                return 0
            
            left_height = height(node.left)
            right_height = height(node.right)
            
            # The path through this node has length left_height + right_height
            self.diameter = max(self.diameter, left_height + right_height)
            
            # Return height of this subtree
            return 1 + max(left_height, right_height)
        
        height(root)
        return self.diameter
    
    def diameterOfBinaryTreeNoMember(self, root: Optional[TreeNode]) -> int:
        """Version without using class member variable"""
        def dfs(node):
            # Returns (height, max_diameter_in_subtree)
            if not node:
                return 0, 0
            
            left_height, left_diameter = dfs(node.left)
            right_height, right_diameter = dfs(node.right)
            
            # Diameter through this node
            current_diameter = left_height + right_height
            
            # Maximum diameter seen so far
            max_diameter = max(current_diameter, left_diameter, right_diameter)
            
            return 1 + max(left_height, right_height), max_diameter
        
        _, diameter = dfs(root)
        return diameter

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
    
    # Test case 1: [1,2,3,4,5] -> 3
    root1 = build_tree([1, 2, 3, 4, 5])
    print(f"Tree [1,2,3,4,5]")
    print(f"Diameter: {sol.diameterOfBinaryTree(root1)} (expected: 3)")
    assert sol.diameterOfBinaryTree(root1) == 3
    
    # Test case 2: [1,2] -> 1
    root2 = build_tree([1, 2])
    print(f"\nTree [1,2]")
    print(f"Diameter: {sol.diameterOfBinaryTree(root2)} (expected: 1)")
    assert sol.diameterOfBinaryTree(root2) == 1
    
    # Test case 3: Single node -> 0
    root3 = TreeNode(1)
    print(f"\nSingle node")
    print(f"Diameter: {sol.diameterOfBinaryTree(root3)} (expected: 0)")
    assert sol.diameterOfBinaryTree(root3) == 0
    
    # Test case 4: Empty tree -> 0
    root4 = None
    print(f"\nEmpty tree")
    print(f"Diameter: {sol.diameterOfBinaryTree(root4)} (expected: 0)")
    assert sol.diameterOfBinaryTree(root4) == 0
    
    # Test case 5: Diameter not through root
    root5 = TreeNode(1)
    root5.left = TreeNode(2)
    root5.left.left = TreeNode(3)
    root5.left.right = TreeNode(4)
    root5.left.left.left = TreeNode(5)
    root5.left.right.right = TreeNode(6)
    print(f"\nTree where diameter doesn't pass through root")
    print(f"Diameter: {sol.diameterOfBinaryTree(root5)} (expected: 4)")
    assert sol.diameterOfBinaryTree(root5) == 4
    
    # Test alternative solution
    print(f"\nAlternative solution: {sol.diameterOfBinaryTreeNoMember(root1)}")
    assert sol.diameterOfBinaryTreeNoMember(root1) == 3
    
    print("\nAll test cases passed!")

