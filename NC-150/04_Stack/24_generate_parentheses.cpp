/*
 * LeetCode 22: Generate Parentheses
 * https://leetcode.com/problems/generate-parentheses/
 * 
 * Given n pairs of parentheses, write a function to generate all combinations 
 * of well-formed parentheses.
 * 
 * Time Complexity: O(4^n / sqrt(n)) - nth Catalan number
 * Space Complexity: O(n) for recursion stack
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
    
private:
    void backtrack(vector<string>& result, string current, int open, int close, int n) {
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        // Can add '(' if we haven't used all n
        if (open < n) {
            backtrack(result, current + "(", open + 1, close, n);
        }
        
        // Can add ')' only if there are unmatched '('
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, n);
        }
    }
};

// Solution 2: Iterative with explicit stack (less common)
class SolutionIterative {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        vector<tuple<string, int, int>> stack;  // (current, open, close)
        stack.push_back({"", 0, 0});
        
        while (!stack.empty()) {
            auto [current, open, close] = stack.back();
            stack.pop_back();
            
            if (current.length() == 2 * n) {
                result.push_back(current);
                continue;
            }
            
            if (close < open) {
                stack.push_back({current + ")", open, close + 1});
            }
            if (open < n) {
                stack.push_back({current + "(", open + 1, close});
            }
        }
        
        return result;
    }
};

void printResult(vector<string>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1: n = 3
    auto result1 = sol.generateParenthesis(3);
    cout << "Test 1 n=3: ";
    printResult(result1);
    // Expected: ["((()))","(()())","(())()","()(())","()()()"]
    
    // Test Case 2: n = 1
    auto result2 = sol.generateParenthesis(1);
    cout << "Test 2 n=1: ";
    printResult(result2);
    // Expected: ["()"]
    
    // Test Case 3: n = 2
    auto result3 = sol.generateParenthesis(2);
    cout << "Test 3 n=2: ";
    printResult(result3);
    // Expected: ["(())","()()"]
    
    // Test Case 4: n = 4
    auto result4 = sol.generateParenthesis(4);
    cout << "Test 4 n=4 (count=" << result4.size() << "): ";
    // Expected: 14 combinations
    
    return 0;
}

