"""
Problem: LRU Cache (LeetCode 146)

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:
- LRUCache(int capacity) Initialize the cache with positive size capacity.
- int get(int key) Return the value if key exists, otherwise return -1.
- void put(int key, int value) Update or insert value. Evict LRU key if capacity exceeded.

Both get and put must run in O(1) average time complexity.

Time Complexity: O(1) for both get and put
Space Complexity: O(capacity)
"""

class DLinkedNode:
    """Doubly linked list node"""
    def __init__(self, key=0, value=0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}  # key -> node
        
        # Dummy head and tail
        self.head = DLinkedNode()
        self.tail = DLinkedNode()
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _remove_node(self, node: DLinkedNode) -> None:
        """Remove node from its current position"""
        node.prev.next = node.next
        node.next.prev = node.prev
    
    def _add_to_head(self, node: DLinkedNode) -> None:
        """Add node right after head (most recently used)"""
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node
    
    def _move_to_head(self, node: DLinkedNode) -> None:
        """Move existing node to head"""
        self._remove_node(node)
        self._add_to_head(node)
    
    def _remove_tail(self) -> DLinkedNode:
        """Remove and return the LRU node (before tail)"""
        lru = self.tail.prev
        self._remove_node(lru)
        return lru
    
    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        
        # Move to head (mark as most recently used)
        node = self.cache[key]
        self._move_to_head(node)
        return node.value
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # Key exists, update value and move to head
            node = self.cache[key]
            node.value = value
            self._move_to_head(node)
        else:
            # New key
            new_node = DLinkedNode(key, value)
            self.cache[key] = new_node
            self._add_to_head(new_node)
            
            if len(self.cache) > self.capacity:
                # Evict LRU
                lru = self._remove_tail()
                del self.cache[lru.key]


# Alternative using OrderedDict (Python-specific)
from collections import OrderedDict

class LRUCacheOrderedDict:
    """LRU Cache using Python's OrderedDict"""
    
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        
        # Move to end (most recently used)
        self.cache.move_to_end(key)
        return self.cache[key]
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache.move_to_end(key)
        
        self.cache[key] = value
        
        if len(self.cache) > self.capacity:
            # Remove first item (LRU)
            self.cache.popitem(last=False)


if __name__ == "__main__":
    # Test case 1: Basic operations
    cache = LRUCache(2)
    
    cache.put(1, 1)
    print("put(1, 1)")
    
    cache.put(2, 2)
    print("put(2, 2)")
    
    print(f"get(1): {cache.get(1)} (expected: 1)")
    assert cache.get(1) == 1
    
    cache.put(3, 3)  # Evicts key 2
    print("put(3, 3) - evicts key 2")
    
    print(f"get(2): {cache.get(2)} (expected: -1)")
    assert cache.get(2) == -1
    
    cache.put(4, 4)  # Evicts key 1
    print("put(4, 4) - evicts key 1")
    
    print(f"get(1): {cache.get(1)} (expected: -1)")
    assert cache.get(1) == -1
    
    print(f"get(3): {cache.get(3)} (expected: 3)")
    assert cache.get(3) == 3
    
    print(f"get(4): {cache.get(4)} (expected: 4)")
    assert cache.get(4) == 4
    
    # Test case 2: Update existing key
    print("\nTest case 2: Update existing key")
    cache2 = LRUCache(2)
    cache2.put(1, 1)
    cache2.put(2, 2)
    cache2.put(1, 10)  # Update key 1
    print(f"get(1) after update: {cache2.get(1)} (expected: 10)")
    assert cache2.get(1) == 10
    
    # Test case 3: Capacity 1
    print("\nTest case 3: Capacity 1")
    cache3 = LRUCache(1)
    cache3.put(1, 1)
    cache3.put(2, 2)  # Evicts 1
    print(f"get(1): {cache3.get(1)} (expected: -1)")
    print(f"get(2): {cache3.get(2)} (expected: 2)")
    assert cache3.get(1) == -1
    assert cache3.get(2) == 2
    
    # Test OrderedDict implementation
    print("\nTest OrderedDict implementation:")
    cache_od = LRUCacheOrderedDict(2)
    cache_od.put(1, 1)
    cache_od.put(2, 2)
    print(f"get(1): {cache_od.get(1)}")
    cache_od.put(3, 3)
    print(f"get(2): {cache_od.get(2)} (expected: -1)")
    
    print("\nAll test cases passed!")

