/*
 * LeetCode 33: Search in Rotated Sorted Array
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * 
 * Search for target in rotated sorted array with unique elements.
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) return mid;
            
            // Check which half is sorted
            if (nums[left] <= nums[mid]) {
                // Left half is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test 1 target=0: " << sol.search(nums, 0) << endl;
    // Expected: 4
    
    cout << "Test 2 target=3: " << sol.search(nums, 3) << endl;
    // Expected: -1
    
    vector<int> nums2 = {1};
    cout << "Test 3 [1] target=0: " << sol.search(nums2, 0) << endl;
    // Expected: -1
    
    return 0;
}

