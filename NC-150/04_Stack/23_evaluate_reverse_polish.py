"""
LeetCode 150: Evaluate Reverse Polish Notation
https://leetcode.com/problems/evaluate-reverse-polish-notation/

Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, /. Each operand may be an integer or another expression.
Division truncates toward zero.

Time Complexity: O(n)
Space Complexity: O(n)
"""

from typing import List


class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        operators = {'+', '-', '*', '/'}
        
        for token in tokens:
            if token in operators:
                b = stack.pop()
                a = stack.pop()
                
                if token == '+':
                    result = a + b
                elif token == '-':
                    result = a - b
                elif token == '*':
                    result = a * b
                else:
                    # Division truncates toward zero
                    result = int(a / b)
                
                stack.append(result)
            else:
                stack.append(int(token))
        
        return stack[0]
    
    # Solution 2: Using lambda functions
    def evalRPNLambda(self, tokens: List[str]) -> int:
        stack = []
        operations = {
            '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '/': lambda a, b: int(a / b)
        }
        
        for token in tokens:
            if token in operations:
                b, a = stack.pop(), stack.pop()
                stack.append(operations[token](a, b))
            else:
                stack.append(int(token))
        
        return stack[0]


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Simple addition
    tokens1 = ["2", "1", "+", "3", "*"]
    print(f"Test 1 ['2','1','+','3','*']: {sol.evalRPN(tokens1)}")
    # Expected: 9
    
    # Test Case 2: Division
    tokens2 = ["4", "13", "5", "/", "+"]
    print(f"Test 2 ['4','13','5','/','+]: {sol.evalRPN(tokens2)}")
    # Expected: 6
    
    # Test Case 3: Complex expression
    tokens3 = ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
    print(f"Test 3 [complex]: {sol.evalRPN(tokens3)}")
    # Expected: 22
    
    # Test Case 4: Negative numbers
    tokens4 = ["-2", "3", "*"]
    print(f"Test 4 ['-2','3','*']: {sol.evalRPN(tokens4)}")
    # Expected: -6
    
    # Test Case 5: Single number
    tokens5 = ["42"]
    print(f"Test 5 ['42']: {sol.evalRPN(tokens5)}")
    # Expected: 42
    
    # Test Case 6: Division truncation toward zero
    tokens6 = ["7", "-3", "/"]
    print(f"Test 6 ['7','-3','/']: {sol.evalRPN(tokens6)}")
    # Expected: -2 (not -3!)

