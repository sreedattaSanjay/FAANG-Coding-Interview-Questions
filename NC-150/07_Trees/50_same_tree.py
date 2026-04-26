"""
Problem: Same Tree (LeetCode 100)

Given the roots of two binary trees p and q, write a function to check 
if they are the same or not. Two binary trees are considered the same 
if they are structurally identical, and the nodes have the same value.

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
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        """Recursive DFS approach"""
        # Both null - same
        if not p and not q:
            return True
        
        # One null, one not - different
        if not p or not q:
            return False
        
        # Both non-null - check value and children
        if p.val != q.val:
            return False
        
        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
    
    def isSameTreeBFS(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        """Iterative BFS approach"""
        queue = deque([(p, q)])
        
        while queue:
            node1, node2 = queue.popleft()
            
            # Both null - continue
            if not node1 and not node2:
                continue
            
            # One null or different values - not same
            if not node1 or not node2:
                return False
            if node1.val != node2.val:
                return False
            
            # Add children pairs
            queue.append((node1.left, node2.left))
            queue.append((node1.right, node2.right))
        
        return True
    
    def isSameTreeDFS(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        """Iterative DFS approach using stack"""
        stack = [(p, q)]
        
        while stack:
            node1, node2 = stack.pop()
            
            if not node1 and not node2:
                continue
            if not node1 or not node2:
                return False
            if node1.val != node2.val:
                return False
            
            stack.append((node1.left, node2.left))
            stack.append((node1.right, node2.right))
        
        return True

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
    
    # Test case 1: [1,2,3] and [1,2,3] -> true
    p1 = build_tree([1, 2, 3])
    q1 = build_tree([1, 2, 3])
    print(f"Tree 1: [1,2,3], Tree 2: [1,2,3]")
    print(f"Same: {sol.isSameTree(p1, q1)} (expected: True)")
    assert sol.isSameTree(p1, q1) == True
    
    # Test case 2: [1,2] and [1,null,2] -> false
    p2 = build_tree([1, 2])
    q2 = TreeNode(1)
    q2.right = TreeNode(2)
    print(f"\nTree 1: [1,2], Tree 2: [1,null,2]")
    print(f"Same: {sol.isSameTree(p2, q2)} (expected: False)")
    assert sol.isSameTree(p2, q2) == False
    
    # Test case 3: [1,2,1] and [1,1,2] -> false
    p3 = build_tree([1, 2, 1])
    q3 = build_tree([1, 1, 2])
    print(f"\nTree 1: [1,2,1], Tree 2: [1,1,2]")
    print(f"Same: {sol.isSameTree(p3, q3)} (expected: False)")
    assert sol.isSameTree(p3, q3) == False
    
    # Test case 4: Both empty -> true
    p4 = None
    q4 = None
    print(f"\nBoth empty trees")
    print(f"Same: {sol.isSameTree(p4, q4)} (expected: True)")
    assert sol.isSameTree(p4, q4) == True
    
    # Test case 5: One empty, one not -> false
    p5 = TreeNode(1)
    q5 = None
    print(f"\nTree 1: [1], Tree 2: empty")
    print(f"Same: {sol.isSameTree(p5, q5)} (expected: False)")
    assert sol.isSameTree(p5, q5) == False
    
    # Test BFS and DFS solutions
    p6 = build_tree([1, 2, 3])
    q6 = build_tree([1, 2, 3])
    print(f"\nBFS solution: {sol.isSameTreeBFS(p6, q6)}")
    print(f"DFS solution: {sol.isSameTreeDFS(p6, q6)}")
    assert sol.isSameTreeBFS(p6, q6) == True
    assert sol.isSameTreeDFS(p6, q6) == True
    
    print("\nAll test cases passed!")

