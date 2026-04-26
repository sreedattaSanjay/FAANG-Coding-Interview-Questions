/*
 * LeetCode 20: Valid Parentheses
 * https://leetcode.com/problems/valid-parentheses/
 * 
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * 
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Solution 1: Stack with HashMap
    bool isValid(string s) {
        stack<char> stk;
        unordered_map<char, char> pairs = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        for (char c : s) {
            if (pairs.count(c)) {
                // It's a closing bracket
                if (stk.empty() || stk.top() != pairs[c]) {
                    return false;
                }
                stk.pop();
            } else {
                // It's an opening bracket
                stk.push(c);
            }
        }
        
        return stk.empty();
    }
    
    // Solution 2: Without HashMap
    bool isValidSimple(string s) {
        stack<char> stk;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stk.push(c);
            } else {
                if (stk.empty()) return false;
                
                char top = stk.top();
                if ((c == ')' && top == '(') ||
                    (c == '}' && top == '{') ||
                    (c == ']' && top == '[')) {
                    stk.pop();
                } else {
                    return false;
                }
            }
        }
        
        return stk.empty();
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Simple valid
    cout << "Test 1 '()': " << (sol.isValid("()") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2: Multiple types
    cout << "Test 2 '()[]{}': " << (sol.isValid("()[]{}") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 3: Nested
    cout << "Test 3 '{[]}': " << (sol.isValid("{[]}") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4: Mismatch
    cout << "Test 4 '(]': " << (sol.isValid("(]") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 5: Wrong order
    cout << "Test 5 '([)]': " << (sol.isValid("([)]") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 6: Only opening
    cout << "Test 6 '(': " << (sol.isValid("(") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 7: Only closing
    cout << "Test 7 ')': " << (sol.isValid(")") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 8: Empty string
    cout << "Test 8 '': " << (sol.isValid("") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 9: Complex nested
    cout << "Test 9 '(({{[[]]}}))': " << (sol.isValid("(({{[[]]}}))") ? "true" : "false") << endl;
    // Expected: true
    
    return 0;
}

