/*
 * LeetCode 42: Trapping Rain Water
 * https://leetcode.com/problems/trapping-rain-water/
 * 
 * Given n non-negative integers representing an elevation map where the width 
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1) for two-pointer approach
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    // Solution 1: Two Pointers (Optimal)
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }
        
        return water;
    }
    
    // Solution 2: Prefix/Suffix Max Arrays
    // Time: O(n), Space: O(n)
    int trapArrays(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;
        
        vector<int> leftMax(n), rightMax(n);
        
        // Build left max array
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        
        // Build right max array
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }
        
        // Calculate water
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }
        
        return water;
    }
    
    // Solution 3: Monotonic Stack
    // Time: O(n), Space: O(n)
    int trapStack(vector<int>& height) {
        stack<int> st;
        int water = 0;
        
        for (int i = 0; i < height.size(); i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int bottom = st.top();
                st.pop();
                
                if (st.empty()) break;
                
                int width = i - st.top() - 1;
                int h = min(height[i], height[st.top()]) - height[bottom];
                water += width * h;
            }
            st.push(i);
        }
        
        return water;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Test 1 [0,1,0,2,1,0,1,3,2,1,2,1]: " << sol.trap(height1) << endl;
    // Expected: 6
    
    // Test Case 2: Another case
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << "Test 2 [4,2,0,3,2,5]: " << sol.trap(height2) << endl;
    // Expected: 9
    
    // Test Case 3: Empty
    vector<int> height3 = {};
    cout << "Test 3 []: " << sol.trap(height3) << endl;
    // Expected: 0
    
    // Test Case 4: No water (increasing)
    vector<int> height4 = {1, 2, 3, 4};
    cout << "Test 4 [1,2,3,4]: " << sol.trap(height4) << endl;
    // Expected: 0
    
    // Test Case 5: No water (decreasing)
    vector<int> height5 = {4, 3, 2, 1};
    cout << "Test 5 [4,3,2,1]: " << sol.trap(height5) << endl;
    // Expected: 0
    
    // Test Case 6: Single element
    vector<int> height6 = {5};
    cout << "Test 6 [5]: " << sol.trap(height6) << endl;
    // Expected: 0
    
    // Test Case 7: Two elements
    vector<int> height7 = {5, 4};
    cout << "Test 7 [5,4]: " << sol.trap(height7) << endl;
    // Expected: 0
    
    // Test Case 8: Valley
    vector<int> height8 = {5, 2, 5};
    cout << "Test 8 [5,2,5]: " << sol.trap(height8) << endl;
    // Expected: 3
    
    return 0;
}

