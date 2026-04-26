/*
 * LeetCode 150: Evaluate Reverse Polish Notation
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 * 
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * Valid operators are +, -, *, /. Each operand may be an integer or another expression.
 * Division truncates toward zero.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> stk;
        unordered_set<string> operators = {"+", "-", "*", "/"};
        
        for (const string& token : tokens) {
            if (operators.count(token)) {
                long long b = stk.top(); stk.pop();
                long long a = stk.top(); stk.pop();
                
                long long result;
                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else result = a / b;  // Truncates toward zero
                
                stk.push(result);
            } else {
                stk.push(stoll(token));
            }
        }
        
        return stk.top();
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Simple addition
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    cout << "Test 1 ['2','1','+','3','*']: " << sol.evalRPN(tokens1) << endl;
    // Expected: 9 ((2+1)*3)
    
    // Test Case 2: Division
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    cout << "Test 2 ['4','13','5','/','+]: " << sol.evalRPN(tokens2) << endl;
    // Expected: 6 (4+(13/5))
    
    // Test Case 3: Complex expression
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    cout << "Test 3 [complex]: " << sol.evalRPN(tokens3) << endl;
    // Expected: 22
    
    // Test Case 4: Negative numbers
    vector<string> tokens4 = {"-2", "3", "*"};
    cout << "Test 4 ['-2','3','*']: " << sol.evalRPN(tokens4) << endl;
    // Expected: -6
    
    // Test Case 5: Single number
    vector<string> tokens5 = {"42"};
    cout << "Test 5 ['42']: " << sol.evalRPN(tokens5) << endl;
    // Expected: 42
    
    // Test Case 6: Subtraction order
    vector<string> tokens6 = {"3", "4", "-"};
    cout << "Test 6 ['3','4','-']: " << sol.evalRPN(tokens6) << endl;
    // Expected: -1 (3-4)
    
    return 0;
}

