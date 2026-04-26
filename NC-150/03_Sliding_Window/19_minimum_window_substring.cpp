/*
 * LeetCode 76: Minimum Window Substring
 * https://leetcode.com/problems/minimum-window-substring/
 * 
 * Given two strings s and t, return the minimum window substring of s such that 
 * every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 * 
 * Time Complexity: O(m + n) where m = len(s), n = len(t)
 * Space Complexity: O(m + n) for hashmaps
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    // Solution 1: Sliding Window with Two Maps
    string minWindow(string s, string t) {
        if (t.empty() || s.length() < t.length()) return "";
        
        unordered_map<char, int> need, have;
        for (char c : t) need[c]++;
        
        int required = need.size();  // Unique chars needed
        int formed = 0;              // Unique chars satisfied
        int left = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            have[c]++;
            
            // Check if current char satisfies requirement
            if (need.count(c) && have[c] == need[c]) {
                formed++;
            }
            
            // Try to contract window while valid
            while (formed == required) {
                // Update result
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }
                
                // Remove left char
                char leftChar = s[left];
                have[leftChar]--;
                if (need.count(leftChar) && have[leftChar] < need[leftChar]) {
                    formed--;
                }
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
    
    // Solution 2: Optimized with filtered s (only chars in t)
    string minWindowOptimized(string s, string t) {
        if (t.empty() || s.length() < t.length()) return "";
        
        unordered_map<char, int> need;
        for (char c : t) need[c]++;
        
        // Filter s to only include chars that are in t
        vector<pair<int, char>> filtered;
        for (int i = 0; i < s.length(); i++) {
            if (need.count(s[i])) {
                filtered.push_back({i, s[i]});
            }
        }
        
        int required = need.size();
        int formed = 0;
        unordered_map<char, int> have;
        int left = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        
        for (int right = 0; right < filtered.size(); right++) {
            char c = filtered[right].second;
            have[c]++;
            
            if (have[c] == need[c]) {
                formed++;
            }
            
            while (formed == required) {
                int start = filtered[left].first;
                int end = filtered[right].first;
                
                if (end - start + 1 < minLen) {
                    minLen = end - start + 1;
                    minStart = start;
                }
                
                char leftChar = filtered[left].second;
                have[leftChar]--;
                if (have[leftChar] < need[leftChar]) {
                    formed--;
                }
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    cout << "Test 1 s='ADOBECODEBANC' t='ABC': '" 
         << sol.minWindow("ADOBECODEBANC", "ABC") << "'" << endl;
    // Expected: "BANC"
    
    // Test Case 2: s equals t
    cout << "Test 2 s='a' t='a': '" << sol.minWindow("a", "a") << "'" << endl;
    // Expected: "a"
    
    // Test Case 3: No valid window
    cout << "Test 3 s='a' t='aa': '" << sol.minWindow("a", "aa") << "'" << endl;
    // Expected: ""
    
    // Test Case 4: t longer than s
    cout << "Test 4 s='ab' t='abc': '" << sol.minWindow("ab", "abc") << "'" << endl;
    // Expected: ""
    
    // Test Case 5: Multiple valid windows
    cout << "Test 5 s='cabwefgewcwaefgcf' t='cae': '" 
         << sol.minWindow("cabwefgewcwaefgcf", "cae") << "'" << endl;
    // Expected: "cwae" (or other minimum)
    
    // Test Case 6: Repeated characters in t
    cout << "Test 6 s='aa' t='aa': '" << sol.minWindow("aa", "aa") << "'" << endl;
    // Expected: "aa"
    
    return 0;
}

