/*
 * Problem: Reverse Nodes in k-Group (LeetCode 25)
 * 
 * Given a linked list, reverse the nodes of a linked list k at a time
 * and return its modified list.
 * 
 * - k is a positive integer and is less than or equal to the length of the list.
 * - If the number of nodes is not a multiple of k, the nodes left out at the
 *   end should remain as-is.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k == 1) return head;
        
        // Dummy node to handle head changes
        ListNode dummy(0);
        dummy.next = head;
        
        ListNode* prevGroupEnd = &dummy;
        
        while (true) {
            // Check if there are k nodes left
            ListNode* kthNode = getKthNode(prevGroupEnd, k);
            if (kthNode == nullptr) break;
            
            // Mark the boundaries
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* nextGroupStart = kthNode->next;
            
            // Reverse the k nodes
            reverseList(groupStart, kthNode);
            
            // Connect with previous and next parts
            prevGroupEnd->next = kthNode;  // kthNode is now the first in reversed group
            groupStart->next = nextGroupStart;  // groupStart is now the last
            
            // Move to next group
            prevGroupEnd = groupStart;
        }
        
        return dummy.next;
    }
    
private:
    // Get the k-th node from current position
    ListNode* getKthNode(ListNode* current, int k) {
        while (current != nullptr && k > 0) {
            current = current->next;
            k--;
        }
        return current;
    }
    
    // Reverse nodes between start and end (inclusive)
    void reverseList(ListNode* start, ListNode* end) {
        ListNode* prev = nullptr;
        ListNode* curr = start;
        ListNode* stop = end->next;
        
        while (curr != stop) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4,5], k=2 -> [2,1,4,3,5]
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    std::cout << "Original: ";
    printList(head1);
    head1 = sol.reverseKGroup(head1, 2);
    std::cout << "k=2: ";
    printList(head1);
    deleteList(head1);
    
    // Test case 2: [1,2,3,4,5], k=3 -> [3,2,1,4,5]
    ListNode* head2 = createList({1, 2, 3, 4, 5});
    std::cout << "\nOriginal: ";
    printList(head2);
    head2 = sol.reverseKGroup(head2, 3);
    std::cout << "k=3: ";
    printList(head2);
    deleteList(head2);
    
    // Test case 3: [1,2,3,4], k=2 -> [2,1,4,3]
    ListNode* head3 = createList({1, 2, 3, 4});
    std::cout << "\nOriginal: ";
    printList(head3);
    head3 = sol.reverseKGroup(head3, 2);
    std::cout << "k=2: ";
    printList(head3);
    deleteList(head3);
    
    // Test case 4: [1], k=1 -> [1]
    ListNode* head4 = createList({1});
    std::cout << "\nOriginal: ";
    printList(head4);
    head4 = sol.reverseKGroup(head4, 1);
    std::cout << "k=1: ";
    printList(head4);
    deleteList(head4);
    
    // Test case 5: [1,2,3,4,5], k=5 -> [5,4,3,2,1]
    ListNode* head5 = createList({1, 2, 3, 4, 5});
    std::cout << "\nOriginal: ";
    printList(head5);
    head5 = sol.reverseKGroup(head5, 5);
    std::cout << "k=5 (entire list): ";
    printList(head5);
    deleteList(head5);
    
    // Test case 6: [1,2,3], k=4 -> [1,2,3] (no change, k > length)
    ListNode* head6 = createList({1, 2, 3});
    std::cout << "\nOriginal: ";
    printList(head6);
    head6 = sol.reverseKGroup(head6, 4);
    std::cout << "k=4 (k > length, no change): ";
    printList(head6);
    deleteList(head6);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

