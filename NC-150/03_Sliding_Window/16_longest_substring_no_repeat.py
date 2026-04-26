"""
LeetCode 3: Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/

Given a string s, find the length of the longest substring without repeating characters.

Time Complexity: O(n)
Space Complexity: O(min(m, n)) where m is charset size
"""


class Solution:
    # Solution 1: Sliding Window with Set
    def lengthOfLongestSubstring(self, s: str) -> int:
        chars = set()
        left = 0
        max_len = 0
        
        for right in range(len(s)):
            # Shrink window until no duplicate
            while s[right] in chars:
                chars.remove(s[left])
                left += 1
            
            chars.add(s[right])
            max_len = max(max_len, right - left + 1)
        
        return max_len
    
    # Solution 2: Sliding Window with HashMap (optimized)
    def lengthOfLongestSubstringOptimized(self, s: str) -> int:
        last_index = {}
        left = 0
        max_len = 0
        
        for right in range(len(s)):
            if s[right] in last_index and last_index[s[right]] >= left:
                left = last_index[s[right]] + 1
            
            last_index[s[right]] = right
            max_len = max(max_len, right - left + 1)
        
        return max_len
    
    # Solution 3: Pythonic with enumerate
    def lengthOfLongestSubstringPythonic(self, s: str) -> int:
        last_seen = {}
        start = 0
        max_len = 0
        
        for i, char in enumerate(s):
            if char in last_seen and last_seen[char] >= start:
                start = last_seen[char] + 1
            else:
                max_len = max(max_len, i - start + 1)
            
            last_seen[char] = i
        
        return max_len


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    print(f"Test 1 'abcabcbb': {sol.lengthOfLongestSubstring('abcabcbb')}")
    # Expected: 3 ("abc")
    
    # Test Case 2: All same characters
    print(f"Test 2 'bbbbb': {sol.lengthOfLongestSubstring('bbbbb')}")
    # Expected: 1 ("b")
    
    # Test Case 3: All unique
    print(f"Test 3 'pwwkew': {sol.lengthOfLongestSubstring('pwwkew')}")
    # Expected: 3 ("wke")
    
    # Test Case 4: Empty string
    print(f"Test 4 '': {sol.lengthOfLongestSubstring('')}")
    # Expected: 0
    
    # Test Case 5: Single character
    print(f"Test 5 'a': {sol.lengthOfLongestSubstring('a')}")
    # Expected: 1
    
    # Test Case 6: Two different characters
    print(f"Test 6 'au': {sol.lengthOfLongestSubstring('au')}")
    # Expected: 2
    
    # Test Case 7: Space in string
    print(f"Test 7 'a b c': {sol.lengthOfLongestSubstring('a b c')}")
    # Expected: 3
    
    # Test Case 8: Repeating pattern
    print(f"Test 8 'abba': {sol.lengthOfLongestSubstring('abba')}")
    # Expected: 2

