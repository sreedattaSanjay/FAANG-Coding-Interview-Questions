"""
LeetCode 875: Koko Eating Bananas
https://leetcode.com/problems/koko-eating-bananas/

Koko can eat k bananas per hour. Find minimum k to eat all bananas in h hours.

Time Complexity: O(n * log(max(piles)))
Space Complexity: O(1)
"""

from typing import List
import math


class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        left, right = 1, max(piles)
        
        while left < right:
            mid = left + (right - left) // 2
            
            if self.can_finish(piles, mid, h):
                right = mid
            else:
                left = mid + 1
        
        return left
    
    def can_finish(self, piles: List[int], k: int, h: int) -> bool:
        hours = sum(math.ceil(pile / k) for pile in piles)
        return hours <= h


if __name__ == "__main__":
    sol = Solution()
    
    piles1 = [3, 6, 7, 11]
    print(f"Test 1 [3,6,7,11] h=8: {sol.minEatingSpeed(piles1, 8)}")
    # Expected: 4
    
    piles2 = [30, 11, 23, 4, 20]
    print(f"Test 2 [30,11,23,4,20] h=5: {sol.minEatingSpeed(piles2, 5)}")
    # Expected: 30
    
    print(f"Test 3 [30,11,23,4,20] h=6: {sol.minEatingSpeed(piles2, 6)}")
    # Expected: 23

