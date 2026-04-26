"""
LeetCode 121: Best Time to Buy and Sell Stock
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

You are given an array prices where prices[i] is the price of a given stock 
on the ith day. You want to maximize your profit by choosing a single day to 
buy and a single day to sell in the future.

Return the maximum profit you can achieve. If no profit is possible, return 0.

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import List


class Solution:
    # Solution 1: Track minimum price seen so far
    def maxProfit(self, prices: List[int]) -> int:
        min_price = float('inf')
        max_profit = 0
        
        for price in prices:
            min_price = min(min_price, price)
            max_profit = max(max_profit, price - min_price)
        
        return max_profit
    
    # Solution 2: Kadane's Algorithm variant
    def maxProfitKadane(self, prices: List[int]) -> int:
        max_profit = 0
        current_profit = 0
        
        for i in range(1, len(prices)):
            current_profit = max(0, current_profit + prices[i] - prices[i - 1])
            max_profit = max(max_profit, current_profit)
        
        return max_profit
    
    # Solution 3: Two Pointers (Sliding Window perspective)
    def maxProfitTwoPointers(self, prices: List[int]) -> int:
        if not prices:
            return 0
        
        left = 0  # Buy day
        max_profit = 0
        
        for right in range(1, len(prices)):
            if prices[right] < prices[left]:
                left = right  # Found new minimum
            else:
                max_profit = max(max_profit, prices[right] - prices[left])
        
        return max_profit


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Normal profit scenario
    prices1 = [7, 1, 5, 3, 6, 4]
    print(f"Test 1 [7,1,5,3,6,4]: {sol.maxProfit(prices1)}")
    # Expected: 5
    
    # Test Case 2: No profit possible
    prices2 = [7, 6, 4, 3, 1]
    print(f"Test 2 [7,6,4,3,1]: {sol.maxProfit(prices2)}")
    # Expected: 0
    
    # Test Case 3: Single element
    prices3 = [1]
    print(f"Test 3 [1]: {sol.maxProfit(prices3)}")
    # Expected: 0
    
    # Test Case 4: Two elements with profit
    prices4 = [1, 2]
    print(f"Test 4 [1,2]: {sol.maxProfit(prices4)}")
    # Expected: 1
    
    # Test Case 5: All same prices
    prices5 = [3, 3, 3, 3]
    print(f"Test 5 [3,3,3,3]: {sol.maxProfit(prices5)}")
    # Expected: 0
    
    # Test Case 6: Buy at beginning, sell at end
    prices6 = [1, 2, 3, 4, 5]
    print(f"Test 6 [1,2,3,4,5]: {sol.maxProfit(prices6)}")
    # Expected: 4
    
    # Test Case 7: Maximum profit in middle
    prices7 = [3, 2, 6, 5, 0, 3]
    print(f"Test 7 [3,2,6,5,0,3]: {sol.maxProfit(prices7)}")
    # Expected: 4

