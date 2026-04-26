"""
LeetCode 124: Binary Tree Maximum Path Sum
https://leetcode.com/problems/binary-tree-maximum-path-sum/

A path in a binary tree is a sequence of nodes where each pair of adjacent 
nodes in the sequence has an edge connecting them. A node can only appear 
in the sequence at most once. Note that the path does not need to pass 
through the root.

The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

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
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        self.max_sum = float('-inf')
        
        def max_gain(node: Optional[TreeNode]) -> int:
            """Returns the maximum path sum starting from this node going DOWN"""
            if not node:
                return 0
            
            # Recursively get max gain from left and right subtrees
            # If gain is negative, we don't include that path (take 0 instead)
            left_gain = max(0, max_gain(node.left))
            right_gain = max(0, max_gain(node.right))
            
            # Path through current node: left -> node -> right
            path_sum = node.val + left_gain + right_gain
            
            # Update global maximum
            self.max_sum = max(self.max_sum, path_sum)
            
            # Return max gain if we continue path through this node (can only go one direction)
            return node.val + max(left_gain, right_gain)
        
        max_gain(root)
        return self.max_sum


# Test
if __name__ == "__main__":
    # Test case 1: [1,2,3] -> 6 (path: 2->1->3)
    root1 = TreeNode(1, TreeNode(2), TreeNode(3))
    
    # Test case 2: [-10,9,20,null,null,15,7] -> 42 (path: 15->20->7)
    root2 = TreeNode(-10)
    root2.left = TreeNode(9)
    root2.right = TreeNode(20)
    root2.right.left = TreeNode(15)
    root2.right.right = TreeNode(7)
    
    sol = Solution()
    print(f"Test 1: {sol.maxPathSum(root1)}")  # Expected: 6
    print(f"Test 2: {sol.maxPathSum(root2)}")  # Expected: 42

