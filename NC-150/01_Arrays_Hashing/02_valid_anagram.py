"""
LeetCode 242: Valid Anagram
https://leetcode.com/problems/valid-anagram/

Given two strings s and t, return true if t is an anagram of s, 
and false otherwise.

An Anagram is a word formed by rearranging the letters of a different word,
using all the original letters exactly once.

Time Complexity: O(n) - single pass through both strings
Space Complexity: O(1) - fixed size (26 letters) or O(k) for k unique chars
"""

from collections import Counter


class Solution:
    # Solution 1: Counter comparison (Pythonic)
    def isAnagram(self, s: str, t: str) -> bool:
        return Counter(s) == Counter(t)
    
    # Solution 2: Manual counting with dictionary
    def isAnagramDict(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        count = {}
        
        for c in s:
            count[c] = count.get(c, 0) + 1
        
        for c in t:
            if c not in count:
                return False
            count[c] -= 1
            if count[c] < 0:
                return False
        
        return True
    
    # Solution 3: Array counting (for lowercase only)
    def isAnagramArray(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        count = [0] * 26
        
        for i in range(len(s)):
            count[ord(s[i]) - ord('a')] += 1
            count[ord(t[i]) - ord('a')] -= 1
        
        return all(c == 0 for c in count)
    
    # Solution 4: Sorting
    def isAnagramSorting(self, s: str, t: str) -> bool:
        return sorted(s) == sorted(t)


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Valid anagram
    print(f"Test 1 'anagram','nagaram': {sol.isAnagram('anagram', 'nagaram')}")
    # Expected: True
    
    # Test Case 2: Not anagram
    print(f"Test 2 'rat','car': {sol.isAnagram('rat', 'car')}")
    # Expected: False
    
    # Test Case 3: Empty strings
    print(f"Test 3 '','': {sol.isAnagram('', '')}")
    # Expected: True
    
    # Test Case 4: Single character same
    print(f"Test 4 'a','a': {sol.isAnagram('a', 'a')}")
    # Expected: True
    
    # Test Case 5: Single character different
    print(f"Test 5 'a','b': {sol.isAnagram('a', 'b')}")
    # Expected: False
    
    # Test Case 6: Different lengths
    print(f"Test 6 'ab','a': {sol.isAnagram('ab', 'a')}")
    # Expected: False
    
    # Test Case 7: Same letters different frequency
    print(f"Test 7 'aacc','ccac': {sol.isAnagram('aacc', 'ccac')}")
    # Expected: False

