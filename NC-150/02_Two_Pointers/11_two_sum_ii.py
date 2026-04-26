"""
LeetCode 167: Two Sum II - Input Array Is Sorted
https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

Given a 1-indexed array of integers numbers that is already sorted in 
non-decreasing order, find two numbers such that they add up to a specific 
target number. Return the indices of the two numbers (1-indexed).

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import List
import bisect


class Solution:
    # Solution 1: Two Pointers (Optimal)
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        left, right = 0, len(numbers) - 1
        
        while left < right:
            current_sum = numbers[left] + numbers[right]
            
            if current_sum == target:
                return [left + 1, right + 1]  # 1-indexed
            elif current_sum < target:
                left += 1   # Need larger sum
            else:
                right -= 1  # Need smaller sum
        
        return []  # No solution found
    
    # Solution 2: Binary Search for each element
    # Time: O(n log n)
    def twoSumBinarySearch(self, numbers: List[int], target: int) -> List[int]:
        for i in range(len(numbers)):
            complement = target - numbers[i]
            
            # Binary search for complement in [i+1, n-1]
            j = bisect.bisect_left(numbers, complement, i + 1)
            
            if j < len(numbers) and numbers[j] == complement:
                return [i + 1, j + 1]
        
        return []


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    nums1 = [2, 7, 11, 15]
    print(f"Test 1 [2,7,11,15] target=9: {sol.twoSum(nums1, 9)}")
    # Expected: [1, 2]
    
    # Test Case 2: Target in middle
    nums2 = [2, 3, 4]
    print(f"Test 2 [2,3,4] target=6: {sol.twoSum(nums2, 6)}")
    # Expected: [1, 3]
    
    # Test Case 3: Negative numbers
    nums3 = [-1, 0]
    print(f"Test 3 [-1,0] target=-1: {sol.twoSum(nums3, -1)}")
    # Expected: [1, 2]
    
    # Test Case 4: Large gap between numbers
    nums4 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    print(f"Test 4 [1,2,3,4,5,6,7,8,9] target=17: {sol.twoSum(nums4, 17)}")
    # Expected: [8, 9]
    
    # Test Case 5: Same numbers
    nums5 = [3, 3]
    print(f"Test 5 [3,3] target=6: {sol.twoSum(nums5, 6)}")
    # Expected: [1, 2]

