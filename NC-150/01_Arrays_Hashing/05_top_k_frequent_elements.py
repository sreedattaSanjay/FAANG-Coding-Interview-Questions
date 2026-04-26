"""
LeetCode 347: Top K Frequent Elements
https://leetcode.com/problems/top-k-frequent-elements/

Given an integer array nums and an integer k, return the k most frequent elements. 
You may return the answer in any order.

Time Complexity: O(n) using bucket sort, O(n log k) using heap
Space Complexity: O(n)
"""

from typing import List
from collections import Counter
import heapq


class Solution:
    # Solution 1: Bucket Sort (Optimal - O(n))
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        # Count frequencies
        freq = Counter(nums)
        
        # Create buckets where index = frequency
        buckets = [[] for _ in range(len(nums) + 1)]
        for num, count in freq.items():
            buckets[count].append(num)
        
        # Collect k most frequent from highest bucket down
        result = []
        for i in range(len(buckets) - 1, -1, -1):
            for num in buckets[i]:
                result.append(num)
                if len(result) == k:
                    return result
        
        return result
    
    # Solution 2: Heap (O(n log k))
    def topKFrequentHeap(self, nums: List[int], k: int) -> List[int]:
        freq = Counter(nums)
        # nlargest uses a min-heap internally, efficient for small k
        return [num for num, count in heapq.nlargest(k, freq.items(), key=lambda x: x[1])]
    
    # Solution 3: Using Counter.most_common (Pythonic)
    def topKFrequentCounter(self, nums: List[int], k: int) -> List[int]:
        return [num for num, count in Counter(nums).most_common(k)]
    
    # Solution 4: Quickselect-based (O(n) average)
    def topKFrequentQuickselect(self, nums: List[int], k: int) -> List[int]:
        freq = Counter(nums)
        unique = list(freq.keys())
        
        def partition(left, right, pivot_idx):
            pivot_freq = freq[unique[pivot_idx]]
            # Move pivot to end
            unique[pivot_idx], unique[right] = unique[right], unique[pivot_idx]
            store_idx = left
            
            for i in range(left, right):
                if freq[unique[i]] < pivot_freq:
                    unique[store_idx], unique[i] = unique[i], unique[store_idx]
                    store_idx += 1
            
            unique[store_idx], unique[right] = unique[right], unique[store_idx]
            return store_idx
        
        def quickselect(left, right, k_smallest):
            if left == right:
                return
            
            import random
            pivot_idx = random.randint(left, right)
            pivot_idx = partition(left, right, pivot_idx)
            
            if k_smallest == pivot_idx:
                return
            elif k_smallest < pivot_idx:
                quickselect(left, pivot_idx - 1, k_smallest)
            else:
                quickselect(pivot_idx + 1, right, k_smallest)
        
        n = len(unique)
        quickselect(0, n - 1, n - k)
        return unique[n - k:]


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    nums1 = [1, 1, 1, 2, 2, 3]
    print(f"Test 1 [1,1,1,2,2,3] k=2: {sol.topKFrequent(nums1, 2)}")
    # Expected: [1, 2] (any order)
    
    # Test Case 2: k = 1
    nums2 = [1]
    print(f"Test 2 [1] k=1: {sol.topKFrequent(nums2, 1)}")
    # Expected: [1]
    
    # Test Case 3: All same frequency
    nums3 = [1, 2, 3, 4]
    print(f"Test 3 [1,2,3,4] k=2: {sol.topKFrequent(nums3, 2)}")
    # Expected: any 2 elements
    
    # Test Case 4: Negative numbers
    nums4 = [-1, -1, -2, -2, -2, -3]
    print(f"Test 4 [-1,-1,-2,-2,-2,-3] k=2: {sol.topKFrequent(nums4, 2)}")
    # Expected: [-2, -1] (any order)
    
    # Test Case 5: k equals unique elements
    nums5 = [1, 2]
    print(f"Test 5 [1,2] k=2: {sol.topKFrequent(nums5, 2)}")
    # Expected: [1, 2] (any order)

