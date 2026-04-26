/*
 * LeetCode 704: Binary Search
 * https://leetcode.com/problems/binary-search/
 * 
 * Given an array of integers nums sorted in ascending order, and a target value,
 * write a function to search for target. Return index if found, else return -1.
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Solution 1: Iterative Binary Search
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // Solution 2: Recursive Binary Search
    int searchRecursive(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size() - 1);
    }
    
private:
    int binarySearch(vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) return binarySearch(nums, target, mid + 1, right);
        return binarySearch(nums, target, left, mid - 1);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Target in middle
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    cout << "Test 1 target=9: " << sol.search(nums1, 9) << endl;
    // Expected: 4
    
    // Test Case 2: Target not found
    cout << "Test 2 target=2: " << sol.search(nums1, 2) << endl;
    // Expected: -1
    
    // Test Case 3: Single element found
    vector<int> nums3 = {5};
    cout << "Test 3 [5] target=5: " << sol.search(nums3, 5) << endl;
    // Expected: 0
    
    // Test Case 4: Single element not found
    cout << "Test 4 [5] target=1: " << sol.search(nums3, 1) << endl;
    // Expected: -1
    
    // Test Case 5: First element
    cout << "Test 5 target=-1: " << sol.search(nums1, -1) << endl;
    // Expected: 0
    
    // Test Case 6: Last element
    cout << "Test 6 target=12: " << sol.search(nums1, 12) << endl;
    // Expected: 5
    
    return 0;
}

