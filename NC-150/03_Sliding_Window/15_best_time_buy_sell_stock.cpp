/*
 * LeetCode 121: Best Time to Buy and Sell Stock
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * 
 * You are given an array prices where prices[i] is the price of a given stock 
 * on the ith day. You want to maximize your profit by choosing a single day to 
 * buy and a single day to sell in the future.
 * 
 * Return the maximum profit you can achieve. If no profit is possible, return 0.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    // Solution 1: Track minimum price seen so far
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            minPrice = min(minPrice, price);
            maxProfit = max(maxProfit, price - minPrice);
        }
        
        return maxProfit;
    }
    
    // Solution 2: Kadane's Algorithm variant (max subarray of differences)
    int maxProfitKadane(vector<int>& prices) {
        int maxProfit = 0;
        int currentProfit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            currentProfit = max(0, currentProfit + prices[i] - prices[i - 1]);
            maxProfit = max(maxProfit, currentProfit);
        }
        
        return maxProfit;
    }
    
    // Solution 3: Two Pointers (Sliding Window perspective)
    int maxProfitTwoPointers(vector<int>& prices) {
        if (prices.empty()) return 0;
        
        int left = 0;  // Buy day
        int maxProfit = 0;
        
        for (int right = 1; right < prices.size(); right++) {
            if (prices[right] < prices[left]) {
                left = right;  // Found new minimum
            } else {
                maxProfit = max(maxProfit, prices[right] - prices[left]);
            }
        }
        
        return maxProfit;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Normal profit scenario
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Test 1 [7,1,5,3,6,4]: " << sol.maxProfit(prices1) << endl;
    // Expected: 5 (buy at 1, sell at 6)
    
    // Test Case 2: No profit possible
    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "Test 2 [7,6,4,3,1]: " << sol.maxProfit(prices2) << endl;
    // Expected: 0
    
    // Test Case 3: Single element
    vector<int> prices3 = {1};
    cout << "Test 3 [1]: " << sol.maxProfit(prices3) << endl;
    // Expected: 0
    
    // Test Case 4: Two elements with profit
    vector<int> prices4 = {1, 2};
    cout << "Test 4 [1,2]: " << sol.maxProfit(prices4) << endl;
    // Expected: 1
    
    // Test Case 5: All same prices
    vector<int> prices5 = {3, 3, 3, 3};
    cout << "Test 5 [3,3,3,3]: " << sol.maxProfit(prices5) << endl;
    // Expected: 0
    
    // Test Case 6: Buy at beginning, sell at end
    vector<int> prices6 = {1, 2, 3, 4, 5};
    cout << "Test 6 [1,2,3,4,5]: " << sol.maxProfit(prices6) << endl;
    // Expected: 4
    
    // Test Case 7: Maximum profit in middle
    vector<int> prices7 = {3, 2, 6, 5, 0, 3};
    cout << "Test 7 [3,2,6,5,0,3]: " << sol.maxProfit(prices7) << endl;
    // Expected: 4 (buy at 2, sell at 6)
    
    return 0;
}

