"""
LeetCode 297: Serialize and Deserialize Binary Tree
https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

Design an algorithm to serialize and deserialize a binary tree. 
Serialization is the process of converting a data structure into a 
sequence of bits so that it can be stored or transmitted.

Time Complexity: O(n) for both serialize and deserialize
Space Complexity: O(n) for storing the tree representation
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Codec:
    """Solution using DFS Preorder traversal"""
    
    def serialize(self, root: Optional[TreeNode]) -> str:
        """Encodes a tree to a single string."""
        result = []
        
        def dfs(node):
            if not node:
                result.append("null")
                return
            
            result.append(str(node.val))
            dfs(node.left)
            dfs(node.right)
        
        dfs(root)
        return ",".join(result)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        """Decodes your encoded data to tree."""
        values = iter(data.split(","))
        
        def dfs():
            val = next(values)
            if val == "null":
                return None
            
            node = TreeNode(int(val))
            node.left = dfs()
            node.right = dfs()
            return node
        
        return dfs()


class CodecBFS:
    """Alternative solution using BFS Level Order traversal"""
    
    def serialize(self, root: Optional[TreeNode]) -> str:
        """Encodes a tree to a single string."""
        if not root:
            return "null"
        
        result = []
        queue = deque([root])
        
        while queue:
            node = queue.popleft()
            
            if node:
                result.append(str(node.val))
                queue.append(node.left)
                queue.append(node.right)
            else:
                result.append("null")
        
        return ",".join(result)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        """Decodes your encoded data to tree."""
        if data == "null":
            return None
        
        values = data.split(",")
        root = TreeNode(int(values[0]))
        queue = deque([root])
        i = 1
        
        while queue and i < len(values):
            node = queue.popleft()
            
            # Left child
            if values[i] != "null":
                node.left = TreeNode(int(values[i]))
                queue.append(node.left)
            i += 1
            
            # Right child
            if i < len(values) and values[i] != "null":
                node.right = TreeNode(int(values[i]))
                queue.append(node.right)
            i += 1
        
        return root


def print_tree(root):
    """Helper to print tree level order"""
    if not root:
        print("null")
        return
    
    result = []
    queue = deque([root])
    
    while queue:
        node = queue.popleft()
        if node:
            result.append(str(node.val))
            queue.append(node.left)
            queue.append(node.right)
        else:
            result.append("null")
    
    # Remove trailing nulls
    while result and result[-1] == "null":
        result.pop()
    
    print(result)


# Test
if __name__ == "__main__":
    # Test case: [1,2,3,null,null,4,5]
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.right.left = TreeNode(4)
    root.right.right = TreeNode(5)
    
    print("=== DFS Codec ===")
    codec_dfs = Codec()
    
    print("Original tree: ", end="")
    print_tree(root)
    
    serialized = codec_dfs.serialize(root)
    print(f"Serialized: {serialized}")
    
    deserialized = codec_dfs.deserialize(serialized)
    print("Deserialized tree: ", end="")
    print_tree(deserialized)
    
    print("\n=== BFS Codec ===")
    codec_bfs = CodecBFS()
    
    serialized_bfs = codec_bfs.serialize(root)
    print(f"Serialized: {serialized_bfs}")
    
    deserialized_bfs = codec_bfs.deserialize(serialized_bfs)
    print("Deserialized tree: ", end="")
    print_tree(deserialized_bfs)

