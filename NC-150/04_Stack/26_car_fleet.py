"""
LeetCode 853: Car Fleet
https://leetcode.com/problems/car-fleet/

n cars are going to the same destination along a one-lane road.
A car fleet is some non-empty set of cars driving at the same position 
and same speed. Count the number of car fleets that will arrive at destination.

Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

from typing import List


class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        if not position:
            return 0
        
        # Create pairs of (position, time to reach target)
        cars = [(p, (target - p) / s) for p, s in zip(position, speed)]
        
        # Sort by position descending (closest to target first)
        cars.sort(reverse=True)
        
        # Count fleets
        fleets = []
        for pos, time in cars:
            if not fleets or time > fleets[-1]:
                # New fleet (slower car)
                fleets.append(time)
            # Else: catches up to fleet ahead
        
        return len(fleets)
    
    # Solution 2: Without explicit stack
    def carFleetSimple(self, target: int, position: List[int], speed: List[int]) -> int:
        if not position:
            return 0
        
        cars = sorted(zip(position, speed), reverse=True)
        fleets = 0
        max_time = 0
        
        for pos, spd in cars:
            time = (target - pos) / spd
            if time > max_time:
                fleets += 1
                max_time = time
        
        return fleets


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    pos1 = [10, 8, 0, 5, 3]
    speed1 = [2, 4, 1, 1, 3]
    print(f"Test 1: {sol.carFleet(12, pos1, speed1)}")
    # Expected: 3
    
    # Test Case 2: Single car
    pos2 = [3]
    speed2 = [3]
    print(f"Test 2: {sol.carFleet(10, pos2, speed2)}")
    # Expected: 1
    
    # Test Case 3: All catch up
    pos3 = [0, 2, 4]
    speed3 = [4, 2, 1]
    print(f"Test 3: {sol.carFleet(100, pos3, speed3)}")
    # Expected: 1
    
    # Test Case 4: None catch up
    pos4 = [6, 8]
    speed4 = [3, 2]
    print(f"Test 4: {sol.carFleet(10, pos4, speed4)}")
    # Expected: 2

