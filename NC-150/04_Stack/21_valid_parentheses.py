"""
LeetCode 20: Valid Parentheses
https://leetcode.com/problems/valid-parentheses/

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

Time Complexity: O(n)
Space Complexity: O(n)
"""


class Solution:
    # Solution 1: Stack with Dictionary
    def isValid(self, s: str) -> bool:
        stack = []
        pairs = {
            ')': '(',
            '}': '{',
            ']': '['
        }
        
        for c in s:
            if c in pairs:
                # It's a closing bracket
                if not stack or stack[-1] != pairs[c]:
                    return False
                stack.pop()
            else:
                # It's an opening bracket
                stack.append(c)
        
        return len(stack) == 0
    
    # Solution 2: Using replace (clever but less efficient)
    def isValidReplace(self, s: str) -> bool:
        while '()' in s or '{}' in s or '[]' in s:
            s = s.replace('()', '').replace('{}', '').replace('[]', '')
        return s == ''


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Simple valid
    print(f"Test 1 '()': {sol.isValid('()')}")
    # Expected: True
    
    # Test Case 2: Multiple types
    print(f"Test 2 '()[]{{}}': {sol.isValid('()[]{}')}")
    # Expected: True
    
    # Test Case 3: Nested
    print(f"Test 3 '{{[]}}': {sol.isValid('{[]}')}")
    # Expected: True
    
    # Test Case 4: Mismatch
    print(f"Test 4 '(]': {sol.isValid('(]')}")
    # Expected: False
    
    # Test Case 5: Wrong order
    print(f"Test 5 '([)]': {sol.isValid('([)]')}")
    # Expected: False
    
    # Test Case 6: Only opening
    print(f"Test 6 '(': {sol.isValid('(')}")
    # Expected: False
    
    # Test Case 7: Only closing
    print(f"Test 7 ')': {sol.isValid(')')}")
    # Expected: False
    
    # Test Case 8: Empty string
    print(f"Test 8 '': {sol.isValid('')}")
    # Expected: True
    
    # Test Case 9: Complex nested
    print(f"Test 9 '(({{[[]]}}))': {sol.isValid('(({{[[]]}}))')}")
    # Expected: True

