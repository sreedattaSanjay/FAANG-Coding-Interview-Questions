"""
LeetCode 239: Sliding Window Maximum
https://leetcode.com/problems/sliding-window-maximum/

Given an array of integers nums and a sliding window of size k moving from 
left to right, return the max value in each window.

Time Complexity: O(n)
Space Complexity: O(k) for the deque
"""

from typing import List
from collections import deque
import heapq


class Solution:
    # Solution 1: Monotonic Decreasing Deque (Optimal)
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        result = []
        dq = deque()  # Stores indices, maintains decreasing order of values
        
        for i in range(len(nums)):
            # Remove elements outside window
            while dq and dq[0] < i - k + 1:
                dq.popleft()
            
            # Remove smaller elements (they can never be max)
            while dq and nums[dq[-1]] < nums[i]:
                dq.pop()
            
            dq.append(i)
            
            # Add to result once window is formed
            if i >= k - 1:
                result.append(nums[dq[0]])
        
        return result
    
    # Solution 2: Max Heap with lazy deletion
    def maxSlidingWindowHeap(self, nums: List[int], k: int) -> List[int]:
        result = []
        # Python has min-heap, so negate values for max-heap
        max_heap = []  # (-value, index)
        
        for i in range(len(nums)):
            heapq.heappush(max_heap, (-nums[i], i))
            
            # Remove elements outside window (lazy deletion)
            while max_heap[0][1] <= i - k:
                heapq.heappop(max_heap)
            
            if i >= k - 1:
                result.append(-max_heap[0][0])
        
        return result
    
    # Solution 3: Brute Force (for comparison)
    def maxSlidingWindowBruteForce(self, nums: List[int], k: int) -> List[int]:
        return [max(nums[i:i+k]) for i in range(len(nums) - k + 1)]


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    nums1 = [1, 3, -1, -3, 5, 3, 6, 7]
    print(f"Test 1 [1,3,-1,-3,5,3,6,7] k=3: {sol.maxSlidingWindow(nums1, 3)}")
    # Expected: [3, 3, 5, 5, 6, 7]
    
    # Test Case 2: k = 1
    nums2 = [1, -1]
    print(f"Test 2 [1,-1] k=1: {sol.maxSlidingWindow(nums2, 1)}")
    # Expected: [1, -1]
    
    # Test Case 3: k = array length
    nums3 = [1, 2, 3]
    print(f"Test 3 [1,2,3] k=3: {sol.maxSlidingWindow(nums3, 3)}")
    # Expected: [3]
    
    # Test Case 4: All same elements
    nums4 = [5, 5, 5, 5]
    print(f"Test 4 [5,5,5,5] k=2: {sol.maxSlidingWindow(nums4, 2)}")
    # Expected: [5, 5, 5]
    
    # Test Case 5: Decreasing array
    nums5 = [9, 8, 7, 6, 5]
    print(f"Test 5 [9,8,7,6,5] k=2: {sol.maxSlidingWindow(nums5, 2)}")
    # Expected: [9, 8, 7, 6]
    
    # Test Case 6: Increasing array
    nums6 = [1, 2, 3, 4, 5]
    print(f"Test 6 [1,2,3,4,5] k=2: {sol.maxSlidingWindow(nums6, 2)}")
    # Expected: [2, 3, 4, 5]

