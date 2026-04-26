"""
LeetCode 4: Median of Two Sorted Arrays
https://leetcode.com/problems/median-of-two-sorted-arrays/

Find median of two sorted arrays in O(log(m+n)) time.

Time Complexity: O(log(min(m,n)))
Space Complexity: O(1)
"""

from typing import List


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        # Ensure nums1 is smaller
        if len(nums1) > len(nums2):
            nums1, nums2 = nums2, nums1
        
        m, n = len(nums1), len(nums2)
        left, right = 0, m
        half = (m + n + 1) // 2
        
        while left <= right:
            i = left + (right - left) // 2
            j = half - i
            
            nums1_left = float('-inf') if i == 0 else nums1[i - 1]
            nums1_right = float('inf') if i == m else nums1[i]
            nums2_left = float('-inf') if j == 0 else nums2[j - 1]
            nums2_right = float('inf') if j == n else nums2[j]
            
            if nums1_left <= nums2_right and nums2_left <= nums1_right:
                # Found correct partition
                if (m + n) % 2 == 0:
                    return (max(nums1_left, nums2_left) + min(nums1_right, nums2_right)) / 2
                else:
                    return max(nums1_left, nums2_left)
            elif nums1_left > nums2_right:
                right = i - 1
            else:
                left = i + 1
        
        return 0.0


if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test 1 [1,3] [2]: {sol.findMedianSortedArrays([1,3], [2])}")
    # Expected: 2.0
    
    print(f"Test 2 [1,2] [3,4]: {sol.findMedianSortedArrays([1,2], [3,4])}")
    # Expected: 2.5

