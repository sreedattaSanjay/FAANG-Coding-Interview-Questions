"""
LeetCode 15: 3Sum
https://leetcode.com/problems/3sum/

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Time Complexity: O(n^2)
Space Complexity: O(1) excluding output (O(n) for sorting)
"""

from typing import List


class Solution:
    # Solution 1: Sort + Two Pointers (Optimal)
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        n = len(nums)
        
        if n < 3:
            return result
        
        # Sort the array
        nums.sort()
        
        for i in range(n - 2):
            # Skip duplicates for i
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            
            # Early termination: if smallest is positive, no solution
            if nums[i] > 0:
                break
            
            left = i + 1
            right = n - 1
            target = -nums[i]
            
            while left < right:
                current_sum = nums[left] + nums[right]
                
                if current_sum == target:
                    result.append([nums[i], nums[left], nums[right]])
                    
                    # Skip duplicates for left
                    while left < right and nums[left] == nums[left + 1]:
                        left += 1
                    # Skip duplicates for right
                    while left < right and nums[right] == nums[right - 1]:
                        right -= 1
                    
                    left += 1
                    right -= 1
                elif current_sum < target:
                    left += 1
                else:
                    right -= 1
        
        return result
    
    # Solution 2: Using set to handle duplicates
    def threeSumSet(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        result = set()
        
        for i in range(len(nums) - 2):
            if nums[i] > 0:
                break
            
            left, right = i + 1, len(nums) - 1
            
            while left < right:
                s = nums[i] + nums[left] + nums[right]
                
                if s == 0:
                    result.add((nums[i], nums[left], nums[right]))
                    left += 1
                    right -= 1
                elif s < 0:
                    left += 1
                else:
                    right -= 1
        
        return [list(t) for t in result]


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case with multiple solutions
    nums1 = [-1, 0, 1, 2, -1, -4]
    print(f"Test 1 [-1,0,1,2,-1,-4]: {sol.threeSum(nums1)}")
    # Expected: [[-1,-1,2],[-1,0,1]]
    
    # Test Case 2: All zeros
    nums2 = [0, 0, 0, 0]
    print(f"Test 2 [0,0,0,0]: {sol.threeSum(nums2)}")
    # Expected: [[0,0,0]]
    
    # Test Case 3: No solution
    nums3 = [1, 2, 3]
    print(f"Test 3 [1,2,3]: {sol.threeSum(nums3)}")
    # Expected: []
    
    # Test Case 4: Empty array
    nums4 = []
    print(f"Test 4 []: {sol.threeSum(nums4)}")
    # Expected: []
    
    # Test Case 5: Exactly 3 elements that sum to 0
    nums5 = [-1, 0, 1]
    print(f"Test 5 [-1,0,1]: {sol.threeSum(nums5)}")
    # Expected: [[-1,0,1]]
    
    # Test Case 6: Many duplicates
    nums6 = [-2, 0, 0, 2, 2]
    print(f"Test 6 [-2,0,0,2,2]: {sol.threeSum(nums6)}")
    # Expected: [[-2,0,2]]

