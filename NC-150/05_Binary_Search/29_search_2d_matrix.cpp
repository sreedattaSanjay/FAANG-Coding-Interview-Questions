/*
 * LeetCode 74: Search a 2D Matrix
 * https://leetcode.com/problems/search-a-2d-matrix/
 * 
 * Given m x n matrix with sorted rows and first element of each row greater 
 * than last element of previous row, search for a target value.
 * 
 * Time Complexity: O(log(m*n))
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Solution 1: Treat as 1D sorted array
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = matrix[mid / n][mid % n];
            
            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
    
    // Solution 2: Two binary searches (find row, then column)
    bool searchMatrixTwoPass(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        
        // Binary search for row
        int top = 0, bottom = m - 1;
        while (top <= bottom) {
            int midRow = top + (bottom - top) / 2;
            if (target < matrix[midRow][0]) {
                bottom = midRow - 1;
            } else if (target > matrix[midRow][n - 1]) {
                top = midRow + 1;
            } else {
                // Target is in this row
                int left = 0, right = n - 1;
                while (left <= right) {
                    int mid = left + (right - left) / 2;
                    if (matrix[midRow][mid] == target) return true;
                    else if (matrix[midRow][mid] < target) left = mid + 1;
                    else right = mid - 1;
                }
                return false;
            }
        }
        
        return false;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    
    cout << "Test 1 target=3: " << (sol.searchMatrix(matrix, 3) ? "true" : "false") << endl;
    // Expected: true
    
    cout << "Test 2 target=13: " << (sol.searchMatrix(matrix, 13) ? "true" : "false") << endl;
    // Expected: false
    
    vector<vector<int>> matrix2 = {{1}};
    cout << "Test 3 [[1]] target=1: " << (sol.searchMatrix(matrix2, 1) ? "true" : "false") << endl;
    // Expected: true
    
    cout << "Test 4 [[1]] target=0: " << (sol.searchMatrix(matrix2, 0) ? "true" : "false") << endl;
    // Expected: false
    
    return 0;
}

