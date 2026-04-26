/*
 * LeetCode 155: Min Stack
 * https://leetcode.com/problems/min-stack/
 * 
 * Design a stack that supports push, pop, top, and retrieving the minimum 
 * element in constant time.
 * 
 * Time Complexity: O(1) for all operations
 * Space Complexity: O(n)
 */

#include <iostream>
#include <stack>
#include <climits>
using namespace std;

// Solution 1: Two stacks - main stack and min stack
class MinStack {
private:
    stack<int> mainStack;
    stack<int> minStack;
    
public:
    MinStack() {}
    
    void push(int val) {
        mainStack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// Solution 2: Single stack with pairs (value, currentMin)
class MinStackPairs {
private:
    stack<pair<int, int>> stk;  // (value, min at this point)
    
public:
    MinStackPairs() {}
    
    void push(int val) {
        if (stk.empty()) {
            stk.push({val, val});
        } else {
            stk.push({val, min(val, stk.top().second)});
        }
    }
    
    void pop() {
        stk.pop();
    }
    
    int top() {
        return stk.top().first;
    }
    
    int getMin() {
        return stk.top().second;
    }
};

int main() {
    // Test MinStack
    MinStack minStack;
    
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "getMin(): " << minStack.getMin() << endl;  // Expected: -3
    minStack.pop();
    cout << "top(): " << minStack.top() << endl;        // Expected: 0
    cout << "getMin(): " << minStack.getMin() << endl;  // Expected: -2
    
    cout << "\n--- Testing MinStackPairs ---\n";
    
    // Test MinStackPairs
    MinStackPairs minStack2;
    
    minStack2.push(-2);
    minStack2.push(0);
    minStack2.push(-3);
    cout << "getMin(): " << minStack2.getMin() << endl;  // Expected: -3
    minStack2.pop();
    cout << "top(): " << minStack2.top() << endl;        // Expected: 0
    cout << "getMin(): " << minStack2.getMin() << endl;  // Expected: -2
    
    return 0;
}

