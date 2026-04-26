/*
 * Problem: Remove Nth Node From End of List (LeetCode 19)
 * 
 * Given the head of a linked list, remove the nth node from the end of the list
 * and return its head.
 * 
 * Time Complexity: O(n) - single pass
 * Space Complexity: O(1)
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    // Solution: Two pointers with gap of n
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Dummy node handles edge case of removing the head
        ListNode dummy(0);
        dummy.next = head;
        
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;
        
        // Move fast pointer n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }
        
        // Move both pointers until fast reaches the end
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        
        // slow is now just before the node to be removed
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;
        
        return dummy.next;
    }
    
    // Alternative: Two-pass approach (find length first)
    ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
        // First pass: count nodes
        int length = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }
        
        // Handle removing the head
        if (n == length) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        
        // Second pass: find the node before the one to remove
        curr = head;
        for (int i = 0; i < length - n - 1; i++) {
            curr = curr->next;
        }
        
        ListNode* toDelete = curr->next;
        curr->next = curr->next->next;
        delete toDelete;
        
        return head;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4,5], n=2 -> [1,2,3,5]
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    std::cout << "Original: ";
    printList(head1);
    head1 = sol.removeNthFromEnd(head1, 2);
    std::cout << "After removing 2nd from end: ";
    printList(head1);
    deleteList(head1);
    
    // Test case 2: [1], n=1 -> []
    ListNode* head2 = createList({1});
    std::cout << "\nOriginal: ";
    printList(head2);
    head2 = sol.removeNthFromEnd(head2, 1);
    std::cout << "After removing 1st from end: ";
    printList(head2);
    deleteList(head2);
    
    // Test case 3: [1,2], n=1 -> [1]
    ListNode* head3 = createList({1, 2});
    std::cout << "\nOriginal: ";
    printList(head3);
    head3 = sol.removeNthFromEnd(head3, 1);
    std::cout << "After removing 1st from end: ";
    printList(head3);
    deleteList(head3);
    
    // Test case 4: [1,2], n=2 -> [2] (remove head)
    ListNode* head4 = createList({1, 2});
    std::cout << "\nOriginal: ";
    printList(head4);
    head4 = sol.removeNthFromEnd(head4, 2);
    std::cout << "After removing 2nd from end (head): ";
    printList(head4);
    deleteList(head4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

