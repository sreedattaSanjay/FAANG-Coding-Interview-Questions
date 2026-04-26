/*
 * LeetCode 853: Car Fleet
 * https://leetcode.com/problems/car-fleet/
 * 
 * n cars are going to the same destination along a one-lane road.
 * A car fleet is some non-empty set of cars driving at the same position 
 * and same speed. Count the number of car fleets that will arrive at destination.
 * 
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;
        
        // Create pairs of (position, time to reach target)
        vector<pair<int, double>> cars;
        for (int i = 0; i < n; i++) {
            double time = (double)(target - position[i]) / speed[i];
            cars.push_back({position[i], time});
        }
        
        // Sort by position (descending - closest to target first)
        sort(cars.begin(), cars.end(), [](auto& a, auto& b) {
            return a.first > b.first;
        });
        
        // Count fleets using stack
        stack<double> fleets;
        for (auto& [pos, time] : cars) {
            if (fleets.empty() || time > fleets.top()) {
                // New fleet (slower car that can't catch up)
                fleets.push(time);
            }
            // Else: this car catches up to the fleet ahead
        }
        
        return fleets.size();
    }
    
    // Solution 2: Without explicit stack
    int carFleetNoStack(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;
        
        vector<pair<int, double>> cars;
        for (int i = 0; i < n; i++) {
            double time = (double)(target - position[i]) / speed[i];
            cars.push_back({position[i], time});
        }
        
        sort(cars.begin(), cars.end());  // Sort by position ascending
        
        int fleets = 0;
        double maxTime = 0;
        
        // Iterate from closest to target (back to front)
        for (int i = n - 1; i >= 0; i--) {
            if (cars[i].second > maxTime) {
                fleets++;
                maxTime = cars[i].second;
            }
        }
        
        return fleets;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Basic case
    vector<int> pos1 = {10, 8, 0, 5, 3};
    vector<int> speed1 = {2, 4, 1, 1, 3};
    cout << "Test 1: " << sol.carFleet(12, pos1, speed1) << endl;
    // Expected: 3
    
    // Test Case 2: Single car
    vector<int> pos2 = {3};
    vector<int> speed2 = {3};
    cout << "Test 2: " << sol.carFleet(10, pos2, speed2) << endl;
    // Expected: 1
    
    // Test Case 3: All catch up
    vector<int> pos3 = {0, 2, 4};
    vector<int> speed3 = {4, 2, 1};
    cout << "Test 3: " << sol.carFleet(100, pos3, speed3) << endl;
    // Expected: 1
    
    // Test Case 4: None catch up
    vector<int> pos4 = {6, 8};
    vector<int> speed4 = {3, 2};
    cout << "Test 4: " << sol.carFleet(10, pos4, speed4) << endl;
    // Expected: 2
    
    return 0;
}

