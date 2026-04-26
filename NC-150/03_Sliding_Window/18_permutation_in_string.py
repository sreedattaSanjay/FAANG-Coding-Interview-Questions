"""
LeetCode 567: Permutation in String
https://leetcode.com/problems/permutation-in-string/

Given two strings s1 and s2, return true if s2 contains a permutation of s1.
In other words, return true if one of s1's permutations is the substring of s2.

Time Complexity: O(n) where n = length of s2
Space Complexity: O(1) - fixed array of size 26
"""

from collections import Counter


class Solution:
    # Solution 1: Counter comparison with sliding window
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        k = len(s1)
        count1 = Counter(s1)
        count2 = Counter(s2[:k])
        
        if count1 == count2:
            return True
        
        # Slide window
        for i in range(k, len(s2)):
            count2[s2[i]] += 1
            count2[s2[i - k]] -= 1
            
            if count2[s2[i - k]] == 0:
                del count2[s2[i - k]]
            
            if count1 == count2:
                return True
        
        return False
    
    # Solution 2: Track matches count (optimized)
    def checkInclusionOptimized(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        k = len(s1)
        count = [0] * 26
        
        # Initialize: count difference
        for i in range(k):
            count[ord(s1[i]) - ord('a')] += 1
            count[ord(s2[i]) - ord('a')] -= 1
        
        matches = sum(1 for c in count if c == 0)
        
        if matches == 26:
            return True
        
        # Slide window
        for i in range(k, len(s2)):
            idx = ord(s2[i]) - ord('a')
            old_idx = ord(s2[i - k]) - ord('a')
            
            # Add new char
            if count[idx] == 0:
                matches -= 1
            count[idx] -= 1
            if count[idx] == 0:
                matches += 1
            
            # Remove old char
            if count[old_idx] == 0:
                matches -= 1
            count[old_idx] += 1
            if count[old_idx] == 0:
                matches += 1
            
            if matches == 26:
                return True
        
        return False


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Permutation exists
    print(f"Test 1 s1='ab' s2='eidbaooo': {sol.checkInclusion('ab', 'eidbaooo')}")
    # Expected: True
    
    # Test Case 2: No permutation
    print(f"Test 2 s1='ab' s2='eidboaoo': {sol.checkInclusion('ab', 'eidboaoo')}")
    # Expected: False
    
    # Test Case 3: s1 longer than s2
    print(f"Test 3 s1='abc' s2='ab': {sol.checkInclusion('abc', 'ab')}")
    # Expected: False
    
    # Test Case 4: Exact match
    print(f"Test 4 s1='ab' s2='ab': {sol.checkInclusion('ab', 'ab')}")
    # Expected: True
    
    # Test Case 5: Single character
    print(f"Test 5 s1='a' s2='ab': {sol.checkInclusion('a', 'ab')}")
    # Expected: True
    
    # Test Case 6: At the end
    print(f"Test 6 s1='ab' s2='xxab': {sol.checkInclusion('ab', 'xxab')}")
    # Expected: True
    
    # Test Case 7: Repeated characters
    print(f"Test 7 s1='aab' s2='cbdaaabo': {sol.checkInclusion('aab', 'cbdaaabo')}")
    # Expected: True

