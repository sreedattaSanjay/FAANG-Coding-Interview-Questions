"""
LeetCode 424: Longest Repeating Character Replacement
https://leetcode.com/problems/longest-repeating-character-replacement/

Given a string s and an integer k, you can choose any character and change it 
to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get.

Time Complexity: O(n)
Space Complexity: O(26) = O(1)
"""

from collections import defaultdict


class Solution:
    # Solution 1: Sliding Window with Max Frequency
    def characterReplacement(self, s: str, k: int) -> int:
        count = defaultdict(int)
        left = 0
        max_freq = 0
        max_len = 0
        
        for right in range(len(s)):
            count[s[right]] += 1
            max_freq = max(max_freq, count[s[right]])
            
            # Window size - maxFreq = characters to replace
            window_size = right - left + 1
            if window_size - max_freq > k:
                count[s[left]] -= 1
                left += 1
            
            max_len = max(max_len, right - left + 1)
        
        return max_len
    
    # Solution 2: With explicit while loop for shrinking
    def characterReplacementExplicit(self, s: str, k: int) -> int:
        count = defaultdict(int)
        left = 0
        max_len = 0
        
        for right in range(len(s)):
            count[s[right]] += 1
            
            # Calculate max frequency in current window
            max_freq = max(count.values()) if count else 0
            
            # Shrink window while invalid
            while right - left + 1 - max_freq > k:
                count[s[left]] -= 1
                left += 1
                max_freq = max(count.values()) if count else 0
            
            max_len = max(max_len, right - left + 1)
        
        return max_len


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    print(f"Test 1 'ABAB' k=2: {sol.characterReplacement('ABAB', 2)}")
    # Expected: 4
    
    # Test Case 2: Another case
    print(f"Test 2 'AABABBA' k=1: {sol.characterReplacement('AABABBA', 1)}")
    # Expected: 4
    
    # Test Case 3: k = 0
    print(f"Test 3 'AAAA' k=0: {sol.characterReplacement('AAAA', 0)}")
    # Expected: 4
    
    # Test Case 4: k >= length
    print(f"Test 4 'ABCD' k=4: {sol.characterReplacement('ABCD', 4)}")
    # Expected: 4
    
    # Test Case 5: Single character
    print(f"Test 5 'A' k=1: {sol.characterReplacement('A', 1)}")
    # Expected: 1
    
    # Test Case 6: Alternating
    print(f"Test 6 'ABABAB' k=2: {sol.characterReplacement('ABABAB', 2)}")
    # Expected: 5
    
    # Test Case 7: Long string
    print(f"Test 7 'AABCABBB' k=2: {sol.characterReplacement('AABCABBB', 2)}")
    # Expected: 6

