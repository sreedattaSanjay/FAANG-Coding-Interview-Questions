"""
LeetCode 155: Min Stack
https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum 
element in constant time.

Time Complexity: O(1) for all operations
Space Complexity: O(n)
"""


# Solution 1: Two stacks
class MinStack:
    def __init__(self):
        self.stack = []
        self.min_stack = []

    def push(self, val: int) -> None:
        self.stack.append(val)
        if not self.min_stack or val <= self.min_stack[-1]:
            self.min_stack.append(val)

    def pop(self) -> None:
        if self.stack[-1] == self.min_stack[-1]:
            self.min_stack.pop()
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.min_stack[-1]


# Solution 2: Single stack with tuples
class MinStackTuples:
    def __init__(self):
        self.stack = []  # (value, current_min)

    def push(self, val: int) -> None:
        if not self.stack:
            self.stack.append((val, val))
        else:
            current_min = min(val, self.stack[-1][1])
            self.stack.append((val, current_min))

    def pop(self) -> None:
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1][0]

    def getMin(self) -> int:
        return self.stack[-1][1]


if __name__ == "__main__":
    # Test MinStack
    minStack = MinStack()
    
    minStack.push(-2)
    minStack.push(0)
    minStack.push(-3)
    print(f"getMin(): {minStack.getMin()}")  # Expected: -3
    minStack.pop()
    print(f"top(): {minStack.top()}")        # Expected: 0
    print(f"getMin(): {minStack.getMin()}")  # Expected: -2
    
    print("\n--- Testing MinStackTuples ---")
    
    # Test MinStackTuples
    minStack2 = MinStackTuples()
    
    minStack2.push(-2)
    minStack2.push(0)
    minStack2.push(-3)
    print(f"getMin(): {minStack2.getMin()}")  # Expected: -3
    minStack2.pop()
    print(f"top(): {minStack2.top()}")        # Expected: 0
    print(f"getMin(): {minStack2.getMin()}")  # Expected: -2

