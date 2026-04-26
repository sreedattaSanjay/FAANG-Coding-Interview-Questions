"""
LeetCode 981: Time Based Key-Value Store
https://leetcode.com/problems/time-based-key-value-store/

Design a data structure that stores key-value pairs with timestamps.

Time Complexity: Set O(1), Get O(log n)
Space Complexity: O(n)
"""

from collections import defaultdict
import bisect


class TimeMap:
    def __init__(self):
        self.store = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.store[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        if key not in self.store:
            return ""
        
        values = self.store[key]
        left, right = 0, len(values) - 1
        result = ""
        
        while left <= right:
            mid = left + (right - left) // 2
            if values[mid][0] <= timestamp:
                result = values[mid][1]
                left = mid + 1
            else:
                right = mid - 1
        
        return result


# Using bisect library
class TimeMapBisect:
    def __init__(self):
        self.store = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.store[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        if key not in self.store:
            return ""
        
        values = self.store[key]
        i = bisect.bisect_right(values, (timestamp, chr(127)))
        
        return values[i - 1][1] if i > 0 else ""


if __name__ == "__main__":
    tm = TimeMap()
    
    tm.set("foo", "bar", 1)
    print(f"get('foo', 1): {tm.get('foo', 1)}")  # bar
    print(f"get('foo', 3): {tm.get('foo', 3)}")  # bar
    
    tm.set("foo", "bar2", 4)
    print(f"get('foo', 4): {tm.get('foo', 4)}")  # bar2
    print(f"get('foo', 5): {tm.get('foo', 5)}")  # bar2

