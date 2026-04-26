/*
 * LeetCode 875: Koko Eating Bananas
 * https://leetcode.com/problems/koko-eating-bananas/
 * 
 * Koko can eat k bananas per hour. Find minimum k to eat all bananas in h hours.
 * 
 * Time Complexity: O(n * log(max(piles)))
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canFinish(piles, mid, h)) {
                right = mid;  // Try smaller speed
            } else {
                left = mid + 1;  // Need faster speed
            }
        }
        
        return left;
    }
    
private:
    bool canFinish(vector<int>& piles, int k, int h) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + k - 1) / k;  // Ceiling division
        }
        return hours <= h;
    }
};

int main() {
    Solution sol;
    
    vector<int> piles1 = {3, 6, 7, 11};
    cout << "Test 1 [3,6,7,11] h=8: " << sol.minEatingSpeed(piles1, 8) << endl;
    // Expected: 4
    
    vector<int> piles2 = {30, 11, 23, 4, 20};
    cout << "Test 2 [30,11,23,4,20] h=5: " << sol.minEatingSpeed(piles2, 5) << endl;
    // Expected: 30
    
    cout << "Test 3 [30,11,23,4,20] h=6: " << sol.minEatingSpeed(piles2, 6) << endl;
    // Expected: 23
    
    return 0;
}

