/*
 * LeetCode 217: Contains Duplicate
 * https://leetcode.com/problems/contains-duplicate/
 * 
 * Given an integer array nums, return true if any value appears at least 
 * twice in the array, and return false if every element is distinct.
 * 
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(n) - hash set storage
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Hash Set (Optimal)
    // Insert elements into set, if already exists return true
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
    
    // Solution 2: Sorting
    // Sort array, duplicates will be adjacent
    // Time: O(n log n), Space: O(1) or O(n) depending on sort
    bool containsDuplicateSorting(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        return false;
    }
    
    // Solution 3: Hash Set with size comparison
    // If set size < array size, there are duplicates
    bool containsDuplicateSetSize(vector<int>& nums) {
        unordered_set<int> unique(nums.begin(), nums.end());
        return unique.size() < nums.size();
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Has duplicates
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Test 1 [1,2,3,1]: " << (sol.containsDuplicate(nums1) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2: No duplicates
    vector<int> nums2 = {1, 2, 3, 4};
    cout << "Test 2 [1,2,3,4]: " << (sol.containsDuplicate(nums2) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3: Multiple duplicates
    vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "Test 3 [1,1,1,3,3,4,3,2,4,2]: " << (sol.containsDuplicate(nums3) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4: Empty array
    vector<int> nums4 = {};
    cout << "Test 4 []: " << (sol.containsDuplicate(nums4) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 5: Single element
    vector<int> nums5 = {1};
    cout << "Test 5 [1]: " << (sol.containsDuplicate(nums5) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 6: Two same elements
    vector<int> nums6 = {1, 1};
    cout << "Test 6 [1,1]: " << (sol.containsDuplicate(nums6) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 7: Negative numbers
    vector<int> nums7 = {-1, -2, -3, -1};
    cout << "Test 7 [-1,-2,-3,-1]: " << (sol.containsDuplicate(nums7) ? "true" : "false") << endl;
    // Expected: true
    
    return 0;
}

