/*
 * LeetCode 15: 3Sum
 * https://leetcode.com/problems/3sum/
 * 
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * 
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(1) excluding output (O(n) for sorting in some implementations)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Sort + Two Pointers (Optimal)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        if (n < 3) return result;
        
        // Sort the array
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for i
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            // Early termination: if smallest is positive, no solution
            if (nums[i] > 0) break;
            
            int left = i + 1;
            int right = n - 1;
            int target = -nums[i];
            
            while (left < right) {
                int sum = nums[left] + nums[right];
                
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for left
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for right
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

void printResult(vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[" << result[i][0] << "," << result[i][1] << "," << result[i][2] << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1: Basic case with multiple solutions
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    auto result1 = sol.threeSum(nums1);
    cout << "Test 1 [-1,0,1,2,-1,-4]: ";
    printResult(result1);
    // Expected: [[-1,-1,2],[-1,0,1]]
    
    // Test Case 2: All zeros
    vector<int> nums2 = {0, 0, 0, 0};
    auto result2 = sol.threeSum(nums2);
    cout << "Test 2 [0,0,0,0]: ";
    printResult(result2);
    // Expected: [[0,0,0]]
    
    // Test Case 3: No solution
    vector<int> nums3 = {1, 2, 3};
    auto result3 = sol.threeSum(nums3);
    cout << "Test 3 [1,2,3]: ";
    printResult(result3);
    // Expected: []
    
    // Test Case 4: Empty array
    vector<int> nums4 = {};
    auto result4 = sol.threeSum(nums4);
    cout << "Test 4 []: ";
    printResult(result4);
    // Expected: []
    
    // Test Case 5: Exactly 3 elements that sum to 0
    vector<int> nums5 = {-1, 0, 1};
    auto result5 = sol.threeSum(nums5);
    cout << "Test 5 [-1,0,1]: ";
    printResult(result5);
    // Expected: [[-1,0,1]]
    
    // Test Case 6: Many duplicates
    vector<int> nums6 = {-2, 0, 0, 2, 2};
    auto result6 = sol.threeSum(nums6);
    cout << "Test 6 [-2,0,0,2,2]: ";
    printResult(result6);
    // Expected: [[-2,0,2]]
    
    return 0;
}

