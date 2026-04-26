"""
LeetCode 1: Two Sum
https://leetcode.com/problems/two-sum/

Given an array of integers nums and an integer target, return indices of 
the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you 
may not use the same element twice.

Time Complexity: O(n) - single pass through array
Space Complexity: O(n) - hash map storage
"""

from typing import List


class Solution:
    # Solution 1: Hash Map - One Pass (Optimal)
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        num_to_index = {}
        
        for i, num in enumerate(nums):
            complement = target - num
            
            if complement in num_to_index:
                return [num_to_index[complement], i]
            
            num_to_index[num] = i
        
        return []  # No solution found
    
    # Solution 2: Hash Map - Two Pass
    def twoSumTwoPass(self, nums: List[int], target: int) -> List[int]:
        num_to_index = {num: i for i, num in enumerate(nums)}
        
        for i, num in enumerate(nums):
            complement = target - num
            if complement in num_to_index and num_to_index[complement] != i:
                return [i, num_to_index[complement]]
        
        return []
    
    # Solution 3: Brute Force
    # Time: O(n^2), Space: O(1)
    def twoSumBruteForce(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            for j in range(i + 1, len(nums)):
                if nums[i] + nums[j] == target:
                    return [i, j]
        return []


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    nums1 = [2, 7, 11, 15]
    print(f"Test 1 [2,7,11,15] target=9: {sol.twoSum(nums1, 9)}")
    # Expected: [0, 1]
    
    # Test Case 2: Non-adjacent elements
    nums2 = [3, 2, 4]
    print(f"Test 2 [3,2,4] target=6: {sol.twoSum(nums2, 6)}")
    # Expected: [1, 2]
    
    # Test Case 3: Same number twice
    nums3 = [3, 3]
    print(f"Test 3 [3,3] target=6: {sol.twoSum(nums3, 6)}")
    # Expected: [0, 1]
    
    # Test Case 4: Negative numbers
    nums4 = [-1, -2, -3, -4, -5]
    print(f"Test 4 [-1,-2,-3,-4,-5] target=-8: {sol.twoSum(nums4, -8)}")
    # Expected: [2, 4]
    
    # Test Case 5: Zero in array
    nums5 = [0, 4, 3, 0]
    print(f"Test 5 [0,4,3,0] target=0: {sol.twoSum(nums5, 0)}")
    # Expected: [0, 3]
    
    # Test Case 6: Large numbers
    nums6 = [1000000000, 2000000000]
    print(f"Test 6 [1000000000, 2000000000] target=3000000000: {sol.twoSum(nums6, 3000000000)}")
    # Expected: [0, 1]

