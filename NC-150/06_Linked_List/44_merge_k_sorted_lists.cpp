/*
 * Problem: Merge k Sorted Lists (LeetCode 23)
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted 
 * in ascending order. Merge all the linked-lists into one sorted linked-list.
 * 
 * Time Complexity: O(N log k) where N is total nodes, k is number of lists
 * Space Complexity: O(log k) for divide and conquer, O(k) for heap
 */

#include <iostream>
#include <vector>
#include <queue>
#include "list_node.h"

class Solution {
public:
    // Solution 1: Divide and Conquer
    // Time: O(N log k), Space: O(log k) recursion
    ListNode* mergeKListsDivideConquer(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeRange(lists, 0, lists.size() - 1);
    }
    
    // Solution 2: Min Heap (Priority Queue)
    // Time: O(N log k), Space: O(k)
    ListNode* mergeKListsHeap(std::vector<ListNode*>& lists) {
        // Custom comparator for min-heap
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val;  // Min-heap
        };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(compare)> pq(compare);
        
        // Add first node of each list to heap
        for (ListNode* list : lists) {
            if (list != nullptr) {
                pq.push(list);
            }
        }
        
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (!pq.empty()) {
            // Get smallest node
            ListNode* smallest = pq.top();
            pq.pop();
            
            // Add to result
            tail->next = smallest;
            tail = tail->next;
            
            // Add next node from the same list
            if (smallest->next != nullptr) {
                pq.push(smallest->next);
            }
        }
        
        return dummy.next;
    }
    
    // Main function using divide and conquer
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        return mergeKListsDivideConquer(lists);
    }
    
private:
    ListNode* mergeRange(std::vector<ListNode*>& lists, int left, int right) {
        if (left == right) return lists[left];
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        ListNode* leftMerged = mergeRange(lists, left, mid);
        ListNode* rightMerged = mergeRange(lists, mid + 1, right);
        
        return mergeTwoLists(leftMerged, rightMerged);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [[1,4,5],[1,3,4],[2,6]]
    std::vector<ListNode*> lists1 = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})
    };
    std::cout << "Lists:" << std::endl;
    for (int i = 0; i < lists1.size(); i++) {
        std::cout << "  List " << i << ": ";
        printList(lists1[i]);
    }
    ListNode* merged1 = sol.mergeKLists(lists1);
    std::cout << "Merged: ";
    printList(merged1);
    deleteList(merged1);
    
    // Test case 2: Empty list
    std::vector<ListNode*> lists2 = {};
    ListNode* merged2 = sol.mergeKLists(lists2);
    std::cout << "\nEmpty input: ";
    printList(merged2);
    
    // Test case 3: [[]]
    std::vector<ListNode*> lists3 = {nullptr};
    ListNode* merged3 = sol.mergeKLists(lists3);
    std::cout << "\n[[]] input: ";
    printList(merged3);
    
    // Test case 4: Single list
    std::vector<ListNode*> lists4 = {createList({1, 2, 3})};
    std::cout << "\nSingle list: ";
    ListNode* merged4 = sol.mergeKLists(lists4);
    printList(merged4);
    deleteList(merged4);
    
    // Test heap solution
    std::vector<ListNode*> lists5 = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})
    };
    ListNode* merged5 = sol.mergeKListsHeap(lists5);
    std::cout << "\nHeap solution: ";
    printList(merged5);
    deleteList(merged5);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

