/*
 * LeetCode 11: Container With Most Water
 * https://leetcode.com/problems/container-with-most-water/
 * 
 * Given n non-negative integers height representing an elevation map where 
 * the width of each bar is 1, find two lines that together with the x-axis 
 * form a container, such that the container contains the most water.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Two Pointers (Optimal)
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            // Calculate area: width * min(left height, right height)
            int width = right - left;
            int h = min(height[left], height[right]);
            int area = width * h;
            
            maxWater = max(maxWater, area);
            
            // Move the pointer with smaller height
            // (moving the larger one can only decrease or maintain area)
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
    
    // Solution 2: Brute Force (for comparison)
    // Time: O(n^2)
    int maxAreaBruteForce(vector<int>& height) {
        int maxWater = 0;
        int n = height.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int width = j - i;
                int h = min(height[i], height[j]);
                maxWater = max(maxWater, width * h);
            }
        }
        
        return maxWater;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Test 1 [1,8,6,2,5,4,8,3,7]: " << sol.maxArea(height1) << endl;
    // Expected: 49 (between indices 1 and 8, height=7, width=7)
    
    // Test Case 2: Two elements
    vector<int> height2 = {1, 1};
    cout << "Test 2 [1,1]: " << sol.maxArea(height2) << endl;
    // Expected: 1
    
    // Test Case 3: Decreasing heights
    vector<int> height3 = {4, 3, 2, 1, 4};
    cout << "Test 3 [4,3,2,1,4]: " << sol.maxArea(height3) << endl;
    // Expected: 16 (between indices 0 and 4)
    
    // Test Case 4: All same height
    vector<int> height4 = {5, 5, 5, 5, 5};
    cout << "Test 4 [5,5,5,5,5]: " << sol.maxArea(height4) << endl;
    // Expected: 20 (between indices 0 and 4)
    
    // Test Case 5: One very tall
    vector<int> height5 = {1, 2, 100, 2, 1};
    cout << "Test 5 [1,2,100,2,1]: " << sol.maxArea(height5) << endl;
    // Expected: 4 (between indices 0 and 4, limited by shorter sides)
    
    // Test Case 6: Large at ends
    vector<int> height6 = {10, 1, 1, 1, 10};
    cout << "Test 6 [10,1,1,1,10]: " << sol.maxArea(height6) << endl;
    // Expected: 40 (between indices 0 and 4)
    
    return 0;
}

