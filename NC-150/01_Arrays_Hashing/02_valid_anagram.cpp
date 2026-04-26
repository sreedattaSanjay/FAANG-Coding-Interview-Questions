/*
 * LeetCode 242: Valid Anagram
 * https://leetcode.com/problems/valid-anagram/
 * 
 * Given two strings s and t, return true if t is an anagram of s, 
 * and false otherwise.
 * 
 * An Anagram is a word formed by rearranging the letters of a different word,
 * using all the original letters exactly once.
 * 
 * Time Complexity: O(n) - single pass through both strings
 * Space Complexity: O(1) - fixed size array (26 letters)
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Character Count Array (Optimal for lowercase letters)
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        int count[26] = {0};
        
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) return false;
        }
        
        return true;
    }
    
    // Solution 2: Hash Map (Works for Unicode)
    bool isAnagramHashMap(string s, string t) {
        if (s.length() != t.length()) return false;
        
        unordered_map<char, int> count;
        
        for (char c : s) {
            count[c]++;
        }
        
        for (char c : t) {
            count[c]--;
            if (count[c] < 0) return false;
        }
        
        return true;
    }
    
    // Solution 3: Sorting
    // Time: O(n log n), Space: O(n) for sorted copies
    bool isAnagramSorting(string s, string t) {
        if (s.length() != t.length()) return false;
        
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        
        return s == t;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Valid anagram
    cout << "Test 1 'anagram','nagaram': " 
         << (sol.isAnagram("anagram", "nagaram") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2: Not anagram
    cout << "Test 2 'rat','car': " 
         << (sol.isAnagram("rat", "car") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3: Empty strings
    cout << "Test 3 '','': " 
         << (sol.isAnagram("", "") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4: Single character same
    cout << "Test 4 'a','a': " 
         << (sol.isAnagram("a", "a") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 5: Single character different
    cout << "Test 5 'a','b': " 
         << (sol.isAnagram("a", "b") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 6: Different lengths
    cout << "Test 6 'ab','a': " 
         << (sol.isAnagram("ab", "a") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 7: Same letters different frequency
    cout << "Test 7 'aacc','ccac': " 
         << (sol.isAnagram("aacc", "ccac") ? "true" : "false") << endl;
    // Expected: false
    
    return 0;
}

