"""
LeetCode 76: Minimum Window Substring
https://leetcode.com/problems/minimum-window-substring/

Given two strings s and t, return the minimum window substring of s such that 
every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

Time Complexity: O(m + n) where m = len(s), n = len(t)
Space Complexity: O(m + n) for hashmaps
"""

from collections import Counter, defaultdict


class Solution:
    # Solution 1: Sliding Window with Two Dicts
    def minWindow(self, s: str, t: str) -> str:
        if not t or len(s) < len(t):
            return ""
        
        need = Counter(t)
        have = defaultdict(int)
        
        required = len(need)  # Unique chars needed
        formed = 0            # Unique chars satisfied
        left = 0
        min_len = float('inf')
        min_start = 0
        
        for right in range(len(s)):
            c = s[right]
            have[c] += 1
            
            # Check if current char satisfies requirement
            if c in need and have[c] == need[c]:
                formed += 1
            
            # Try to contract window while valid
            while formed == required:
                # Update result
                if right - left + 1 < min_len:
                    min_len = right - left + 1
                    min_start = left
                
                # Remove left char
                left_char = s[left]
                have[left_char] -= 1
                if left_char in need and have[left_char] < need[left_char]:
                    formed -= 1
                left += 1
        
        return "" if min_len == float('inf') else s[min_start:min_start + min_len]
    
    # Solution 2: More Pythonic
    def minWindowPythonic(self, s: str, t: str) -> str:
        if not t or len(s) < len(t):
            return ""
        
        need = Counter(t)
        missing = len(t)  # Total chars still needed
        left = 0
        result = (float('inf'), 0, 0)  # (length, start, end)
        
        for right, char in enumerate(s):
            if need[char] > 0:
                missing -= 1
            need[char] -= 1
            
            # All chars found
            while missing == 0:
                if right - left + 1 < result[0]:
                    result = (right - left + 1, left, right + 1)
                
                # Remove left char
                need[s[left]] += 1
                if need[s[left]] > 0:
                    missing += 1
                left += 1
        
        return "" if result[0] == float('inf') else s[result[1]:result[2]]


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    print(f"Test 1 s='ADOBECODEBANC' t='ABC': '{sol.minWindow('ADOBECODEBANC', 'ABC')}'")
    # Expected: "BANC"
    
    # Test Case 2: s equals t
    print(f"Test 2 s='a' t='a': '{sol.minWindow('a', 'a')}'")
    # Expected: "a"
    
    # Test Case 3: No valid window
    print(f"Test 3 s='a' t='aa': '{sol.minWindow('a', 'aa')}'")
    # Expected: ""
    
    # Test Case 4: t longer than s
    print(f"Test 4 s='ab' t='abc': '{sol.minWindow('ab', 'abc')}'")
    # Expected: ""
    
    # Test Case 5: Multiple valid windows
    print(f"Test 5 s='cabwefgewcwaefgcf' t='cae': '{sol.minWindow('cabwefgewcwaefgcf', 'cae')}'")
    # Expected: "cwae"
    
    # Test Case 6: Repeated characters in t
    print(f"Test 6 s='aa' t='aa': '{sol.minWindow('aa', 'aa')}'")
    # Expected: "aa"

