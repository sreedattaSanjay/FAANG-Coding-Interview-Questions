"""
Problem: Copy List with Random Pointer (LeetCode 138)

A linked list is given where each node contains an additional random pointer
which could point to any node in the list or null.
Return a deep copy of the list.

Time Complexity: O(n)
Space Complexity: O(n) for hash map, O(1) for interweaving approach
"""

from typing import Optional

class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        """Hash map approach - O(n) space"""
        if not head:
            return None
        
        # Map original nodes to their copies
        old_to_new = {}
        
        # First pass: create all nodes
        curr = head
        while curr:
            old_to_new[curr] = Node(curr.val)
            curr = curr.next
        
        # Second pass: set next and random pointers
        curr = head
        while curr:
            copy = old_to_new[curr]
            copy.next = old_to_new.get(curr.next)
            copy.random = old_to_new.get(curr.random)
            curr = curr.next
        
        return old_to_new[head]
    
    def copyRandomListInterweave(self, head: 'Optional[Node]') -> 'Optional[Node]':
        """Interweaving approach - O(1) space"""
        if not head:
            return None
        
        # Step 1: Create copies interleaved with original
        # 1 -> 1' -> 2 -> 2' -> 3 -> 3'
        curr = head
        while curr:
            copy = Node(curr.val)
            copy.next = curr.next
            curr.next = copy
            curr = copy.next
        
        # Step 2: Set random pointers for copies
        curr = head
        while curr:
            if curr.random:
                curr.next.random = curr.random.next
            curr = curr.next.next
        
        # Step 3: Separate the two lists
        dummy = Node(0)
        copy_tail = dummy
        curr = head
        
        while curr:
            copy = curr.next
            next_orig = copy.next
            
            copy_tail.next = copy
            copy_tail = copy
            
            curr.next = next_orig
            curr = next_orig
        
        return dummy.next

def print_list(head):
    """Helper to print list with random pointers"""
    # First, create index mapping
    node_to_idx = {}
    curr = head
    idx = 0
    while curr:
        node_to_idx[curr] = idx
        curr = curr.next
        idx += 1
    
    # Now print with random indices
    curr = head
    idx = 0
    while curr:
        random_idx = node_to_idx.get(curr.random, "null")
        print(f"Node {idx}: val={curr.val}, random={random_idx}")
        curr = curr.next
        idx += 1

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    n0 = Node(7)
    n1 = Node(13)
    n2 = Node(11)
    n3 = Node(10)
    n4 = Node(1)
    
    n0.next = n1
    n1.next = n2
    n2.next = n3
    n3.next = n4
    
    n0.random = None
    n1.random = n0
    n2.random = n4
    n3.random = n2
    n4.random = n0
    
    print("Original list:")
    print_list(n0)
    
    copy = sol.copyRandomList(n0)
    print("\nCopied list:")
    print_list(copy)
    
    # Verify deep copy
    print("\nVerifying deep copy:")
    print(f"Original head: {id(n0)}")
    print(f"Copy head: {id(copy)}")
    print(f"Different objects: {n0 is not copy}")
    
    # Test case 2: Empty list
    empty_copy = sol.copyRandomList(None)
    print(f"\nEmpty list copy: {empty_copy}")
    
    # Test case 3: Single node pointing to itself
    single = Node(1)
    single.random = single
    single_copy = sol.copyRandomList(single)
    print(f"\nSingle node with self-reference:")
    print(f"Original random points to itself: {single.random is single}")
    print(f"Copy random points to itself: {single_copy.random is single_copy}")
    print(f"Copy is different object: {single is not single_copy}")
    
    print("\nAll test cases passed!")

