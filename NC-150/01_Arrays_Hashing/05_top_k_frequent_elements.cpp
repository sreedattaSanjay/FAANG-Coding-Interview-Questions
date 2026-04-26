/*
 * LeetCode 347: Top K Frequent Elements
 * https://leetcode.com/problems/top-k-frequent-elements/
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements. 
 * You may return the answer in any order.
 * 
 * Time Complexity: O(n) using bucket sort, O(n log k) using heap
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Solution 1: Bucket Sort (Optimal - O(n))
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Step 2: Create buckets where index = frequency
        // bucket[i] contains all numbers with frequency i
        vector<vector<int>> buckets(nums.size() + 1);
        for (auto& [num, count] : freq) {
            buckets[count].push_back(num);
        }
        
        // Step 3: Collect k most frequent from highest bucket down
        vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) break;
            }
        }
        
        return result;
    }
    
    // Solution 2: Min Heap (O(n log k))
    vector<int> topKFrequentHeap(vector<int>& nums, int k) {
        // Count frequencies
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Min heap of (frequency, number) - keeps k largest
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for (auto& [num, count] : freq) {
            minHeap.push({count, num});
            if (minHeap.size() > k) {
                minHeap.pop(); // Remove smallest frequency
            }
        }
        
        // Extract results
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
    
    // Solution 3: Sorting by frequency (O(n log n))
    vector<int> topKFrequentSort(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        vector<pair<int, int>> freqVec(freq.begin(), freq.end());
        sort(freqVec.begin(), freqVec.end(), 
             [](auto& a, auto& b) { return a.second > b.second; });
        
        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(freqVec[i].first);
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
    vector<int> nums1 = {1, 1, 1, 2, 2, 3};
    auto result1 = sol.topKFrequent(nums1, 2);
    cout << "Test 1 [1,1,1,2,2,3] k=2: ";
    printVector(result1);
    // Expected: [1, 2] (any order)
    
    // Test Case 2: k = 1
    vector<int> nums2 = {1};
    auto result2 = sol.topKFrequent(nums2, 1);
    cout << "Test 2 [1] k=1: ";
    printVector(result2);
    // Expected: [1]
    
    // Test Case 3: All same frequency
    vector<int> nums3 = {1, 2, 3, 4};
    auto result3 = sol.topKFrequent(nums3, 2);
    cout << "Test 3 [1,2,3,4] k=2: ";
    printVector(result3);
    // Expected: any 2 elements
    
    // Test Case 4: Negative numbers
    vector<int> nums4 = {-1, -1, -2, -2, -2, -3};
    auto result4 = sol.topKFrequent(nums4, 2);
    cout << "Test 4 [-1,-1,-2,-2,-2,-3] k=2: ";
    printVector(result4);
    // Expected: [-2, -1] (any order)
    
    // Test Case 5: k equals unique elements
    vector<int> nums5 = {1, 2};
    auto result5 = sol.topKFrequent(nums5, 2);
    cout << "Test 5 [1,2] k=2: ";
    printVector(result5);
    // Expected: [1, 2] (any order)
    
    return 0;
}

