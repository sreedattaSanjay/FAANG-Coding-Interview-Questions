/*
 * LeetCode 739: Daily Temperatures
 * https://leetcode.com/problems/daily-temperatures/
 * 
 * Given an array of integers temperatures, return an array answer such that 
 * answer[i] is the number of days you have to wait after the ith day to get 
 * a warmer temperature.
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
    // Solution 1: Monotonic Decreasing Stack
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> stk;  // Stores indices
        
        for (int i = 0; i < n; i++) {
            // While current temp is warmer than temp at stack top
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int prevIndex = stk.top();
                stk.pop();
                result[prevIndex] = i - prevIndex;
            }
            stk.push(i);
        }
        
        return result;
    }
    
    // Solution 2: Iterate from right (alternative approach)
    vector<int> dailyTemperaturesFromRight(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        
        for (int i = n - 2; i >= 0; i--) {
            int j = i + 1;
            while (j < n) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    break;
                } else if (result[j] == 0) {
                    // No warmer day after j
                    break;
                } else {
                    // Jump to next potential warmer day
                    j += result[j];
                }
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
    vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    auto result1 = sol.dailyTemperatures(temps1);
    cout << "Test 1: ";
    printVector(result1);
    // Expected: [1, 1, 4, 2, 1, 1, 0, 0]
    
    // Test Case 2: All decreasing
    vector<int> temps2 = {30, 40, 50, 60};
    auto result2 = sol.dailyTemperatures(temps2);
    cout << "Test 2: ";
    printVector(result2);
    // Expected: [1, 1, 1, 0]
    
    // Test Case 3: All same
    vector<int> temps3 = {30, 30, 30};
    auto result3 = sol.dailyTemperatures(temps3);
    cout << "Test 3: ";
    printVector(result3);
    // Expected: [0, 0, 0]
    
    // Test Case 4: Decreasing then jump
    vector<int> temps4 = {89, 62, 70, 58, 47, 90};
    auto result4 = sol.dailyTemperatures(temps4);
    cout << "Test 4: ";
    printVector(result4);
    // Expected: [5, 1, 3, 2, 1, 0]
    
    return 0;
}

