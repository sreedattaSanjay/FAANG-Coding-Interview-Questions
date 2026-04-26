"""
LeetCode 42: Trapping Rain Water
https://leetcode.com/problems/trapping-rain-water/

Given n non-negative integers representing an elevation map where the width 
of each bar is 1, compute how much water it can trap after raining.

Time Complexity: O(n)
Space Complexity: O(1) for two-pointer approach
"""

from typing import List


class Solution:
    # Solution 1: Two Pointers (Optimal)
    def trap(self, height: List[int]) -> int:
        if not height:
            return 0
        
        left, right = 0, len(height) - 1
        left_max, right_max = 0, 0
        water = 0
        
        while left < right:
            if height[left] < height[right]:
                if height[left] >= left_max:
                    left_max = height[left]
                else:
                    water += left_max - height[left]
                left += 1
            else:
                if height[right] >= right_max:
                    right_max = height[right]
                else:
                    water += right_max - height[right]
                right -= 1
        
        return water
    
    # Solution 2: Prefix/Suffix Max Arrays
    # Time: O(n), Space: O(n)
    def trapArrays(self, height: List[int]) -> int:
        if not height:
            return 0
        
        n = len(height)
        left_max = [0] * n
        right_max = [0] * n
        
        # Build left max array
        left_max[0] = height[0]
        for i in range(1, n):
            left_max[i] = max(left_max[i - 1], height[i])
        
        # Build right max array
        right_max[n - 1] = height[n - 1]
        for i in range(n - 2, -1, -1):
            right_max[i] = max(right_max[i + 1], height[i])
        
        # Calculate water
        water = 0
        for i in range(n):
            water += min(left_max[i], right_max[i]) - height[i]
        
        return water
    
    # Solution 3: Monotonic Stack
    # Time: O(n), Space: O(n)
    def trapStack(self, height: List[int]) -> int:
        stack = []
        water = 0
        
        for i in range(len(height)):
            while stack and height[i] > height[stack[-1]]:
                bottom = stack.pop()
                
                if not stack:
                    break
                
                width = i - stack[-1] - 1
                h = min(height[i], height[stack[-1]]) - height[bottom]
                water += width * h
            
            stack.append(i)
        
        return water


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    height1 = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    print(f"Test 1 [0,1,0,2,1,0,1,3,2,1,2,1]: {sol.trap(height1)}")
    # Expected: 6
    
    # Test Case 2: Another case
    height2 = [4, 2, 0, 3, 2, 5]
    print(f"Test 2 [4,2,0,3,2,5]: {sol.trap(height2)}")
    # Expected: 9
    
    # Test Case 3: Empty
    height3 = []
    print(f"Test 3 []: {sol.trap(height3)}")
    # Expected: 0
    
    # Test Case 4: No water (increasing)
    height4 = [1, 2, 3, 4]
    print(f"Test 4 [1,2,3,4]: {sol.trap(height4)}")
    # Expected: 0
    
    # Test Case 5: No water (decreasing)
    height5 = [4, 3, 2, 1]
    print(f"Test 5 [4,3,2,1]: {sol.trap(height5)}")
    # Expected: 0
    
    # Test Case 6: Single element
    height6 = [5]
    print(f"Test 6 [5]: {sol.trap(height6)}")
    # Expected: 0
    
    # Test Case 7: Valley
    height7 = [5, 2, 5]
    print(f"Test 7 [5,2,5]: {sol.trap(height7)}")
    # Expected: 3

