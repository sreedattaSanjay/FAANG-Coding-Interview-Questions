"""
LeetCode 22: Generate Parentheses
https://leetcode.com/problems/generate-parentheses/

Given n pairs of parentheses, write a function to generate all combinations 
of well-formed parentheses.

Time Complexity: O(4^n / sqrt(n)) - nth Catalan number
Space Complexity: O(n) for recursion stack
"""

from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        result = []
        
        def backtrack(current: str, open_count: int, close_count: int):
            if len(current) == 2 * n:
                result.append(current)
                return
            
            # Can add '(' if we haven't used all n
            if open_count < n:
                backtrack(current + "(", open_count + 1, close_count)
            
            # Can add ')' only if there are unmatched '('
            if close_count < open_count:
                backtrack(current + ")", open_count, close_count + 1)
        
        backtrack("", 0, 0)
        return result
    
    # Solution 2: Using list instead of string concatenation (more efficient)
    def generateParenthesisOptimized(self, n: int) -> List[str]:
        result = []
        
        def backtrack(current: List[str], open_count: int, close_count: int):
            if len(current) == 2 * n:
                result.append("".join(current))
                return
            
            if open_count < n:
                current.append("(")
                backtrack(current, open_count + 1, close_count)
                current.pop()
            
            if close_count < open_count:
                current.append(")")
                backtrack(current, open_count, close_count + 1)
                current.pop()
        
        backtrack([], 0, 0)
        return result


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: n = 3
    print(f"Test 1 n=3: {sol.generateParenthesis(3)}")
    # Expected: ["((()))","(()())","(())()","()(())","()()()"]
    
    # Test Case 2: n = 1
    print(f"Test 2 n=1: {sol.generateParenthesis(1)}")
    # Expected: ["()"]
    
    # Test Case 3: n = 2
    print(f"Test 3 n=2: {sol.generateParenthesis(2)}")
    # Expected: ["(())","()()"]
    
    # Test Case 4: n = 4
    result4 = sol.generateParenthesis(4)
    print(f"Test 4 n=4 (count={len(result4)})")
    # Expected: 14 combinations

