"""
LeetCode 128: Longest Consecutive Sequence
https://leetcode.com/problems/longest-consecutive-sequence/

Given an unsorted array of integers nums, return the length of the 
longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

Time Complexity: O(n)
Space Complexity: O(n)
"""

from typing import List


class Solution:
    # Solution 1: Hash Set - find sequence starts (Optimal)
    def longestConsecutive(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        num_set = set(nums)
        max_len = 0
        
        for num in num_set:
            # Only start counting if num is the START of a sequence
            # i.e., num-1 doesn't exist in set
            if num - 1 not in num_set:
                current_num = num
                current_len = 1
                
                # Count consecutive numbers
                while current_num + 1 in num_set:
                    current_num += 1
                    current_len += 1
                
                max_len = max(max_len, current_len)
        
        return max_len
    
    # Solution 2: Sorting
    # Time: O(n log n)
    def longestConsecutiveSorting(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        nums = sorted(set(nums))  # Remove duplicates and sort
        
        max_len = 1
        current_len = 1
        
        for i in range(1, len(nums)):
            if nums[i] == nums[i - 1] + 1:
                current_len += 1
            else:
                max_len = max(max_len, current_len)
                current_len = 1
        
        return max(max_len, current_len)
    
    # Solution 3: Expand from each element
    def longestConsecutiveExpand(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        num_set = set(nums)
        max_len = 0
        
        while num_set:
            num = num_set.pop()
            left = num - 1
            right = num + 1
            
            # Expand left
            while left in num_set:
                num_set.remove(left)
                left -= 1
            
            # Expand right
            while right in num_set:
                num_set.remove(right)
                right += 1
            
            max_len = max(max_len, right - left - 1)
        
        return max_len


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    nums1 = [100, 4, 200, 1, 3, 2]
    print(f"Test 1 [100,4,200,1,3,2]: {sol.longestConsecutive(nums1)}")
    # Expected: 4 (sequence: 1,2,3,4)
    
    # Test Case 2: Longer sequence
    nums2 = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
    print(f"Test 2 [0,3,7,2,5,8,4,6,0,1]: {sol.longestConsecutive(nums2)}")
    # Expected: 9 (sequence: 0,1,2,3,4,5,6,7,8)
    
    # Test Case 3: Empty array
    nums3 = []
    print(f"Test 3 []: {sol.longestConsecutive(nums3)}")
    # Expected: 0
    
    # Test Case 4: Single element
    nums4 = [1]
    print(f"Test 4 [1]: {sol.longestConsecutive(nums4)}")
    # Expected: 1
    
    # Test Case 5: No consecutive (all same)
    nums5 = [5, 5, 5, 5]
    print(f"Test 5 [5,5,5,5]: {sol.longestConsecutive(nums5)}")
    # Expected: 1
    
    # Test Case 6: Negative numbers
    nums6 = [-3, -2, -1, 0, 1]
    print(f"Test 6 [-3,-2,-1,0,1]: {sol.longestConsecutive(nums6)}")
    # Expected: 5
    
    # Test Case 7: Separate sequences
    nums7 = [1, 2, 3, 100, 101, 102, 103]
    print(f"Test 7 [1,2,3,100,101,102,103]: {sol.longestConsecutive(nums7)}")
    # Expected: 4 (sequence: 100,101,102,103)

