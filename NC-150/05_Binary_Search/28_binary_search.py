"""
LeetCode 704: Binary Search
https://leetcode.com/problems/binary-search/

Given an array of integers nums sorted in ascending order, and a target value,
write a function to search for target. Return index if found, else return -1.

Time Complexity: O(log n)
Space Complexity: O(1)
"""

from typing import List


class Solution:
    # Solution 1: Iterative Binary Search
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        
        return -1
    
    # Solution 2: Recursive Binary Search
    def searchRecursive(self, nums: List[int], target: int) -> int:
        def binary_search(left: int, right: int) -> int:
            if left > right:
                return -1
            
            mid = left + (right - left) // 2
            
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                return binary_search(mid + 1, right)
            else:
                return binary_search(left, mid - 1)
        
        return binary_search(0, len(nums) - 1)
    
    # Solution 3: Using bisect (library)
    def searchBisect(self, nums: List[int], target: int) -> int:
        import bisect
        i = bisect.bisect_left(nums, target)
        if i < len(nums) and nums[i] == target:
            return i
        return -1


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Target in middle
    nums1 = [-1, 0, 3, 5, 9, 12]
    print(f"Test 1 target=9: {sol.search(nums1, 9)}")
    # Expected: 4
    
    # Test Case 2: Target not found
    print(f"Test 2 target=2: {sol.search(nums1, 2)}")
    # Expected: -1
    
    # Test Case 3: Single element found
    nums3 = [5]
    print(f"Test 3 [5] target=5: {sol.search(nums3, 5)}")
    # Expected: 0
    
    # Test Case 4: Single element not found
    print(f"Test 4 [5] target=1: {sol.search(nums3, 1)}")
    # Expected: -1
    
    # Test Case 5: First element
    print(f"Test 5 target=-1: {sol.search(nums1, -1)}")
    # Expected: 0
    
    # Test Case 6: Last element
    print(f"Test 6 target=12: {sol.search(nums1, 12)}")
    # Expected: 5

