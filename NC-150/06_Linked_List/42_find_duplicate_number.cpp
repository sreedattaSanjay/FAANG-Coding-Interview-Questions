/*
 * Problem: Find the Duplicate Number (LeetCode 287)
 * 
 * Given an array of integers nums containing n + 1 integers where each integer
 * is in the range [1, n] inclusive. There is only one repeated number, find it.
 * 
 * Constraints:
 * - Must not modify the array
 * - Must use only constant extra space
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>

class Solution {
public:
    // Floyd's Cycle Detection - treat array as linked list
    // nums[i] = next pointer, index = node
    // Time: O(n), Space: O(1)
    int findDuplicate(std::vector<int>& nums) {
        // Phase 1: Find the intersection point
        int slow = nums[0];
        int fast = nums[0];
        
        do {
            slow = nums[slow];           // Move 1 step
            fast = nums[nums[fast]];     // Move 2 steps
        } while (slow != fast);
        
        // Phase 2: Find the entrance to the cycle (duplicate)
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
    
    // Alternative: Binary Search (doesn't modify array)
    // Time: O(n log n), Space: O(1)
    int findDuplicateBinarySearch(std::vector<int>& nums) {
        int left = 1, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = 0;
            
            // Count numbers <= mid
            for (int num : nums) {
                if (num <= mid) count++;
            }
            
            // If count > mid, duplicate is in [1, mid]
            if (count > mid) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,3,4,2,2] -> 2
    std::vector<int> nums1 = {1, 3, 4, 2, 2};
    std::cout << "Array: [1,3,4,2,2]" << std::endl;
    std::cout << "Duplicate: " << sol.findDuplicate(nums1) << std::endl;
    
    // Test case 2: [3,1,3,4,2] -> 3
    std::vector<int> nums2 = {3, 1, 3, 4, 2};
    std::cout << "\nArray: [3,1,3,4,2]" << std::endl;
    std::cout << "Duplicate: " << sol.findDuplicate(nums2) << std::endl;
    
    // Test case 3: [1,1] -> 1
    std::vector<int> nums3 = {1, 1};
    std::cout << "\nArray: [1,1]" << std::endl;
    std::cout << "Duplicate: " << sol.findDuplicate(nums3) << std::endl;
    
    // Test case 4: [1,1,2] -> 1
    std::vector<int> nums4 = {1, 1, 2};
    std::cout << "\nArray: [1,1,2]" << std::endl;
    std::cout << "Duplicate: " << sol.findDuplicate(nums4) << std::endl;
    
    // Test case 5: [2,2,2,2,2] -> 2
    std::vector<int> nums5 = {2, 2, 2, 2, 2};
    std::cout << "\nArray: [2,2,2,2,2]" << std::endl;
    std::cout << "Duplicate: " << sol.findDuplicate(nums5) << std::endl;
    
    // Test binary search approach
    std::vector<int> nums6 = {1, 3, 4, 2, 2};
    std::cout << "\nBinary search approach: " << sol.findDuplicateBinarySearch(nums6) << std::endl;
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

