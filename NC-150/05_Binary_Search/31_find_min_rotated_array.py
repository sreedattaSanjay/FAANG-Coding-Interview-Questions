"""
LeetCode 153: Find Minimum in Rotated Sorted Array
https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

Given a rotated sorted array with unique elements, find the minimum element.

Time Complexity: O(log n)
Space Complexity: O(1)
"""

from typing import List


class Solution:
    def findMin(self, nums: List[int]) -> int:
        left, right = 0, len(nums) - 1
        
        while left < right:
            mid = left + (right - left) // 2
            
            if nums[mid] > nums[right]:
                # Minimum is in right half
                left = mid + 1
            else:
                # Minimum is in left half (including mid)
                right = mid
        
        return nums[left]


if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test 1 [3,4,5,1,2]: {sol.findMin([3,4,5,1,2])}")
    # Expected: 1
    
    print(f"Test 2 [4,5,6,7,0,1,2]: {sol.findMin([4,5,6,7,0,1,2])}")
    # Expected: 0
    
    print(f"Test 3 [11,13,15,17]: {sol.findMin([11,13,15,17])}")
    # Expected: 11

