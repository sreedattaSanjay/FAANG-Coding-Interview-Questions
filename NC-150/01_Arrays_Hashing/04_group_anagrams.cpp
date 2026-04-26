/*
 * LeetCode 49: Group Anagrams
 * https://leetcode.com/problems/group-anagrams/
 * 
 * Given an array of strings strs, group the anagrams together. 
 * You can return the answer in any order.
 * 
 * An Anagram is a word formed by rearranging the letters of a different word,
 * using all the original letters exactly once.
 * 
 * Time Complexity: O(n * k log k) where n = number of strings, k = max string length
 * Space Complexity: O(n * k) - storing all strings in hash map
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Sorted String as Key
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& pair : groups) {
            result.push_back(move(pair.second));
        }
        
        return result;
    }
    
    // Solution 2: Character Count as Key
    // Time: O(n * k) - no sorting needed
    vector<vector<string>> groupAnagramsCount(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& s : strs) {
            // Create count key: "a2b1c3..." format
            int count[26] = {0};
            for (char c : s) {
                count[c - 'a']++;
            }
            
            string key = "";
            for (int i = 0; i < 26; i++) {
                if (count[i] > 0) {
                    key += ('a' + i);
                    key += to_string(count[i]);
                }
            }
            
            groups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& pair : groups) {
            result.push_back(move(pair.second));
        }
        
        return result;
    }
};

void printResult(vector<vector<string>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result1 = sol.groupAnagrams(strs1);
    cout << "Test 1: ";
    printResult(result1);
    // Expected: [["bat"],["nat","tan"],["ate","eat","tea"]] (any order)
    
    // Test Case 2: Empty string
    vector<string> strs2 = {""};
    auto result2 = sol.groupAnagrams(strs2);
    cout << "Test 2: ";
    printResult(result2);
    // Expected: [[""]]
    
    // Test Case 3: Single character
    vector<string> strs3 = {"a"};
    auto result3 = sol.groupAnagrams(strs3);
    cout << "Test 3: ";
    printResult(result3);
    // Expected: [["a"]]
    
    // Test Case 4: No anagrams
    vector<string> strs4 = {"abc", "def", "ghi"};
    auto result4 = sol.groupAnagrams(strs4);
    cout << "Test 4: ";
    printResult(result4);
    // Expected: [["abc"],["def"],["ghi"]]
    
    // Test Case 5: All same anagram
    vector<string> strs5 = {"abc", "bca", "cab"};
    auto result5 = sol.groupAnagrams(strs5);
    cout << "Test 5: ";
    printResult(result5);
    // Expected: [["abc","bca","cab"]]
    
    return 0;
}

