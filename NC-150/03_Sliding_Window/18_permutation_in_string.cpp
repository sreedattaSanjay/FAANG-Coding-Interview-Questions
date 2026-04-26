/*
 * LeetCode 567: Permutation in String
 * https://leetcode.com/problems/permutation-in-string/
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * 
 * Time Complexity: O(n) where n = length of s2
 * Space Complexity: O(1) - fixed array of size 26
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // Solution 1: Fixed-size sliding window with frequency match
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        int count1[26] = {0}, count2[26] = {0};
        int k = s1.length();
        
        // Initialize counts for first window
        for (int i = 0; i < k; i++) {
            count1[s1[i] - 'a']++;
            count2[s2[i] - 'a']++;
        }
        
        if (equal(begin(count1), end(count1), begin(count2))) return true;
        
        // Slide window
        for (int i = k; i < s2.length(); i++) {
            count2[s2[i] - 'a']++;           // Add new char
            count2[s2[i - k] - 'a']--;       // Remove old char
            
            if (equal(begin(count1), end(count1), begin(count2))) return true;
        }
        
        return false;
    }
    
    // Solution 2: Track matches count (optimized comparison)
    bool checkInclusionOptimized(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        int count[26] = {0};
        int k = s1.length();
        int matches = 0;
        
        // Initialize: count difference (need - have)
        for (int i = 0; i < k; i++) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        
        // Count how many characters match perfectly
        for (int i = 0; i < 26; i++) {
            if (count[i] == 0) matches++;
        }
        
        if (matches == 26) return true;
        
        // Slide window
        for (int i = k; i < s2.length(); i++) {
            int idx = s2[i] - 'a';
            // Add new char
            if (count[idx] == 0) matches--;
            count[idx]--;
            if (count[idx] == 0) matches++;
            
            int oldIdx = s2[i - k] - 'a';
            // Remove old char
            if (count[oldIdx] == 0) matches--;
            count[oldIdx]++;
            if (count[oldIdx] == 0) matches++;
            
            if (matches == 26) return true;
        }
        
        return false;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Permutation exists
    cout << "Test 1 s1='ab' s2='eidbaooo': " 
         << (sol.checkInclusion("ab", "eidbaooo") ? "true" : "false") << endl;
    // Expected: true ("ba" is permutation of "ab")
    
    // Test Case 2: No permutation
    cout << "Test 2 s1='ab' s2='eidboaoo': " 
         << (sol.checkInclusion("ab", "eidboaoo") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3: s1 longer than s2
    cout << "Test 3 s1='abc' s2='ab': " 
         << (sol.checkInclusion("abc", "ab") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 4: Exact match
    cout << "Test 4 s1='ab' s2='ab': " 
         << (sol.checkInclusion("ab", "ab") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 5: Single character
    cout << "Test 5 s1='a' s2='ab': " 
         << (sol.checkInclusion("a", "ab") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 6: At the end
    cout << "Test 6 s1='ab' s2='xxab': " 
         << (sol.checkInclusion("ab", "xxab") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 7: Repeated characters
    cout << "Test 7 s1='aab' s2='cbdaaabo': " 
         << (sol.checkInclusion("aab", "cbdaaabo") ? "true" : "false") << endl;
    // Expected: true
    
    return 0;
}

