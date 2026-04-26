/*
 * LeetCode 128: Longest Consecutive Sequence
 * https://leetcode.com/problems/longest-consecutive-sequence/
 * 
 * Given an unsorted array of integers nums, return the length of the 
 * longest consecutive elements sequence.
 * 
 * You must write an algorithm that runs in O(n) time.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Hash Set - find sequence starts (Optimal)
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;
        
        for (int num : numSet) {
            // Only start counting if num is the START of a sequence
            // i.e., num-1 doesn't exist in set
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentLen = 1;
                
                // Count consecutive numbers
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentLen++;
                }
                
                maxLen = max(maxLen, currentLen);
            }
        }
        
        return maxLen;
    }
    
    // Solution 2: Sorting
    // Time: O(n log n), Space: O(1) or O(n) for sort
    int longestConsecutiveSorting(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        sort(nums.begin(), nums.end());
        
        int maxLen = 1;
        int currentLen = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                // Skip duplicates
                continue;
            } else if (nums[i] == nums[i - 1] + 1) {
                // Consecutive
                currentLen++;
            } else {
                // Gap - reset
                maxLen = max(maxLen, currentLen);
                currentLen = 1;
            }
        }
        
        return max(maxLen, currentLen);
    }
    
    // Solution 3: Union Find
    // Each element points to next consecutive element if exists
    int longestConsecutiveUnionFind(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;
        
        for (int num : nums) {
            if (numSet.count(num)) {
                numSet.erase(num);
                int left = num - 1;
                int right = num + 1;
                
                while (numSet.count(left)) {
                    numSet.erase(left);
                    left--;
                }
                
                while (numSet.count(right)) {
                    numSet.erase(right);
                    right++;
                }
                
                maxLen = max(maxLen, right - left - 1);
            }
        }
        
        return maxLen;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "Test 1 [100,4,200,1,3,2]: " << sol.longestConsecutive(nums1) << endl;
    // Expected: 4 (sequence: 1,2,3,4)
    
    // Test Case 2: Longer sequence
    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "Test 2 [0,3,7,2,5,8,4,6,0,1]: " << sol.longestConsecutive(nums2) << endl;
    // Expected: 9 (sequence: 0,1,2,3,4,5,6,7,8)
    
    // Test Case 3: Empty array
    vector<int> nums3 = {};
    cout << "Test 3 []: " << sol.longestConsecutive(nums3) << endl;
    // Expected: 0
    
    // Test Case 4: Single element
    vector<int> nums4 = {1};
    cout << "Test 4 [1]: " << sol.longestConsecutive(nums4) << endl;
    // Expected: 1
    
    // Test Case 5: No consecutive (all same)
    vector<int> nums5 = {5, 5, 5, 5};
    cout << "Test 5 [5,5,5,5]: " << sol.longestConsecutive(nums5) << endl;
    // Expected: 1
    
    // Test Case 6: Negative numbers
    vector<int> nums6 = {-3, -2, -1, 0, 1};
    cout << "Test 6 [-3,-2,-1,0,1]: " << sol.longestConsecutive(nums6) << endl;
    // Expected: 5
    
    // Test Case 7: Separate sequences
    vector<int> nums7 = {1, 2, 3, 100, 101, 102, 103};
    cout << "Test 7 [1,2,3,100,101,102,103]: " << sol.longestConsecutive(nums7) << endl;
    // Expected: 4 (sequence: 100,101,102,103)
    
    return 0;
}

