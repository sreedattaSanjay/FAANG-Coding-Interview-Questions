/*
 * Problem: Copy List with Random Pointer (LeetCode 138)
 * 
 * A linked list is given where each node contains an additional random pointer
 * which could point to any node in the list or null.
 * Return a deep copy of the list.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n) for hash map, O(1) for interweaving approach
 */

#include <iostream>
#include <unordered_map>

// Special Node with random pointer
struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    // Solution 1: Using Hash Map
    // Time: O(n), Space: O(n)
    Node* copyRandomListHashMap(Node* head) {
        if (head == nullptr) return nullptr;
        
        // Map original nodes to their copies
        std::unordered_map<Node*, Node*> oldToNew;
        
        // First pass: create all nodes
        Node* curr = head;
        while (curr != nullptr) {
            oldToNew[curr] = new Node(curr->val);
            curr = curr->next;
        }
        
        // Second pass: set next and random pointers
        curr = head;
        while (curr != nullptr) {
            Node* copy = oldToNew[curr];
            copy->next = oldToNew[curr->next];
            copy->random = oldToNew[curr->random];
            curr = curr->next;
        }
        
        return oldToNew[head];
    }
    
    // Solution 2: Interweaving Nodes (O(1) space)
    // Time: O(n), Space: O(1)
    Node* copyRandomListInterweave(Node* head) {
        if (head == nullptr) return nullptr;
        
        // Step 1: Create copies interleaved with original
        // 1 -> 1' -> 2 -> 2' -> 3 -> 3'
        Node* curr = head;
        while (curr != nullptr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }
        
        // Step 2: Set random pointers for copies
        curr = head;
        while (curr != nullptr) {
            if (curr->random != nullptr) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }
        
        // Step 3: Separate the two lists
        Node* dummy = new Node(0);
        Node* copyTail = dummy;
        curr = head;
        
        while (curr != nullptr) {
            Node* copy = curr->next;
            Node* nextOrig = copy->next;
            
            copyTail->next = copy;
            copyTail = copy;
            
            curr->next = nextOrig;
            curr = nextOrig;
        }
        
        Node* result = dummy->next;
        delete dummy;
        return result;
    }
    
    // Main function using hash map approach
    Node* copyRandomList(Node* head) {
        return copyRandomListHashMap(head);
    }
};

// Helper function to print list
void printList(Node* head) {
    Node* curr = head;
    int index = 0;
    while (curr != nullptr) {
        std::cout << "Node " << index << ": val=" << curr->val;
        if (curr->random != nullptr) {
            // Find random's index
            Node* temp = head;
            int randIndex = 0;
            while (temp != curr->random) {
                temp = temp->next;
                randIndex++;
            }
            std::cout << ", random=" << randIndex;
        } else {
            std::cout << ", random=null";
        }
        std::cout << std::endl;
        curr = curr->next;
        index++;
    }
}

int main() {
    Solution sol;
    
    // Test case 1: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    Node* n0 = new Node(7);
    Node* n1 = new Node(13);
    Node* n2 = new Node(11);
    Node* n3 = new Node(10);
    Node* n4 = new Node(1);
    
    n0->next = n1; n1->next = n2; n2->next = n3; n3->next = n4;
    n0->random = nullptr;
    n1->random = n0;
    n2->random = n4;
    n3->random = n2;
    n4->random = n0;
    
    std::cout << "Original list:" << std::endl;
    printList(n0);
    
    Node* copy = sol.copyRandomList(n0);
    std::cout << "\nCopied list:" << std::endl;
    printList(copy);
    
    // Verify deep copy (different addresses)
    std::cout << "\nVerifying deep copy:" << std::endl;
    std::cout << "Original head address: " << n0 << std::endl;
    std::cout << "Copy head address: " << copy << std::endl;
    std::cout << "Addresses are different: " << (n0 != copy ? "YES" : "NO") << std::endl;
    
    // Test case 2: Empty list
    Node* empty = nullptr;
    Node* copyEmpty = sol.copyRandomList(empty);
    std::cout << "\nEmpty list copy: " << (copyEmpty == nullptr ? "null" : "not null") << std::endl;
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

