"""
LeetCode 74: Search a 2D Matrix
https://leetcode.com/problems/search-a-2d-matrix/

Given m x n matrix with sorted rows and first element of each row greater 
than last element of previous row, search for a target value.

Time Complexity: O(log(m*n))
Space Complexity: O(1)
"""

from typing import List


class Solution:
    # Solution 1: Treat as 1D sorted array
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        left, right = 0, m * n - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            mid_val = matrix[mid // n][mid % n]
            
            if mid_val == target:
                return True
            elif mid_val < target:
                left = mid + 1
            else:
                right = mid - 1
        
        return False
    
    # Solution 2: Two binary searches
    def searchMatrixTwoPass(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        
        # Find the row
        top, bottom = 0, m - 1
        while top <= bottom:
            mid_row = top + (bottom - top) // 2
            if target < matrix[mid_row][0]:
                bottom = mid_row - 1
            elif target > matrix[mid_row][n - 1]:
                top = mid_row + 1
            else:
                # Binary search in this row
                left, right = 0, n - 1
                while left <= right:
                    mid = left + (right - left) // 2
                    if matrix[mid_row][mid] == target:
                        return True
                    elif matrix[mid_row][mid] < target:
                        left = mid + 1
                    else:
                        right = mid - 1
                return False
        
        return False


if __name__ == "__main__":
    sol = Solution()
    
    matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]
    
    print(f"Test 1 target=3: {sol.searchMatrix(matrix, 3)}")
    # Expected: True
    
    print(f"Test 2 target=13: {sol.searchMatrix(matrix, 13)}")
    # Expected: False
    
    matrix2 = [[1]]
    print(f"Test 3 [[1]] target=1: {sol.searchMatrix(matrix2, 1)}")
    # Expected: True

