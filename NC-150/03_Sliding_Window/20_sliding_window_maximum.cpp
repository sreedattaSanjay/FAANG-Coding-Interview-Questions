/*
 * LeetCode 239: Sliding Window Maximum
 * https://leetcode.com/problems/sliding-window-maximum/
 * 
 * Given an array of integers nums and a sliding window of size k moving from 
 * left to right, return the max value in each window.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(k) for the deque
 */

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

class Solution {
public:
    // Solution 1: Monotonic Decreasing Deque (Optimal)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq;  // Stores indices, maintains decreasing order of values
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove elements outside window
            while (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            
            // Remove smaller elements (they can never be max)
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add to result once window is formed
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
    
    // Solution 2: Max Heap with lazy deletion
    // Time: O(n log n) in worst case
    vector<int> maxSlidingWindowHeap(vector<int>& nums, int k) {
        vector<int> result;
        priority_queue<pair<int, int>> maxHeap;  // (value, index)
        
        for (int i = 0; i < nums.size(); i++) {
            maxHeap.push({nums[i], i});
            
            // Remove elements outside window (lazy deletion)
            while (maxHeap.top().second <= i - k) {
                maxHeap.pop();
            }
            
            if (i >= k - 1) {
                result.push_back(maxHeap.top().first);
            }
        }
        
        return result;
    }
    
    // Solution 3: Brute Force (for comparison)
    // Time: O(n * k)
    vector<int> maxSlidingWindowBruteForce(vector<int>& nums, int k) {
        vector<int> result;
        
        for (int i = 0; i <= nums.size() - k; i++) {
            int maxVal = nums[i];
            for (int j = i; j < i + k; j++) {
                maxVal = max(maxVal, nums[j]);
            }
            result.push_back(maxVal);
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
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    auto result1 = sol.maxSlidingWindow(nums1, 3);
    cout << "Test 1 [1,3,-1,-3,5,3,6,7] k=3: ";
    printVector(result1);
    // Expected: [3, 3, 5, 5, 6, 7]
    
    // Test Case 2: k = 1
    vector<int> nums2 = {1, -1};
    auto result2 = sol.maxSlidingWindow(nums2, 1);
    cout << "Test 2 [1,-1] k=1: ";
    printVector(result2);
    // Expected: [1, -1]
    
    // Test Case 3: k = array length
    vector<int> nums3 = {1, 2, 3};
    auto result3 = sol.maxSlidingWindow(nums3, 3);
    cout << "Test 3 [1,2,3] k=3: ";
    printVector(result3);
    // Expected: [3]
    
    // Test Case 4: All same elements
    vector<int> nums4 = {5, 5, 5, 5};
    auto result4 = sol.maxSlidingWindow(nums4, 2);
    cout << "Test 4 [5,5,5,5] k=2: ";
    printVector(result4);
    // Expected: [5, 5, 5]
    
    // Test Case 5: Decreasing array
    vector<int> nums5 = {9, 8, 7, 6, 5};
    auto result5 = sol.maxSlidingWindow(nums5, 2);
    cout << "Test 5 [9,8,7,6,5] k=2: ";
    printVector(result5);
    // Expected: [9, 8, 7, 6]
    
    // Test Case 6: Increasing array
    vector<int> nums6 = {1, 2, 3, 4, 5};
    auto result6 = sol.maxSlidingWindow(nums6, 2);
    cout << "Test 6 [1,2,3,4,5] k=2: ";
    printVector(result6);
    // Expected: [2, 3, 4, 5]
    
    return 0;
}

