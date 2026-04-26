# LRU Cache - Detailed Explanation

## Problem Statement
Design a data structure that follows LRU (Least Recently Used) cache constraints:
- `get(key)`: Return value if key exists, else -1
- `put(key, value)`: Update or insert. Evict LRU item if over capacity

Both operations must be **O(1)** time.

## Key Insight: Two Data Structures

To achieve O(1) for both operations, we need:
1. **Hash Map**: O(1) lookup by key
2. **Doubly Linked List**: O(1) add/remove from any position

### Why Doubly Linked List?
- Need to remove from middle (when accessed)
- Need to add to front (mark as recently used)
- Need to remove from back (evict LRU)
- All these are O(1) with doubly linked list

## Data Structure Design

```
Hash Map: { key -> node pointer }

Doubly Linked List:
[HEAD] <-> [Most Recent] <-> ... <-> [Least Recent] <-> [TAIL]
  ↑                                                        ↑
dummy                                                    dummy
```

- **Head side**: Most recently used
- **Tail side**: Least recently used
- Dummy nodes simplify edge cases

## Operations

### get(key)
1. If key not in map, return -1
2. Get node from map
3. Move node to head (mark as recently used)
4. Return value

### put(key, value)
1. If key exists:
   - Update value
   - Move to head
2. If key doesn't exist:
   - Create new node
   - Add to map and list head
   - If over capacity, remove LRU (tail's prev)

## Visual Walkthrough

```
Capacity: 2

put(1, 1):
  Map: {1: Node1}
  List: [HEAD] <-> [1] <-> [TAIL]

put(2, 2):
  Map: {1: Node1, 2: Node2}
  List: [HEAD] <-> [2] <-> [1] <-> [TAIL]

get(1): returns 1, moves 1 to front
  List: [HEAD] <-> [1] <-> [2] <-> [TAIL]

put(3, 3): evicts key 2 (LRU)
  Map: {1: Node1, 3: Node3}
  List: [HEAD] <-> [3] <-> [1] <-> [TAIL]

get(2): returns -1 (evicted)
```

## Code Template

```python
class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = {}  # key -> node
        self.head = Node()  # Dummy
        self.tail = Node()  # Dummy
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _remove(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev
    
    def _add_to_head(self, node):
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node
    
    def get(self, key):
        if key not in self.cache:
            return -1
        node = self.cache[key]
        self._remove(node)
        self._add_to_head(node)
        return node.value
    
    def put(self, key, value):
        if key in self.cache:
            node = self.cache[key]
            node.value = value
            self._remove(node)
            self._add_to_head(node)
        else:
            node = Node(key, value)
            self.cache[key] = node
            self._add_to_head(node)
            if len(self.cache) > self.capacity:
                lru = self.tail.prev
                self._remove(lru)
                del self.cache[lru.key]
```

## Complexity Analysis
- **Time**: O(1) for both get and put
  - Hash map: O(1) lookup
  - Linked list operations: O(1)
- **Space**: O(capacity) - at most capacity nodes

## Edge Cases

| Case | Scenario | Handling |
|------|----------|----------|
| Get missing key | `get(5)` when 5 not in cache | Return -1 |
| Update existing | `put(1, 10)` when 1 exists | Update value, move to head |
| Capacity 1 | Every put evicts | Only one item ever in cache |
| Same key twice | `put(1,1), put(1,1)` | Just moves to head |

## Common Mistakes

1. **Forgetting to update map on eviction**: Must delete key when removing node
2. **Node doesn't store key**: Need key to delete from map when evicting
3. **Wrong order of operations**: Update pointers carefully
4. **Not using dummy nodes**: Makes head/tail handling complex

## Interview Tips

1. **Draw the structure**: Show hash map + doubly linked list
2. **Explain why both**: Hash map for lookup, list for ordering
3. **Mention dummy nodes**: Shows you know about edge case handling
4. **Consider alternatives**: In Python, mention `OrderedDict`

## Python Alternative: OrderedDict

```python
from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key):
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key)
        return self.cache[key]
    
    def put(self, key, value):
        if key in self.cache:
            self.cache.move_to_end(key)
        self.cache[key] = value
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)
```

Note: In interviews, implement the full solution to show data structure knowledge.

## Related Problems
- LFU Cache (Least Frequently Used)
- Design Browser History
- All O(1) Data Structure

