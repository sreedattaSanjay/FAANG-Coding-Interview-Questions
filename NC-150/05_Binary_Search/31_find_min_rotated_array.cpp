/*
 * LeetCode 153: Find Minimum in Rotated Sorted Array
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 * 
 * Given a rotated sorted array with unique elements, find the minimum element.
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right]) {
                // Minimum is in right half
                left = mid + 1;
            } else {
                // Minimum is in left half (including mid)
                right = mid;
            }
        }
        
        return nums[left];
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {3, 4, 5, 1, 2};
    cout << "Test 1 [3,4,5,1,2]: " << sol.findMin(nums1) << endl;
    // Expected: 1
    
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test 2 [4,5,6,7,0,1,2]: " << sol.findMin(nums2) << endl;
    // Expected: 0
    
    vector<int> nums3 = {11, 13, 15, 17};
    cout << "Test 3 [11,13,15,17]: " << sol.findMin(nums3) << endl;
    // Expected: 11
    
    vector<int> nums4 = {2, 1};
    cout << "Test 4 [2,1]: " << sol.findMin(nums4) << endl;
    // Expected: 1
    
    return 0;
}

