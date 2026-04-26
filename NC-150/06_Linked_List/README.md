# Linked List Problems

This folder contains solutions to the **Linked List** category from NeetCode 150.

## Problem List

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Reverse Linked List](01_reverse_linked_list.cpp) | Easy | Iterative/Recursive |
| 2 | [Merge Two Sorted Lists](02_merge_two_sorted_lists.cpp) | Easy | Two Pointers |
| 3 | [Reorder List](03_reorder_list.cpp) | Medium | Find Middle + Reverse + Merge |
| 4 | [Remove Nth Node From End](04_remove_nth_from_end.cpp) | Medium | Two Pointers (Fast-Slow) |
| 5 | [Copy List with Random Pointer](05_copy_list_random_pointer.cpp) | Medium | Hash Map / Interweaving |
| 6 | [Add Two Numbers](06_add_two_numbers.cpp) | Medium | Carry Simulation |
| 7 | [Linked List Cycle](07_linked_list_cycle.cpp) | Easy | Floyd's Cycle Detection |
| 8 | [Find the Duplicate Number](08_find_duplicate_number.cpp) | Medium | Floyd's Algorithm |
| 9 | [LRU Cache](09_lru_cache.cpp) | Medium | Hash Map + Doubly Linked List |
| 10 | [Merge k Sorted Lists](10_merge_k_sorted_lists.cpp) | Hard | Divide & Conquer / Heap |
| 11 | [Reverse Nodes in k-Group](11_reverse_nodes_k_group.cpp) | Hard | Group Reversal |

## Key Concepts

### ListNode Definition
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

### Common Techniques

1. **Two Pointers (Fast-Slow)**
   - Find middle of list
   - Detect cycles
   - Find nth node from end

2. **Reversal**
   - Iterative: prev, curr, next pointers
   - Recursive: trust the recursion

3. **Dummy Node**
   - Simplifies edge cases (empty list, single node)
   - Consistent return value

4. **Floyd's Cycle Detection**
   - Slow moves 1 step, fast moves 2 steps
   - If they meet, cycle exists
   - Can find cycle start point

## Time/Space Complexity Patterns

| Operation | Time | Space |
|-----------|------|-------|
| Traversal | O(n) | O(1) |
| Reversal (Iterative) | O(n) | O(1) |
| Reversal (Recursive) | O(n) | O(n) |
| Find Middle | O(n) | O(1) |
| Cycle Detection | O(n) | O(1) |
| Merge Two Lists | O(n+m) | O(1) |
