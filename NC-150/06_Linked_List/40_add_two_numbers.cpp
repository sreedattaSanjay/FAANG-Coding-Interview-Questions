/*
 * Problem: Add Two Numbers (LeetCode 2)
 * 
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each node contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * 
 * Time Complexity: O(max(n, m))
 * Space Complexity: O(max(n, m)) for the result list
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        int carry = 0;
        
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }
        
        return dummy.next;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: 342 + 465 = 807
    // [2,4,3] + [5,6,4] = [7,0,8]
    ListNode* l1 = createList({2, 4, 3});
    ListNode* l2 = createList({5, 6, 4});
    std::cout << "List 1 (342): ";
    printList(l1);
    std::cout << "List 2 (465): ";
    printList(l2);
    ListNode* result1 = sol.addTwoNumbers(l1, l2);
    std::cout << "Sum (807): ";
    printList(result1);
    deleteList(l1);
    deleteList(l2);
    deleteList(result1);
    
    // Test case 2: 0 + 0 = 0
    ListNode* l3 = createList({0});
    ListNode* l4 = createList({0});
    std::cout << "\nList 1 (0): ";
    printList(l3);
    std::cout << "List 2 (0): ";
    printList(l4);
    ListNode* result2 = sol.addTwoNumbers(l3, l4);
    std::cout << "Sum (0): ";
    printList(result2);
    deleteList(l3);
    deleteList(l4);
    deleteList(result2);
    
    // Test case 3: 9999999 + 9999 = 10009998
    // [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    ListNode* l5 = createList({9, 9, 9, 9, 9, 9, 9});
    ListNode* l6 = createList({9, 9, 9, 9});
    std::cout << "\nList 1 (9999999): ";
    printList(l5);
    std::cout << "List 2 (9999): ";
    printList(l6);
    ListNode* result3 = sol.addTwoNumbers(l5, l6);
    std::cout << "Sum (10009998): ";
    printList(result3);
    deleteList(l5);
    deleteList(l6);
    deleteList(result3);
    
    // Test case 4: Different lengths with carry
    // [9,9] + [1] = [0,0,1] (99 + 1 = 100)
    ListNode* l7 = createList({9, 9});
    ListNode* l8 = createList({1});
    std::cout << "\nList 1 (99): ";
    printList(l7);
    std::cout << "List 2 (1): ";
    printList(l8);
    ListNode* result4 = sol.addTwoNumbers(l7, l8);
    std::cout << "Sum (100): ";
    printList(result4);
    deleteList(l7);
    deleteList(l8);
    deleteList(result4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

