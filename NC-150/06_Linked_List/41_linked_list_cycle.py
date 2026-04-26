"""
Problem: Linked List Cycle (LeetCode 141)

Given head, the head of a linked list, determine if the linked list has a cycle.
A cycle exists if a node can be reached again by continuously following next.

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        """Floyd's Cycle Detection (Tortoise and Hare)"""
        if not head or not head.next:
            return False
        
        slow = head
        fast = head
        
        while fast and fast.next:
            slow = slow.next         # Move 1 step
            fast = fast.next.next    # Move 2 steps
            
            if slow == fast:
                return True  # Cycle detected
        
        return False  # Fast reached end, no cycle
    
    def hasCycleHashSet(self, head: Optional[ListNode]) -> bool:
        """Alternative: Using HashSet - O(n) space"""
        visited = set()
        
        while head:
            if head in visited:
                return True
            visited.add(head)
            head = head.next
        
        return False
    
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """Find the start of the cycle (bonus)"""
        if not head or not head.next:
            return None
        
        slow = head
        fast = head
        
        # Phase 1: Detect if cycle exists
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            
            if slow == fast:
                # Phase 2: Find the start of the cycle
                slow = head
                while slow != fast:
                    slow = slow.next
                    fast = fast.next
                return slow  # Start of cycle
        
        return None  # No cycle

# Helper function
def create_list_with_cycle(values, cycle_index):
    """Create a list with a cycle at the given index"""
    if not values:
        return None
    
    head = ListNode(values[0])
    current = head
    cycle_node = None
    
    for i, val in enumerate(values[1:], 1):
        current.next = ListNode(val)
        current = current.next
        if i == cycle_index:
            cycle_node = current
    
    if cycle_index == 0:
        cycle_node = head
    
    if cycle_node:
        current.next = cycle_node  # Create cycle
    
    return head

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: Cycle exists [3,2,0,-4] with cycle at index 1
    head1 = create_list_with_cycle([3, 2, 0, -4], 1)
    print(f"Test 1 (cycle at index 1): {sol.hasCycle(head1)}")
    cycle_start = sol.detectCycle(head1)
    print(f"Cycle starts at value: {cycle_start.val if cycle_start else None}")
    assert sol.hasCycle(head1) == True
    
    # Test case 2: Cycle at head [1,2]
    head2 = ListNode(1)
    node2 = ListNode(2)
    head2.next = node2
    node2.next = head2
    print(f"\nTest 2 (cycle at head): {sol.hasCycle(head2)}")
    assert sol.hasCycle(head2) == True
    
    # Test case 3: No cycle
    head3 = ListNode(1)
    head3.next = ListNode(2)
    head3.next.next = ListNode(3)
    print(f"\nTest 3 (no cycle): {sol.hasCycle(head3)}")
    assert sol.hasCycle(head3) == False
    
    # Test case 4: Single node, no cycle
    head4 = ListNode(1)
    print(f"\nTest 4 (single node): {sol.hasCycle(head4)}")
    assert sol.hasCycle(head4) == False
    
    # Test case 5: Empty list
    head5 = None
    print(f"\nTest 5 (empty): {sol.hasCycle(head5)}")
    assert sol.hasCycle(head5) == False
    
    # Test HashSet solution
    head6 = create_list_with_cycle([1, 2, 3, 4], 2)
    print(f"\nTest HashSet solution: {sol.hasCycleHashSet(head6)}")
    assert sol.hasCycleHashSet(head6) == True
    
    print("\nAll test cases passed!")

