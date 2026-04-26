/*
 * LeetCode 167: Two Sum II - Input Array Is Sorted
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * 
 * Given a 1-indexed array of integers numbers that is already sorted in 
 * non-decreasing order, find two numbers such that they add up to a specific 
 * target number. Return the indices of the two numbers (1-indexed).
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Solution 1: Two Pointers (Optimal)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            
            if (sum == target) {
                return {left + 1, right + 1};  // 1-indexed
            } else if (sum < target) {
                left++;   // Need larger sum
            } else {
                right--;  // Need smaller sum
            }
        }
        
        return {};  // No solution found (shouldn't happen per problem)
    }
    
    // Solution 2: Binary Search for each element
    // Time: O(n log n)
    vector<int> twoSumBinarySearch(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); i++) {
            int complement = target - numbers[i];
            
            // Binary search for complement in [i+1, n-1]
            int left = i + 1, right = numbers.size() - 1;
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (numbers[mid] == complement) {
                    return {i + 1, mid + 1};
                } else if (numbers[mid] < complement) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
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
    // Expected: [1, 2]
    
    // Test Case 2: Target in middle
    vector<int> nums2 = {2, 3, 4};
    auto result2 = sol.twoSum(nums2, 6);
    cout << "Test 2 [2,3,4] target=6: ";
    printResult(result2);
    // Expected: [1, 3]
    
    // Test Case 3: Negative numbers
    vector<int> nums3 = {-1, 0};
    auto result3 = sol.twoSum(nums3, -1);
    cout << "Test 3 [-1,0] target=-1: ";
    printResult(result3);
    // Expected: [1, 2]
    
    // Test Case 4: Large gap between numbers
    vector<int> nums4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto result4 = sol.twoSum(nums4, 17);
    cout << "Test 4 [1,2,3,4,5,6,7,8,9] target=17: ";
    printResult(result4);
    // Expected: [8, 9]
    
    // Test Case 5: Same numbers
    vector<int> nums5 = {3, 3};
    auto result5 = sol.twoSum(nums5, 6);
    cout << "Test 5 [3,3] target=6: ";
    printResult(result5);
    // Expected: [1, 2]
    
    return 0;
}

