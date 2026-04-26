/*
 * LeetCode 125: Valid Palindrome
 * https://leetcode.com/problems/valid-palindrome/
 * 
 * A phrase is a palindrome if, after converting all uppercase letters to lowercase 
 * and removing all non-alphanumeric characters, it reads the same forward and backward.
 * 
 * Given a string s, return true if it is a palindrome, or false otherwise.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    // Solution 1: Two Pointers (Optimal)
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            
            // Skip non-alphanumeric from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare characters (case-insensitive)
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
    
    // Solution 2: Build cleaned string and compare
    // Space: O(n)
    bool isPalindromeClean(string s) {
        string cleaned = "";
        for (char c : s) {
            if (isalnum(c)) {
                cleaned += tolower(c);
            }
        }
        
        int left = 0, right = cleaned.length() - 1;
        while (left < right) {
            if (cleaned[left] != cleaned[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
    
    // Solution 3: Reverse and compare
    // Space: O(n)
    bool isPalindromeReverse(string s) {
        string cleaned = "";
        for (char c : s) {
            if (isalnum(c)) {
                cleaned += tolower(c);
            }
        }
        
        string reversed = cleaned;
        reverse(reversed.begin(), reversed.end());
        
        return cleaned == reversed;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Valid palindrome with spaces and punctuation
    cout << "Test 1 'A man, a plan, a canal: Panama': " 
         << (sol.isPalindrome("A man, a plan, a canal: Panama") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2: Not a palindrome
    cout << "Test 2 'race a car': " 
         << (sol.isPalindrome("race a car") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3: Empty string (after removing non-alphanumeric)
    cout << "Test 3 ' ': " 
         << (sol.isPalindrome(" ") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4: Single character
    cout << "Test 4 'a': " 
         << (sol.isPalindrome("a") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 5: Only non-alphanumeric
    cout << "Test 5 '.,': " 
         << (sol.isPalindrome(".,") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 6: Numbers
    cout << "Test 6 '12321': " 
         << (sol.isPalindrome("12321") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 7: Mixed case
    cout << "Test 7 'Aa': " 
         << (sol.isPalindrome("Aa") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 8: Alphanumeric mix
    cout << "Test 8 '0P': " 
         << (sol.isPalindrome("0P") ? "true" : "false") << endl;
    // Expected: false
    
    return 0;
}

