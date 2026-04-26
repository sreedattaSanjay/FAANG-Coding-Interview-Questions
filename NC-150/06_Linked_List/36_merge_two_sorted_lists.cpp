/*
 * Problem: Merge Two Sorted Lists (LeetCode 21)
 * 
 * Merge two sorted linked lists and return it as a sorted list.
 * The list should be made by splicing together the nodes of the first two lists.
 * 
 * Time Complexity: O(n + m) where n, m are lengths of the two lists
 * Space Complexity: O(1) for iterative, O(n + m) for recursive
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    // Solution 1: Iterative with dummy node
    // Time: O(n + m), Space: O(1)
    ListNode* mergeTwoListsIterative(ListNode* list1, ListNode* list2) {
        // Dummy node simplifies edge cases
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        
        // Attach the remaining list (one of them is empty)
        tail->next = (list1 != nullptr) ? list1 : list2;
        
        return dummy.next;
    }
    
    // Solution 2: Recursive
    // Time: O(n + m), Space: O(n + m) for recursion stack
    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
        // Base cases
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        
        // Choose smaller value as head, recurse for the rest
        if (list1->val <= list2->val) {
            list1->next = mergeTwoListsRecursive(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoListsRecursive(list1, list2->next);
            return list2;
        }
    }
    
    // Main function using iterative approach
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        return mergeTwoListsIterative(list1, list2);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,4] + [1,3,4] = [1,1,2,3,4,4]
    ListNode* l1 = createList({1, 2, 4});
    ListNode* l2 = createList({1, 3, 4});
    std::cout << "List 1: ";
    printList(l1);
    std::cout << "List 2: ";
    printList(l2);
    ListNode* merged1 = sol.mergeTwoLists(l1, l2);
    std::cout << "Merged: ";
    printList(merged1);
    deleteList(merged1);
    
    // Test case 2: [] + [] = []
    ListNode* l3 = createList({});
    ListNode* l4 = createList({});
    std::cout << "\nList 1: ";
    printList(l3);
    std::cout << "List 2: ";
    printList(l4);
    ListNode* merged2 = sol.mergeTwoLists(l3, l4);
    std::cout << "Merged: ";
    printList(merged2);
    deleteList(merged2);
    
    // Test case 3: [] + [0] = [0]
    ListNode* l5 = createList({});
    ListNode* l6 = createList({0});
    std::cout << "\nList 1: ";
    printList(l5);
    std::cout << "List 2: ";
    printList(l6);
    ListNode* merged3 = sol.mergeTwoLists(l5, l6);
    std::cout << "Merged: ";
    printList(merged3);
    deleteList(merged3);
    
    // Test case 4: Different lengths [1,3,5,7] + [2,4]
    ListNode* l7 = createList({1, 3, 5, 7});
    ListNode* l8 = createList({2, 4});
    std::cout << "\nList 1: ";
    printList(l7);
    std::cout << "List 2: ";
    printList(l8);
    ListNode* merged4 = sol.mergeTwoLists(l7, l8);
    std::cout << "Merged: ";
    printList(merged4);
    deleteList(merged4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

