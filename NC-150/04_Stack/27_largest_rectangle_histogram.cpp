/*
 * LeetCode 84: Largest Rectangle in Histogram
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 * 
 * Given an array of integers heights representing the histogram's bar height,
 * return the area of the largest rectangle in the histogram.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    // Solution 1: Monotonic Increasing Stack
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;  // Stores indices
        int maxArea = 0;
        int n = heights.size();
        
        for (int i = 0; i <= n; i++) {
            // Use 0 as sentinel for the last iteration
            int h = (i == n) ? 0 : heights[i];
            
            while (!stk.empty() && h < heights[stk.top()]) {
                int height = heights[stk.top()];
                stk.pop();
                
                // Width: from current position back to previous bar in stack
                int width = stk.empty() ? i : i - stk.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            
            stk.push(i);
        }
        
        return maxArea;
    }
    
    // Solution 2: Two-pass to find boundaries
    int largestRectangleAreaTwoPass(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        stack<int> stk;
        
        // Find left boundary (first smaller element to the left)
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && heights[stk.top()] >= heights[i]) {
                stk.pop();
            }
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        
        while (!stk.empty()) stk.pop();
        
        // Find right boundary (first smaller element to the right)
        for (int i = n - 1; i >= 0; i--) {
            while (!stk.empty() && heights[stk.top()] >= heights[i]) {
                stk.pop();
            }
            right[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        
        // Calculate max area
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            int width = right[i] - left[i] - 1;
            maxArea = max(maxArea, heights[i] * width);
        }
        
        return maxArea;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Test 1 [2,1,5,6,2,3]: " << sol.largestRectangleArea(heights1) << endl;
    // Expected: 10 (5 * 2, between indices 2 and 3)
    
    // Test Case 2: All same height
    vector<int> heights2 = {2, 4};
    cout << "Test 2 [2,4]: " << sol.largestRectangleArea(heights2) << endl;
    // Expected: 4
    
    // Test Case 3: Single bar
    vector<int> heights3 = {5};
    cout << "Test 3 [5]: " << sol.largestRectangleArea(heights3) << endl;
    // Expected: 5
    
    // Test Case 4: Increasing
    vector<int> heights4 = {1, 2, 3, 4, 5};
    cout << "Test 4 [1,2,3,4,5]: " << sol.largestRectangleArea(heights4) << endl;
    // Expected: 9 (3 * 3)
    
    // Test Case 5: Decreasing
    vector<int> heights5 = {5, 4, 3, 2, 1};
    cout << "Test 5 [5,4,3,2,1]: " << sol.largestRectangleArea(heights5) << endl;
    // Expected: 9 (3 * 3)
    
    // Test Case 6: Mountain shape
    vector<int> heights6 = {1, 2, 3, 2, 1};
    cout << "Test 6 [1,2,3,2,1]: " << sol.largestRectangleArea(heights6) << endl;
    // Expected: 6 (2 * 3)
    
    return 0;
}

