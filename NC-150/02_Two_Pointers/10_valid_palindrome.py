"""
LeetCode 125: Valid Palindrome
https://leetcode.com/problems/valid-palindrome/

A phrase is a palindrome if, after converting all uppercase letters to lowercase 
and removing all non-alphanumeric characters, it reads the same forward and backward.

Given a string s, return true if it is a palindrome, or false otherwise.

Time Complexity: O(n)
Space Complexity: O(1)
"""


class Solution:
    # Solution 1: Two Pointers (Optimal)
    def isPalindrome(self, s: str) -> bool:
        left, right = 0, len(s) - 1
        
        while left < right:
            # Skip non-alphanumeric from left
            while left < right and not s[left].isalnum():
                left += 1
            
            # Skip non-alphanumeric from right
            while left < right and not s[right].isalnum():
                right -= 1
            
            # Compare characters (case-insensitive)
            if s[left].lower() != s[right].lower():
                return False
            
            left += 1
            right -= 1
        
        return True
    
    # Solution 2: Pythonic one-liner
    def isPalindromePythonic(self, s: str) -> bool:
        cleaned = ''.join(c.lower() for c in s if c.isalnum())
        return cleaned == cleaned[::-1]
    
    # Solution 3: Build cleaned string and use two pointers
    def isPalindromeClean(self, s: str) -> bool:
        cleaned = [c.lower() for c in s if c.isalnum()]
        
        left, right = 0, len(cleaned) - 1
        while left < right:
            if cleaned[left] != cleaned[right]:
                return False
            left += 1
            right -= 1
        
        return True


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Valid palindrome with spaces and punctuation
    print(f"Test 1 'A man, a plan, a canal: Panama': {sol.isPalindrome('A man, a plan, a canal: Panama')}")
    # Expected: True
    
    # Test Case 2: Not a palindrome
    print(f"Test 2 'race a car': {sol.isPalindrome('race a car')}")
    # Expected: False
    
    # Test Case 3: Empty string (after removing non-alphanumeric)
    print(f"Test 3 ' ': {sol.isPalindrome(' ')}")
    # Expected: True
    
    # Test Case 4: Single character
    print(f"Test 4 'a': {sol.isPalindrome('a')}")
    # Expected: True
    
    # Test Case 5: Only non-alphanumeric
    print(f"Test 5 '.,': {sol.isPalindrome('.,')}")
    # Expected: True
    
    # Test Case 6: Numbers
    print(f"Test 6 '12321': {sol.isPalindrome('12321')}")
    # Expected: True
    
    # Test Case 7: Mixed case
    print(f"Test 7 'Aa': {sol.isPalindrome('Aa')}")
    # Expected: True
    
    # Test Case 8: Alphanumeric mix
    print(f"Test 8 '0P': {sol.isPalindrome('0P')}")
    # Expected: False

