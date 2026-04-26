"""
Problem: Find the Duplicate Number (LeetCode 287)

Given an array of integers nums containing n + 1 integers where each integer
is in the range [1, n] inclusive. There is only one repeated number, find it.

Constraints:
- Must not modify the array
- Must use only constant extra space

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import List

class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        """Floyd's Cycle Detection - treat array as linked list"""
        # Phase 1: Find the intersection point
        slow = nums[0]
        fast = nums[0]
        
        while True:
            slow = nums[slow]           # Move 1 step
            fast = nums[nums[fast]]     # Move 2 steps
            if slow == fast:
                break
        
        # Phase 2: Find the entrance to the cycle (duplicate)
        slow = nums[0]
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        
        return slow
    
    def findDuplicateBinarySearch(self, nums: List[int]) -> int:
        """Binary Search approach - O(n log n) time, O(1) space"""
        left, right = 1, len(nums) - 1
        
        while left < right:
            mid = (left + right) // 2
            
            # Count numbers <= mid
            count = sum(1 for num in nums if num <= mid)
            
            # If count > mid, duplicate is in [1, mid]
            if count > mid:
                right = mid
            else:
                left = mid + 1
        
        return left

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [1,3,4,2,2] -> 2
    nums1 = [1, 3, 4, 2, 2]
    print(f"Array: {nums1}")
    print(f"Duplicate: {sol.findDuplicate(nums1)}")
    assert sol.findDuplicate(nums1) == 2
    
    # Test case 2: [3,1,3,4,2] -> 3
    nums2 = [3, 1, 3, 4, 2]
    print(f"\nArray: {nums2}")
    print(f"Duplicate: {sol.findDuplicate(nums2)}")
    assert sol.findDuplicate(nums2) == 3
    
    # Test case 3: [1,1] -> 1
    nums3 = [1, 1]
    print(f"\nArray: {nums3}")
    print(f"Duplicate: {sol.findDuplicate(nums3)}")
    assert sol.findDuplicate(nums3) == 1
    
    # Test case 4: [1,1,2] -> 1
    nums4 = [1, 1, 2]
    print(f"\nArray: {nums4}")
    print(f"Duplicate: {sol.findDuplicate(nums4)}")
    assert sol.findDuplicate(nums4) == 1
    
    # Test case 5: [2,2,2,2,2] -> 2 (multiple duplicates of same number)
    nums5 = [2, 2, 2, 2, 2]
    print(f"\nArray: {nums5}")
    print(f"Duplicate: {sol.findDuplicate(nums5)}")
    assert sol.findDuplicate(nums5) == 2
    
    # Test binary search approach
    nums6 = [1, 3, 4, 2, 2]
    print(f"\nBinary search approach on {nums6}: {sol.findDuplicateBinarySearch(nums6)}")
    assert sol.findDuplicateBinarySearch(nums6) == 2
    
    print("\nAll test cases passed!")

