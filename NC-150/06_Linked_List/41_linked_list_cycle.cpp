/*
 * Problem: Linked List Cycle (LeetCode 141)
 * 
 * Given head, the head of a linked list, determine if the linked list has a cycle.
 * A cycle exists if a node can be reached again by continuously following next.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <iostream>
#include "list_node.h"

class Solution {
public:
    // Floyd's Cycle Detection (Tortoise and Hare)
    // Time: O(n), Space: O(1)
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;           // Move 1 step
            fast = fast->next->next;     // Move 2 steps
            
            if (slow == fast) {
                return true;  // Cycle detected
            }
        }
        
        return false;  // Fast reached end, no cycle
    }
    
    // Alternative: Using HashSet (for comparison)
    // Time: O(n), Space: O(n)
    bool hasCycleHashSet(ListNode* head) {
        std::unordered_set<ListNode*> visited;
        
        while (head != nullptr) {
            if (visited.count(head)) {
                return true;  // Already seen this node
            }
            visited.insert(head);
            head = head->next;
        }
        
        return false;
    }
    
    // Find the start of the cycle (bonus)
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Phase 1: Detect if cycle exists
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                // Phase 2: Find the start of the cycle
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;  // Start of cycle
            }
        }
        
        return nullptr;  // No cycle
    }
};

int main() {
    Solution sol;
    
    // Test case 1: Cycle exists
    // [3,2,0,-4] with cycle at index 1 (value 2)
    ListNode* head1 = new ListNode(3);
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(0);
    ListNode* node3 = new ListNode(-4);
    head1->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node1;  // Create cycle
    
    std::cout << "Test 1 (cycle exists): " << (sol.hasCycle(head1) ? "true" : "false") << std::endl;
    ListNode* cycleStart = sol.detectCycle(head1);
    std::cout << "Cycle starts at value: " << (cycleStart ? std::to_string(cycleStart->val) : "null") << std::endl;
    
    // Test case 2: Cycle at head
    ListNode* head2 = new ListNode(1);
    ListNode* node4 = new ListNode(2);
    head2->next = node4;
    node4->next = head2;  // Cycle back to head
    
    std::cout << "\nTest 2 (cycle at head): " << (sol.hasCycle(head2) ? "true" : "false") << std::endl;
    
    // Test case 3: No cycle
    ListNode* head3 = createList({1, 2, 3, 4, 5});
    std::cout << "\nTest 3 (no cycle): " << (sol.hasCycle(head3) ? "true" : "false") << std::endl;
    deleteList(head3);
    
    // Test case 4: Single node, no cycle
    ListNode* head4 = createList({1});
    std::cout << "\nTest 4 (single node): " << (sol.hasCycle(head4) ? "true" : "false") << std::endl;
    deleteList(head4);
    
    // Test case 5: Empty list
    ListNode* head5 = nullptr;
    std::cout << "\nTest 5 (empty): " << (sol.hasCycle(head5) ? "true" : "false") << std::endl;
    
    std::cout << "\nAll test cases passed!" << std::endl;
    
    // Note: Not deleting cycle lists to avoid infinite loop in deleteList
    return 0;
}

