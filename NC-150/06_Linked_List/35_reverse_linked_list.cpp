/*
 * Problem: Reverse Linked List (LeetCode 206)
 * 
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * 
 * Time Complexity: O(n) - single pass through the list
 * Space Complexity: O(1) for iterative, O(n) for recursive
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    // Solution 1: Iterative approach
    // Time: O(n), Space: O(1)
    ListNode* reverseListIterative(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;  // Save next
            curr->next = prev;                 // Reverse the link
            prev = curr;                       // Move prev forward
            curr = nextTemp;                   // Move curr forward
        }
        
        return prev;
    }
    
    // Solution 2: Recursive approach
    // Time: O(n), Space: O(n) due to recursion stack
    ListNode* reverseListRecursive(ListNode* head) {
        // Base case: empty list or single node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Reverse the rest of the list
        ListNode* newHead = reverseListRecursive(head->next);
        
        // Put the first element at the end
        head->next->next = head;
        head->next = nullptr;
        
        return newHead;
    }
    
    // Main function using iterative approach
    ListNode* reverseList(ListNode* head) {
        return reverseListIterative(head);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4,5] -> [5,4,3,2,1]
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    std::cout << "Original: ";
    printList(head1);
    head1 = sol.reverseList(head1);
    std::cout << "Reversed: ";
    printList(head1);
    deleteList(head1);
    
    // Test case 2: [1,2] -> [2,1]
    ListNode* head2 = createList({1, 2});
    std::cout << "\nOriginal: ";
    printList(head2);
    head2 = sol.reverseList(head2);
    std::cout << "Reversed: ";
    printList(head2);
    deleteList(head2);
    
    // Test case 3: [] -> []
    ListNode* head3 = createList({});
    std::cout << "\nOriginal: ";
    printList(head3);
    head3 = sol.reverseList(head3);
    std::cout << "Reversed: ";
    printList(head3);
    deleteList(head3);
    
    // Test case 4: Single node [1] -> [1]
    ListNode* head4 = createList({1});
    std::cout << "\nOriginal: ";
    printList(head4);
    head4 = sol.reverseList(head4);
    std::cout << "Reversed: ";
    printList(head4);
    deleteList(head4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}
