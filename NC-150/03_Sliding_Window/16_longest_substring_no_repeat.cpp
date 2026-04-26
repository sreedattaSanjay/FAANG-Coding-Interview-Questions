/*
 * LeetCode 3: Longest Substring Without Repeating Characters
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * 
 * Given a string s, find the length of the longest substring without repeating characters.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(min(m, n)) where m is charset size
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Sliding Window with Set
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> chars;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Shrink window until no duplicate
            while (chars.count(s[right])) {
                chars.erase(s[left]);
                left++;
            }
            
            chars.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
    // Solution 2: Sliding Window with HashMap (optimized)
    // Jump left pointer directly to avoid incremental moves
    int lengthOfLongestSubstringOptimized(string s) {
        unordered_map<char, int> lastIndex;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (lastIndex.count(s[right]) && lastIndex[s[right]] >= left) {
                left = lastIndex[s[right]] + 1;
            }
            
            lastIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
    // Solution 3: Array instead of HashMap (for ASCII)
    int lengthOfLongestSubstringArray(string s) {
        int lastIndex[128];
        fill(lastIndex, lastIndex + 128, -1);
        
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (lastIndex[s[right]] >= left) {
                left = lastIndex[s[right]] + 1;
            }
            
            lastIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    cout << "Test 1 'abcabcbb': " << sol.lengthOfLongestSubstring("abcabcbb") << endl;
    // Expected: 3 ("abc")
    
    // Test Case 2: All same characters
    cout << "Test 2 'bbbbb': " << sol.lengthOfLongestSubstring("bbbbb") << endl;
    // Expected: 1 ("b")
    
    // Test Case 3: All unique
    cout << "Test 3 'pwwkew': " << sol.lengthOfLongestSubstring("pwwkew") << endl;
    // Expected: 3 ("wke")
    
    // Test Case 4: Empty string
    cout << "Test 4 '': " << sol.lengthOfLongestSubstring("") << endl;
    // Expected: 0
    
    // Test Case 5: Single character
    cout << "Test 5 'a': " << sol.lengthOfLongestSubstring("a") << endl;
    // Expected: 1
    
    // Test Case 6: Two different characters
    cout << "Test 6 'au': " << sol.lengthOfLongestSubstring("au") << endl;
    // Expected: 2
    
    // Test Case 7: Space in string
    cout << "Test 7 'a b c': " << sol.lengthOfLongestSubstring("a b c") << endl;
    // Expected: 3 ("a b" or " bc")
    
    // Test Case 8: Repeating pattern
    cout << "Test 8 'abba': " << sol.lengthOfLongestSubstring("abba") << endl;
    // Expected: 2 ("ab" or "ba")
    
    return 0;
}

