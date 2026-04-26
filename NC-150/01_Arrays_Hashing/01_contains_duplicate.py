"""
LeetCode 217: Contains Duplicate
https://leetcode.com/problems/contains-duplicate/

Given an integer array nums, return true if any value appears at least 
twice in the array, and return false if every element is distinct.

Time Complexity: O(n) - single pass through array
Space Complexity: O(n) - hash set storage
"""

from typing import List


class Solution:
    # Solution 1: Hash Set (Optimal)
    def containsDuplicate(self, nums: List[int]) -> bool:
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False
    
    # Solution 2: Set size comparison (Pythonic)
    def containsDuplicateSetSize(self, nums: List[int]) -> bool:
        return len(set(nums)) < len(nums)
    
    # Solution 3: Sorting approach
    # Time: O(n log n), Space: O(1) if in-place sort allowed
    def containsDuplicateSorting(self, nums: List[int]) -> bool:
        nums.sort()
        for i in range(1, len(nums)):
            if nums[i] == nums[i - 1]:
                return True
        return False


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Has duplicates
    nums1 = [1, 2, 3, 1]
    print(f"Test 1 [1,2,3,1]: {sol.containsDuplicate(nums1)}")
    # Expected: True
    
    # Test Case 2: No duplicates
    nums2 = [1, 2, 3, 4]
    print(f"Test 2 [1,2,3,4]: {sol.containsDuplicate(nums2)}")
    # Expected: False
    
    # Test Case 3: Multiple duplicates
    nums3 = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2]
    print(f"Test 3 [1,1,1,3,3,4,3,2,4,2]: {sol.containsDuplicate(nums3)}")
    # Expected: True
    
    # Test Case 4: Empty array
    nums4 = []
    print(f"Test 4 []: {sol.containsDuplicate(nums4)}")
    # Expected: False
    
    # Test Case 5: Single element
    nums5 = [1]
    print(f"Test 5 [1]: {sol.containsDuplicate(nums5)}")
    # Expected: False
    
    # Test Case 6: Two same elements
    nums6 = [1, 1]
    print(f"Test 6 [1,1]: {sol.containsDuplicate(nums6)}")
    # Expected: True
    
    # Test Case 7: Negative numbers
    nums7 = [-1, -2, -3, -1]
    print(f"Test 7 [-1,-2,-3,-1]: {sol.containsDuplicate(nums7)}")
    # Expected: True

