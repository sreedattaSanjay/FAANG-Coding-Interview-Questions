"""
LeetCode 33: Search in Rotated Sorted Array
https://leetcode.com/problems/search-in-rotated-sorted-array/

Search for target in rotated sorted array with unique elements.

Time Complexity: O(log n)
Space Complexity: O(1)
"""

from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            
            if nums[mid] == target:
                return mid
            
            # Check which half is sorted
            if nums[left] <= nums[mid]:
                # Left half is sorted
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                # Right half is sorted
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        
        return -1


if __name__ == "__main__":
    sol = Solution()
    
    nums = [4, 5, 6, 7, 0, 1, 2]
    print(f"Test 1 target=0: {sol.search(nums, 0)}")
    # Expected: 4
    
    print(f"Test 2 target=3: {sol.search(nums, 3)}")
    # Expected: -1

