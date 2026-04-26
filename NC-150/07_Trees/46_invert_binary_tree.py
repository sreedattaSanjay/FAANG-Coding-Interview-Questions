"""
Problem: Invert Binary Tree (LeetCode 226)

Given the root of a binary tree, invert the tree, and return its root.
Invert means swap left and right children at every node.

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
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        """Recursive DFS approach"""
        if not root:
            return None
        
        # Swap left and right children
        root.left, root.right = root.right, root.left
        
        # Recursively invert subtrees
        self.invertTree(root.left)
        self.invertTree(root.right)
        
        return root
    
    def invertTreeBFS(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        """Iterative BFS approach using queue"""
        if not root:
            return None
        
        queue = deque([root])
        
        while queue:
            node = queue.popleft()
            
            # Swap children
            node.left, node.right = node.right, node.left
            
            # Add children to queue
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        
        return root
    
    def invertTreeDFS(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        """Iterative DFS approach using stack"""
        if not root:
            return None
        
        stack = [root]
        
        while stack:
            node = stack.pop()
            
            # Swap children
            node.left, node.right = node.right, node.left
            
            # Add children to stack
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)
        
        return root

# Helper functions
def build_tree(values):
    """Build tree from level-order list (None for null nodes)"""
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

def tree_to_list(root):
    """Convert tree to level-order list"""
    if not root:
        return []
    
    result = []
    queue = deque([root])
    
    while queue:
        node = queue.popleft()
        if node:
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
        else:
            result.append(None)
    
    # Remove trailing Nones
    while result and result[-1] is None:
        result.pop()
    
    return result

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [4,2,7,1,3,6,9] -> [4,7,2,9,6,3,1]
    root1 = build_tree([4, 2, 7, 1, 3, 6, 9])
    print(f"Original: {tree_to_list(root1)}")
    root1 = sol.invertTree(root1)
    print(f"Inverted: {tree_to_list(root1)}")
    assert tree_to_list(root1) == [4, 7, 2, 9, 6, 3, 1]
    
    # Test case 2: [2,1,3] -> [2,3,1]
    root2 = build_tree([2, 1, 3])
    print(f"\nOriginal: {tree_to_list(root2)}")
    root2 = sol.invertTree(root2)
    print(f"Inverted: {tree_to_list(root2)}")
    assert tree_to_list(root2) == [2, 3, 1]
    
    # Test case 3: Empty tree
    root3 = None
    root3 = sol.invertTree(root3)
    print(f"\nEmpty tree: {tree_to_list(root3)}")
    assert tree_to_list(root3) == []
    
    # Test case 4: Single node
    root4 = TreeNode(1)
    root4 = sol.invertTree(root4)
    print(f"Single node: {tree_to_list(root4)}")
    assert tree_to_list(root4) == [1]
    
    # Test BFS solution
    root5 = build_tree([4, 2, 7, 1, 3, 6, 9])
    root5 = sol.invertTreeBFS(root5)
    print(f"\nBFS inverted: {tree_to_list(root5)}")
    assert tree_to_list(root5) == [4, 7, 2, 9, 6, 3, 1]
    
    print("\nAll test cases passed!")

