"""
LeetCode 11: Container With Most Water
https://leetcode.com/problems/container-with-most-water/

Given n non-negative integers height representing an elevation map where 
the width of each bar is 1, find two lines that together with the x-axis 
form a container, such that the container contains the most water.

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import List


class Solution:
    # Solution 1: Two Pointers (Optimal)
    def maxArea(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        max_water = 0
        
        while left < right:
            # Calculate area: width * min(left height, right height)
            width = right - left
            h = min(height[left], height[right])
            area = width * h
            
            max_water = max(max_water, area)
            
            # Move the pointer with smaller height
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        
        return max_water
    
    # Solution 2: Two pointers with optimization (skip smaller heights)
    def maxAreaOptimized(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        max_water = 0
        
        while left < right:
            h = min(height[left], height[right])
            max_water = max(max_water, (right - left) * h)
            
            # Skip all heights smaller than current minimum
            while left < right and height[left] <= h:
                left += 1
            while left < right and height[right] <= h:
                right -= 1
        
        return max_water
    
    # Solution 3: Brute Force (for comparison)
    # Time: O(n^2)
    def maxAreaBruteForce(self, height: List[int]) -> int:
        max_water = 0
        n = len(height)
        
        for i in range(n):
            for j in range(i + 1, n):
                width = j - i
                h = min(height[i], height[j])
                max_water = max(max_water, width * h)
        
        return max_water


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    print(f"Test 1 [1,8,6,2,5,4,8,3,7]: {sol.maxArea(height1)}")
    # Expected: 49
    
    # Test Case 2: Two elements
    height2 = [1, 1]
    print(f"Test 2 [1,1]: {sol.maxArea(height2)}")
    # Expected: 1
    
    # Test Case 3: Decreasing heights
    height3 = [4, 3, 2, 1, 4]
    print(f"Test 3 [4,3,2,1,4]: {sol.maxArea(height3)}")
    # Expected: 16
    
    # Test Case 4: All same height
    height4 = [5, 5, 5, 5, 5]
    print(f"Test 4 [5,5,5,5,5]: {sol.maxArea(height4)}")
    # Expected: 20
    
    # Test Case 5: One very tall
    height5 = [1, 2, 100, 2, 1]
    print(f"Test 5 [1,2,100,2,1]: {sol.maxArea(height5)}")
    # Expected: 4
    
    # Test Case 6: Large at ends
    height6 = [10, 1, 1, 1, 10]
    print(f"Test 6 [10,1,1,1,10]: {sol.maxArea(height6)}")
    # Expected: 40

