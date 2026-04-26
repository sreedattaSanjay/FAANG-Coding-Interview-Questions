"""
LeetCode 212: Word Search II
https://leetcode.com/problems/word-search-ii/

Given an m x n board of characters and a list of strings words, 
return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, 
where adjacent cells are horizontally or vertically neighboring. 
The same letter cell may not be used more than once in a word.

Approach: Build a Trie from words, then DFS on board using Trie for pruning

Time Complexity: O(m * n * 4^L) where L is max word length
Space Complexity: O(N * L) for Trie where N is number of words
"""

from typing import List


class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = None  # Store complete word at end node


class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # Build Trie from words
        root = TrieNode()
        for word in words:
            node = root
            for char in word:
                if char not in node.children:
                    node.children[char] = TrieNode()
                node = node.children[char]
            node.word = word
        
        result = []
        m, n = len(board), len(board[0])
        
        def dfs(row: int, col: int, node: TrieNode):
            # Bounds check
            if row < 0 or row >= m or col < 0 or col >= n:
                return
            
            char = board[row][col]
            
            # Already visited or no such prefix in Trie
            if char == '#' or char not in node.children:
                return
            
            node = node.children[char]
            
            # Found a word
            if node.word:
                result.append(node.word)
                node.word = None  # Avoid duplicates
            
            # Mark as visited
            board[row][col] = '#'
            
            # Explore all 4 directions
            dfs(row + 1, col, node)
            dfs(row - 1, col, node)
            dfs(row, col + 1, node)
            dfs(row, col - 1, node)
            
            # Restore cell
            board[row][col] = char
            
            # Optimization: prune Trie by removing leaf nodes
            # (helps when same word appears multiple times in board)
        
        # DFS from each cell
        for i in range(m):
            for j in range(n):
                dfs(i, j, root)
        
        return result


class SolutionOptimized:
    """Optimized version with Trie pruning"""
    
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # Build Trie
        root = {}
        for word in words:
            node = root
            for char in word:
                node = node.setdefault(char, {})
            node['$'] = word  # '$' marks end of word
        
        result = []
        m, n = len(board), len(board[0])
        
        def dfs(row: int, col: int, parent: dict):
            char = board[row][col]
            node = parent[char]
            
            # Check if word found
            word = node.pop('$', None)
            if word:
                result.append(word)
            
            # Mark visited
            board[row][col] = '#'
            
            # Explore neighbors
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = row + dr, col + dc
                if 0 <= nr < m and 0 <= nc < n and board[nr][nc] in node:
                    dfs(nr, nc, node)
            
            # Restore
            board[row][col] = char
            
            # Pruning: remove empty branches
            if not node:
                parent.pop(char)
        
        for i in range(m):
            for j in range(n):
                if board[i][j] in root:
                    dfs(i, j, root)
        
        return result


# Test
if __name__ == "__main__":
    # Test case 1
    board1 = [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ]
    words1 = ["oath", "pea", "eat", "rain"]
    
    sol = Solution()
    result1 = sol.findWords([row[:] for row in board1], words1)  # Copy board
    print(f"Test 1: {result1}")  # Expected: ["eat", "oath"]
    
    # Test case 2
    board2 = [
        ['a','b'],
        ['c','d']
    ]
    words2 = ["abcb"]
    
    result2 = sol.findWords(board2, words2)
    print(f"Test 2: {result2}")  # Expected: []
    
    # Test optimized version
    print("\nOptimized version:")
    sol_opt = SolutionOptimized()
    board1_copy = [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ]
    result1_opt = sol_opt.findWords(board1_copy, words1)
    print(f"Test 1: {result1_opt}")  # Expected: ["oath", "eat"] or ["eat", "oath"]

