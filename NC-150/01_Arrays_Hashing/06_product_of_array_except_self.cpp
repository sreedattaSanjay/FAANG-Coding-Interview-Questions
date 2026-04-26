/*
 * LeetCode 238: Product of Array Except Self
 * https://leetcode.com/problems/product-of-array-except-self/
 * 
 * Given an integer array nums, return an array answer such that answer[i] 
 * is equal to the product of all the elements of nums except nums[i].
 * 
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using division.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1) extra space (output array doesn't count)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Solution 1: Two-pass with output array (Optimal)
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // First pass: calculate prefix products
        // result[i] = product of all elements to the left of i
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }
        
        // Second pass: multiply by suffix products
        // result[i] *= product of all elements to the right of i
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }
        
        return result;
    }
    
    // Solution 2: Using prefix and suffix arrays (O(n) extra space)
    vector<int> productExceptSelfArrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n, 1), suffix(n, 1), result(n);
        
        // Build prefix products
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }
        
        // Build suffix products
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }
        
        // Combine
        for (int i = 0; i < n; i++) {
            result[i] = prefix[i] * suffix[i];
        }
        
        return result;
    }
    
    // Solution 3: With Division (if zeros handled, but problem says no division)
    // Included for educational purposes
    vector<int> productExceptSelfDivision(vector<int>& nums) {
        int n = nums.size();
        int product = 1;
        int zeroCount = 0;
        
        for (int num : nums) {
            if (num == 0) {
                zeroCount++;
            } else {
                product *= num;
            }
        }
        
        vector<int> result(n, 0);
        
        for (int i = 0; i < n; i++) {
            if (zeroCount > 1) {
                result[i] = 0;
            } else if (zeroCount == 1) {
                result[i] = (nums[i] == 0) ? product : 0;
            } else {
                result[i] = product / nums[i];
            }
        }
        
        return result;
    }
};

void printVector(vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> nums1 = {1, 2, 3, 4};
    auto result1 = sol.productExceptSelf(nums1);
    cout << "Test 1 [1,2,3,4]: ";
    printVector(result1);
    // Expected: [24, 12, 8, 6]
    
    // Test Case 2: Contains zero
    vector<int> nums2 = {-1, 1, 0, -3, 3};
    auto result2 = sol.productExceptSelf(nums2);
    cout << "Test 2 [-1,1,0,-3,3]: ";
    printVector(result2);
    // Expected: [0, 0, 9, 0, 0]
    
    // Test Case 3: Two elements
    vector<int> nums3 = {1, 2};
    auto result3 = sol.productExceptSelf(nums3);
    cout << "Test 3 [1,2]: ";
    printVector(result3);
    // Expected: [2, 1]
    
    // Test Case 4: Contains multiple zeros
    vector<int> nums4 = {0, 0, 1};
    auto result4 = sol.productExceptSelf(nums4);
    cout << "Test 4 [0,0,1]: ";
    printVector(result4);
    // Expected: [0, 0, 0]
    
    // Test Case 5: All ones
    vector<int> nums5 = {1, 1, 1, 1};
    auto result5 = sol.productExceptSelf(nums5);
    cout << "Test 5 [1,1,1,1]: ";
    printVector(result5);
    // Expected: [1, 1, 1, 1]
    
    // Test Case 6: Negative numbers
    vector<int> nums6 = {-1, -2, -3};
    auto result6 = sol.productExceptSelf(nums6);
    cout << "Test 6 [-1,-2,-3]: ";
    printVector(result6);
    // Expected: [6, 3, 2]
    
    return 0;
}

