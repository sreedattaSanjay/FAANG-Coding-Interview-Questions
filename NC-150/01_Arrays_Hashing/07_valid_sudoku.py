"""
LeetCode 36: Valid Sudoku
https://leetcode.com/problems/valid-sudoku/

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be 
validated according to the following rules:
1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3x3 sub-boxes must contain digits 1-9 without repetition.

Time Complexity: O(81) = O(1) - fixed size board
Space Complexity: O(81) = O(1) - fixed size sets
"""

from typing import List
from collections import defaultdict


class Solution:
    # Solution 1: Three dictionaries of sets
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = defaultdict(set)
        cols = defaultdict(set)
        boxes = defaultdict(set)
        
        for i in range(9):
            for j in range(9):
                c = board[i][j]
                if c == '.':
                    continue
                
                box_idx = (i // 3, j // 3)
                
                if c in rows[i] or c in cols[j] or c in boxes[box_idx]:
                    return False
                
                rows[i].add(c)
                cols[j].add(c)
                boxes[box_idx].add(c)
        
        return True
    
    # Solution 2: Single set with encoded keys
    def isValidSudokuEncoded(self, board: List[List[str]]) -> bool:
        seen = set()
        
        for i in range(9):
            for j in range(9):
                c = board[i][j]
                if c == '.':
                    continue
                
                row_key = (c, 'row', i)
                col_key = (c, 'col', j)
                box_key = (c, 'box', i // 3, j // 3)
                
                if row_key in seen or col_key in seen or box_key in seen:
                    return False
                
                seen.add(row_key)
                seen.add(col_key)
                seen.add(box_key)
        
        return True
    
    # Solution 3: Bitmask approach
    def isValidSudokuBitmask(self, board: List[List[str]]) -> bool:
        rows = [0] * 9
        cols = [0] * 9
        boxes = [0] * 9
        
        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    continue
                
                num = int(board[i][j])
                mask = 1 << num
                box_idx = 3 * (i // 3) + (j // 3)
                
                if (rows[i] & mask) or (cols[j] & mask) or (boxes[box_idx] & mask):
                    return False
                
                rows[i] |= mask
                cols[j] |= mask
                boxes[box_idx] |= mask
        
        return True


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Valid Sudoku
    board1 = [
        ["5","3",".",".","7",".",".",".","."],
        ["6",".",".","1","9","5",".",".","."],
        [".","9","8",".",".",".",".","6","."],
        ["8",".",".",".","6",".",".",".","3"],
        ["4",".",".","8",".","3",".",".","1"],
        ["7",".",".",".","2",".",".",".","6"],
        [".","6",".",".",".",".","2","8","."],
        [".",".",".","4","1","9",".",".","5"],
        [".",".",".",".","8",".",".","7","9"]
    ]
    print(f"Test 1 (Valid): {sol.isValidSudoku(board1)}")
    # Expected: True
    
    # Test Case 2: Invalid - duplicate in column
    board2 = [
        ["8","3",".",".","7",".",".",".","."],
        ["6",".",".","1","9","5",".",".","."],
        [".","9","8",".",".",".",".","6","."],
        ["8",".",".",".","6",".",".",".","3"],
        ["4",".",".","8",".","3",".",".","1"],
        ["7",".",".",".","2",".",".",".","6"],
        [".","6",".",".",".",".","2","8","."],
        [".",".",".","4","1","9",".",".","5"],
        [".",".",".",".","8",".",".","7","9"]
    ]
    print(f"Test 2 (Invalid - duplicate 8 in col): {sol.isValidSudoku(board2)}")
    # Expected: False
    
    # Test Case 3: Empty board
    board3 = [["." for _ in range(9)] for _ in range(9)]
    print(f"Test 3 (Empty): {sol.isValidSudoku(board3)}")
    # Expected: True

