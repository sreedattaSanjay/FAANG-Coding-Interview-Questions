/*
 * LeetCode 424: Longest Repeating Character Replacement
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * 
 * Given a string s and an integer k, you can choose any character and change it 
 * to any other uppercase English character. You can perform this operation at most k times.
 * 
 * Return the length of the longest substring containing the same letter you can get.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(26) = O(1)
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Sliding Window with Max Frequency
    int characterReplacement(string s, int k) {
        int count[26] = {0};
        int left = 0;
        int maxFreq = 0;  // Max frequency of any char in current window
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right] - 'A']++;
            maxFreq = max(maxFreq, count[s[right] - 'A']);
            
            // Window size - maxFreq = characters to replace
            // If > k, we need to shrink window
            int windowSize = right - left + 1;
            if (windowSize - maxFreq > k) {
                count[s[left] - 'A']--;
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
    // Solution 2: Sliding Window (recalculate max each time)
    // Slightly slower but easier to understand
    int characterReplacementSimple(string s, int k) {
        int count[26] = {0};
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right] - 'A']++;
            
            // Find max frequency in current window
            int maxFreq = 0;
            for (int i = 0; i < 26; i++) {
                maxFreq = max(maxFreq, count[i]);
            }
            
            // Shrink window while invalid
            while (right - left + 1 - maxFreq > k) {
                count[s[left] - 'A']--;
                left++;
                
                // Recalculate max
                maxFreq = 0;
                for (int i = 0; i < 26; i++) {
                    maxFreq = max(maxFreq, count[i]);
                }
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    cout << "Test 1 'ABAB' k=2: " << sol.characterReplacement("ABAB", 2) << endl;
    // Expected: 4 (Replace both A's with B's or vice versa)
    
    // Test Case 2: Another case
    cout << "Test 2 'AABABBA' k=1: " << sol.characterReplacement("AABABBA", 1) << endl;
    // Expected: 4 (Replace middle B with A to get "AAAA")
    
    // Test Case 3: k = 0
    cout << "Test 3 'AAAA' k=0: " << sol.characterReplacement("AAAA", 0) << endl;
    // Expected: 4 (All same, no replacement needed)
    
    // Test Case 4: k >= length
    cout << "Test 4 'ABCD' k=4: " << sol.characterReplacement("ABCD", 4) << endl;
    // Expected: 4 (Can change all to same)
    
    // Test Case 5: Single character
    cout << "Test 5 'A' k=1: " << sol.characterReplacement("A", 1) << endl;
    // Expected: 1
    
    // Test Case 6: Alternating
    cout << "Test 6 'ABABAB' k=2: " << sol.characterReplacement("ABABAB", 2) << endl;
    // Expected: 5
    
    // Test Case 7: Long string
    cout << "Test 7 'AABCABBB' k=2: " << sol.characterReplacement("AABCABBB", 2) << endl;
    // Expected: 6
    
    return 0;
}

