/*
 * LeetCode 981: Time Based Key-Value Store
 * https://leetcode.com/problems/time-based-key-value-store/
 * 
 * Design a data structure that stores key-value pairs with timestamps.
 * 
 * Time Complexity: Set O(1), Get O(log n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> store;
    
public:
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if (store.find(key) == store.end()) return "";
        
        auto& vec = store[key];
        int left = 0, right = vec.size() - 1;
        string result = "";
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (vec[mid].first <= timestamp) {
                result = vec[mid].second;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};

int main() {
    TimeMap tm;
    
    tm.set("foo", "bar", 1);
    cout << "get('foo', 1): " << tm.get("foo", 1) << endl;  // bar
    cout << "get('foo', 3): " << tm.get("foo", 3) << endl;  // bar
    
    tm.set("foo", "bar2", 4);
    cout << "get('foo', 4): " << tm.get("foo", 4) << endl;  // bar2
    cout << "get('foo', 5): " << tm.get("foo", 5) << endl;  // bar2
    
    return 0;
}

