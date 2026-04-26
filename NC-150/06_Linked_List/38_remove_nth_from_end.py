"""
Problem: Remove Nth Node From End of List (LeetCode 19)

Given the head of a linked list, remove the nth node from the end of the list
and return its head.

Time Complexity: O(n) - single pass
Space Complexity: O(1)
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        """Two pointers with gap of n - single pass solution"""
        # Dummy node handles edge case of removing the head
        dummy = ListNode(0, head)
        
        fast = dummy
        slow = dummy
        
        # Move fast pointer n+1 steps ahead
        for _ in range(n + 1):
            fast = fast.next
        
        # Move both pointers until fast reaches the end
        while fast:
            fast = fast.next
            slow = slow.next
        
        # slow is now just before the node to be removed
        slow.next = slow.next.next
        
        return dummy.next
    
    def removeNthFromEndTwoPass(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        """Two-pass approach: find length first"""
        # First pass: count nodes
        length = 0
        curr = head
        while curr:
            length += 1
            curr = curr.next
        
        # Handle removing the head
        if n == length:
            return head.next
        
        # Second pass: find the node before the one to remove
        curr = head
        for _ in range(length - n - 1):
            curr = curr.next
        
        curr.next = curr.next.next
        return head

# Helper functions
def create_list(values):
    if not values:
        return None
    head = ListNode(values[0])
    current = head
    for val in values[1:]:
        current.next = ListNode(val)
        current = current.next
    return head

def list_to_array(head):
    result = []
    while head:
        result.append(head.val)
        head = head.next
    return result

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [1,2,3,4,5], n=2 -> [1,2,3,5]
    head1 = create_list([1, 2, 3, 4, 5])
    print(f"Original: {list_to_array(head1)}")
    head1 = sol.removeNthFromEnd(head1, 2)
    print(f"After removing 2nd from end: {list_to_array(head1)}")
    assert list_to_array(head1) == [1, 2, 3, 5]
    
    # Test case 2: [1], n=1 -> []
    head2 = create_list([1])
    head2 = sol.removeNthFromEnd(head2, 1)
    print(f"\nAfter removing only node: {list_to_array(head2)}")
    assert list_to_array(head2) == []
    
    # Test case 3: [1,2], n=1 -> [1]
    head3 = create_list([1, 2])
    head3 = sol.removeNthFromEnd(head3, 1)
    print(f"After removing last: {list_to_array(head3)}")
    assert list_to_array(head3) == [1]
    
    # Test case 4: [1,2], n=2 -> [2] (remove head)
    head4 = create_list([1, 2])
    head4 = sol.removeNthFromEnd(head4, 2)
    print(f"After removing head: {list_to_array(head4)}")
    assert list_to_array(head4) == [2]
    
    print("\nAll test cases passed!")

