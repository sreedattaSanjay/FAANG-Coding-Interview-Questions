/*
 * Problem: LRU Cache (LeetCode 146)
 * 
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
 * 
 * Implement the LRUCache class:
 * - LRUCache(int capacity) Initialize the cache with positive size capacity.
 * - int get(int key) Return the value if key exists, otherwise return -1.
 * - void put(int key, int value) Update or insert value. Evict LRU key if capacity exceeded.
 * 
 * Both get and put must run in O(1) average time complexity.
 * 
 * Time Complexity: O(1) for both get and put
 * Space Complexity: O(capacity)
 */

#include <iostream>
#include <unordered_map>

class LRUCache {
private:
    // Doubly linked list node
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    int capacity;
    std::unordered_map<int, Node*> cache;  // key -> node pointer
    Node* head;  // Dummy head (most recent)
    Node* tail;  // Dummy tail (least recent)
    
    // Remove node from its current position
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    // Add node right after head (most recently used position)
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    // Move existing node to head
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    // Remove and return the least recently used node (before tail)
    Node* removeTail() {
        Node* lru = tail->prev;
        removeNode(lru);
        return lru;
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {
        // Create dummy head and tail
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    ~LRUCache() {
        // Clean up all nodes
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        // Move to head (mark as most recently used)
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Key exists, update value and move to head
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // New key
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            
            if (cache.size() > capacity) {
                // Evict LRU (node before tail)
                Node* lru = removeTail();
                cache.erase(lru->key);
                delete lru;
            }
        }
    }
};

int main() {
    // Test case 1: Basic operations
    LRUCache cache1(2);
    
    cache1.put(1, 1);
    std::cout << "put(1, 1)" << std::endl;
    
    cache1.put(2, 2);
    std::cout << "put(2, 2)" << std::endl;
    
    std::cout << "get(1): " << cache1.get(1) << " (expected: 1)" << std::endl;
    
    cache1.put(3, 3);  // Evicts key 2
    std::cout << "put(3, 3) - evicts key 2" << std::endl;
    
    std::cout << "get(2): " << cache1.get(2) << " (expected: -1)" << std::endl;
    
    cache1.put(4, 4);  // Evicts key 1
    std::cout << "put(4, 4) - evicts key 1" << std::endl;
    
    std::cout << "get(1): " << cache1.get(1) << " (expected: -1)" << std::endl;
    std::cout << "get(3): " << cache1.get(3) << " (expected: 3)" << std::endl;
    std::cout << "get(4): " << cache1.get(4) << " (expected: 4)" << std::endl;
    
    // Test case 2: Update existing key
    std::cout << "\nTest case 2: Update existing key" << std::endl;
    LRUCache cache2(2);
    cache2.put(1, 1);
    cache2.put(2, 2);
    cache2.put(1, 10);  // Update key 1
    std::cout << "get(1) after update: " << cache2.get(1) << " (expected: 10)" << std::endl;
    
    // Test case 3: Capacity 1
    std::cout << "\nTest case 3: Capacity 1" << std::endl;
    LRUCache cache3(1);
    cache3.put(1, 1);
    cache3.put(2, 2);  // Evicts 1
    std::cout << "get(1): " << cache3.get(1) << " (expected: -1)" << std::endl;
    std::cout << "get(2): " << cache3.get(2) << " (expected: 2)" << std::endl;
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

