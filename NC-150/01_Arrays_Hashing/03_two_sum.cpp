/*
 * LeetCode 1: Two Sum
 * https://leetcode.com/problems/two-sum/
 * 
 * Given an array of integers nums and an integer target, return indices of 
 * the two numbers such that they add up to target.
 * 
 * You may assume that each input would have exactly one solution, and you 
 * may not use the same element twice.
 * 
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(n) - hash map storage
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Solution 1: Hash Map - One Pass (Optimal)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numToIndex;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (numToIndex.count(complement)) {
                return {numToIndex[complement], i};
            }
            
            numToIndex[nums[i]] = i;
        }
        
        return {}; // No solution found (shouldn't happen per problem statement)
    }
    
    // Solution 2: Hash Map - Two Pass
    vector<int> twoSumTwoPass(vector<int>& nums, int target) {
        unordered_map<int, int> numToIndex;
        
        // First pass: build the hash map
        for (int i = 0; i < nums.size(); i++) {
            numToIndex[nums[i]] = i;
        }
        
        // Second pass: find complement
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (numToIndex.count(complement) && numToIndex[complement] != i) {
                return {i, numToIndex[complement]};
            }
        }
        
        return {};
    }
    
    // Solution 3: Brute Force
    // Time: O(n^2), Space: O(1)
    vector<int> twoSumBruteForce(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};

void printResult(vector<int>& result) {
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> nums1 = {2, 7, 11, 15};
    auto result1 = sol.twoSum(nums1, 9);
    cout << "Test 1 [2,7,11,15] target=9: ";
    printResult(result1);
    // Expected: [0, 1]
    
    // Test Case 2: Non-adjacent elements
    vector<int> nums2 = {3, 2, 4};
    auto result2 = sol.twoSum(nums2, 6);
    cout << "Test 2 [3,2,4] target=6: ";
    printResult(result2);
    // Expected: [1, 2]
    
    // Test Case 3: Same number twice
    vector<int> nums3 = {3, 3};
    auto result3 = sol.twoSum(nums3, 6);
    cout << "Test 3 [3,3] target=6: ";
    printResult(result3);
    // Expected: [0, 1]
    
    // Test Case 4: Negative numbers
    vector<int> nums4 = {-1, -2, -3, -4, -5};
    auto result4 = sol.twoSum(nums4, -8);
    cout << "Test 4 [-1,-2,-3,-4,-5] target=-8: ";
    printResult(result4);
    // Expected: [2, 4]
    
    // Test Case 5: Zero in array
    vector<int> nums5 = {0, 4, 3, 0};
    auto result5 = sol.twoSum(nums5, 0);
    cout << "Test 5 [0,4,3,0] target=0: ";
    printResult(result5);
    // Expected: [0, 3]
    
    // Test Case 6: Large numbers
    vector<int> nums6 = {1000000000, 2000000000};
    auto result6 = sol.twoSum(nums6, 3000000000);
    cout << "Test 6 [1000000000, 2000000000] target=3000000000: ";
    printResult(result6);
    // Expected: [0, 1]
    
    return 0;
}

