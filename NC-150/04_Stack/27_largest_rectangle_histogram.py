"""
LeetCode 84: Largest Rectangle in Histogram
https://leetcode.com/problems/largest-rectangle-in-histogram/

Given an array of integers heights representing the histogram's bar height,
return the area of the largest rectangle in the histogram.

Time Complexity: O(n)
Space Complexity: O(n)
"""

from typing import List


class Solution:
    # Solution 1: Monotonic Increasing Stack
    def largestRectangleArea(self, heights: List[int]) -> int:
        stack = []  # Stores indices
        max_area = 0
        
        # Add sentinel value at end
        heights = heights + [0]
        
        for i, h in enumerate(heights):
            while stack and h < heights[stack[-1]]:
                height = heights[stack.pop()]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)
        
        return max_area
    
    # Solution 2: Two-pass to find boundaries
    def largestRectangleAreaTwoPass(self, heights: List[int]) -> int:
        n = len(heights)
        left = [-1] * n
        right = [n] * n
        stack = []
        
        # Find left boundary
        for i in range(n):
            while stack and heights[stack[-1]] >= heights[i]:
                stack.pop()
            left[i] = stack[-1] if stack else -1
            stack.append(i)
        
        stack = []
        
        # Find right boundary
        for i in range(n - 1, -1, -1):
            while stack and heights[stack[-1]] >= heights[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n
            stack.append(i)
        
        # Calculate max area
        max_area = 0
        for i in range(n):
            width = right[i] - left[i] - 1
            max_area = max(max_area, heights[i] * width)
        
        return max_area


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    heights1 = [2, 1, 5, 6, 2, 3]
    print(f"Test 1 [2,1,5,6,2,3]: {sol.largestRectangleArea(heights1)}")
    # Expected: 10
    
    # Test Case 2: Two bars
    heights2 = [2, 4]
    print(f"Test 2 [2,4]: {sol.largestRectangleArea(heights2)}")
    # Expected: 4
    
    # Test Case 3: Single bar
    heights3 = [5]
    print(f"Test 3 [5]: {sol.largestRectangleArea(heights3)}")
    # Expected: 5
    
    # Test Case 4: Increasing
    heights4 = [1, 2, 3, 4, 5]
    print(f"Test 4 [1,2,3,4,5]: {sol.largestRectangleArea(heights4)}")
    # Expected: 9
    
    # Test Case 5: Decreasing
    heights5 = [5, 4, 3, 2, 1]
    print(f"Test 5 [5,4,3,2,1]: {sol.largestRectangleArea(heights5)}")
    # Expected: 9

