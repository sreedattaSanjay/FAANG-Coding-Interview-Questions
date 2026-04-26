/*
 * LeetCode 4: Median of Two Sorted Arrays
 * https://leetcode.com/problems/median-of-two-sorted-arrays/
 * 
 * Find median of two sorted arrays in O(log(m+n)) time.
 * 
 * Time Complexity: O(log(min(m,n)))
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is smaller
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        int half = (m + n + 1) / 2;
        
        while (left <= right) {
            int i = left + (right - left) / 2;  // Partition in nums1
            int j = half - i;                    // Partition in nums2
            
            int nums1Left = (i == 0) ? INT_MIN : nums1[i - 1];
            int nums1Right = (i == m) ? INT_MAX : nums1[i];
            int nums2Left = (j == 0) ? INT_MIN : nums2[j - 1];
            int nums2Right = (j == n) ? INT_MAX : nums2[j];
            
            if (nums1Left <= nums2Right && nums2Left <= nums1Right) {
                // Found correct partition
                if ((m + n) % 2 == 0) {
                    return (max(nums1Left, nums2Left) + min(nums1Right, nums2Right)) / 2.0;
                } else {
                    return max(nums1Left, nums2Left);
                }
            } else if (nums1Left > nums2Right) {
                right = i - 1;
            } else {
                left = i + 1;
            }
        }
        
        return 0.0;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Test 1 [1,3] [2]: " << sol.findMedianSortedArrays(nums1, nums2) << endl;
    // Expected: 2.0
    
    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << "Test 2 [1,2] [3,4]: " << sol.findMedianSortedArrays(nums3, nums4) << endl;
    // Expected: 2.5
    
    return 0;
}

