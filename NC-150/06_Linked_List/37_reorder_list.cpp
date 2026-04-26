/*
 * Problem: Reorder List (LeetCode 143)
 * 
 * Given a singly linked list L: L0 → L1 → … → Ln-1 → Ln
 * Reorder it to: L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
 * 
 * You may not modify the values in the list's nodes, only nodes may be changed.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        
        // Step 1: Find the middle of the list (slow-fast pointer)
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Step 2: Reverse the second half
        ListNode* secondHalf = reverseList(slow->next);
        slow->next = nullptr;  // Cut the first half
        
        // Step 3: Merge the two halves alternately
        ListNode* firstHalf = head;
        while (secondHalf != nullptr) {
            ListNode* temp1 = firstHalf->next;
            ListNode* temp2 = secondHalf->next;
            
            firstHalf->next = secondHalf;
            secondHalf->next = temp1;
            
            firstHalf = temp1;
            secondHalf = temp2;
        }
    }
    
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4] -> [1,4,2,3]
    ListNode* head1 = createList({1, 2, 3, 4});
    std::cout << "Original: ";
    printList(head1);
    sol.reorderList(head1);
    std::cout << "Reordered: ";
    printList(head1);
    deleteList(head1);
    
    // Test case 2: [1,2,3,4,5] -> [1,5,2,4,3]
    ListNode* head2 = createList({1, 2, 3, 4, 5});
    std::cout << "\nOriginal: ";
    printList(head2);
    sol.reorderList(head2);
    std::cout << "Reordered: ";
    printList(head2);
    deleteList(head2);
    
    // Test case 3: [1] -> [1]
    ListNode* head3 = createList({1});
    std::cout << "\nOriginal: ";
    printList(head3);
    sol.reorderList(head3);
    std::cout << "Reordered: ";
    printList(head3);
    deleteList(head3);
    
    // Test case 4: [1,2] -> [1,2]
    ListNode* head4 = createList({1, 2});
    std::cout << "\nOriginal: ";
    printList(head4);
    sol.reorderList(head4);
    std::cout << "Reordered: ";
    printList(head4);
    deleteList(head4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

