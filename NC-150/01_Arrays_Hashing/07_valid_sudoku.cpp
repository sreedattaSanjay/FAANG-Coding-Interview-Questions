/*
 * LeetCode 36: Valid Sudoku
 * https://leetcode.com/problems/valid-sudoku/
 * 
 * Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be 
 * validated according to the following rules:
 * 1. Each row must contain the digits 1-9 without repetition.
 * 2. Each column must contain the digits 1-9 without repetition.
 * 3. Each of the nine 3x3 sub-boxes must contain digits 1-9 without repetition.
 * 
 * Time Complexity: O(81) = O(1) - fixed size board
 * Space Complexity: O(81) = O(1) - fixed size sets
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    // Solution 1: Three sets for rows, cols, and boxes
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> rows[9];
        unordered_set<char> cols[9];
        unordered_set<char> boxes[9];
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c == '.') continue;
                
                // Calculate box index: 3 * (i / 3) + (j / 3)
                int boxIdx = 3 * (i / 3) + (j / 3);
                
                // Check if already exists in row, col, or box
                if (rows[i].count(c) || cols[j].count(c) || boxes[boxIdx].count(c)) {
                    return false;
                }
                
                rows[i].insert(c);
                cols[j].insert(c);
                boxes[boxIdx].insert(c);
            }
        }
        
        return true;
    }
    
    // Solution 2: Single set with encoded keys
    bool isValidSudokuEncoded(vector<vector<char>>& board) {
        unordered_set<string> seen;
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c == '.') continue;
                
                string rowKey = string(1, c) + " in row " + to_string(i);
                string colKey = string(1, c) + " in col " + to_string(j);
                string boxKey = string(1, c) + " in box " + to_string(i/3) + "-" + to_string(j/3);
                
                if (seen.count(rowKey) || seen.count(colKey) || seen.count(boxKey)) {
                    return false;
                }
                
                seen.insert(rowKey);
                seen.insert(colKey);
                seen.insert(boxKey);
            }
        }
        
        return true;
    }
    
    // Solution 3: Bitmask approach
    bool isValidSudokuBitmask(vector<vector<char>>& board) {
        int rows[9] = {0}, cols[9] = {0}, boxes[9] = {0};
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                
                int num = board[i][j] - '0';
                int mask = 1 << num;
                int boxIdx = 3 * (i / 3) + (j / 3);
                
                if ((rows[i] & mask) || (cols[j] & mask) || (boxes[boxIdx] & mask)) {
                    return false;
                }
                
                rows[i] |= mask;
                cols[j] |= mask;
                boxes[boxIdx] |= mask;
            }
        }
        
        return true;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Valid Sudoku
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << "Test 1 (Valid): " << (sol.isValidSudoku(board1) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2: Invalid - duplicate in row
    vector<vector<char>> board2 = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << "Test 2 (Invalid - duplicate 8 in col): " << (sol.isValidSudoku(board2) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3: Empty board
    vector<vector<char>> board3(9, vector<char>(9, '.'));
    cout << "Test 3 (Empty): " << (sol.isValidSudoku(board3) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4: Invalid - duplicate in box
    vector<vector<char>> board4 = {
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'1','.','.','.','.','.','.','.','.'},
        {'.','1','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','1'}
    };
    cout << "Test 4 (Invalid - duplicate 1 in box 6): " << (sol.isValidSudoku(board4) ? "true" : "false") << endl;
    // Expected: false
    
    return 0;
}

