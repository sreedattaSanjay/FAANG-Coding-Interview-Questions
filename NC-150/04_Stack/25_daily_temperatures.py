"""
LeetCode 739: Daily Temperatures
https://leetcode.com/problems/daily-temperatures/

Given an array of integers temperatures, return an array answer such that 
answer[i] is the number of days you have to wait after the ith day to get 
a warmer temperature.

Time Complexity: O(n)
Space Complexity: O(n)
"""

from typing import List


class Solution:
    # Solution 1: Monotonic Decreasing Stack
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        result = [0] * n
        stack = []  # Stores indices
        
        for i in range(n):
            # While current temp is warmer than temp at stack top
            while stack and temperatures[i] > temperatures[stack[-1]]:
                prev_index = stack.pop()
                result[prev_index] = i - prev_index
            stack.append(i)
        
        return result
    
    # Solution 2: Iterate from right
    def dailyTemperaturesFromRight(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        result = [0] * n
        
        for i in range(n - 2, -1, -1):
            j = i + 1
            while j < n:
                if temperatures[j] > temperatures[i]:
                    result[i] = j - i
                    break
                elif result[j] == 0:
                    break
                else:
                    j += result[j]
        
        return result


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    temps1 = [73, 74, 75, 71, 69, 72, 76, 73]
    print(f"Test 1: {sol.dailyTemperatures(temps1)}")
    # Expected: [1, 1, 4, 2, 1, 1, 0, 0]
    
    # Test Case 2: All increasing
    temps2 = [30, 40, 50, 60]
    print(f"Test 2: {sol.dailyTemperatures(temps2)}")
    # Expected: [1, 1, 1, 0]
    
    # Test Case 3: All same
    temps3 = [30, 30, 30]
    print(f"Test 3: {sol.dailyTemperatures(temps3)}")
    # Expected: [0, 0, 0]
    
    # Test Case 4: Decreasing then jump
    temps4 = [89, 62, 70, 58, 47, 90]
    print(f"Test 4: {sol.dailyTemperatures(temps4)}")
    # Expected: [5, 1, 3, 2, 1, 0]

