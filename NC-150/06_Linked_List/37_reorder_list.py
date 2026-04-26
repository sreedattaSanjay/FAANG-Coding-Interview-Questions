"""
Problem: Reorder List (LeetCode 143)

Given a singly linked list L: L0 → L1 → … → Ln-1 → Ln
Reorder it to: L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …

You may not modify the values in the list's nodes, only nodes may be changed.

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
        if not head or not head.next:
            return
        
        # Step 1: Find the middle of the list (slow-fast pointer)
        slow, fast = head, head
        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next
        
        # Step 2: Reverse the second half
        second_half = self.reverse_list(slow.next)
        slow.next = None  # Cut the first half
        
        # Step 3: Merge the two halves alternately
        first_half = head
        while second_half:
            temp1 = first_half.next
            temp2 = second_half.next
            
            first_half.next = second_half
            second_half.next = temp1
            
            first_half = temp1
            second_half = temp2
    
    def reverse_list(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev = None
        curr = head
        while curr:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
        return prev

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
    
    # Test case 1: [1,2,3,4] -> [1,4,2,3]
    head1 = create_list([1, 2, 3, 4])
    print(f"Original: {list_to_array(head1)}")
    sol.reorderList(head1)
    print(f"Reordered: {list_to_array(head1)}")
    assert list_to_array(head1) == [1, 4, 2, 3]
    
    # Test case 2: [1,2,3,4,5] -> [1,5,2,4,3]
    head2 = create_list([1, 2, 3, 4, 5])
    print(f"\nOriginal: {list_to_array(head2)}")
    sol.reorderList(head2)
    print(f"Reordered: {list_to_array(head2)}")
    assert list_to_array(head2) == [1, 5, 2, 4, 3]
    
    # Test case 3: [1] -> [1]
    head3 = create_list([1])
    sol.reorderList(head3)
    print(f"\nSingle node: {list_to_array(head3)}")
    assert list_to_array(head3) == [1]
    
    # Test case 4: [1,2] -> [1,2]
    head4 = create_list([1, 2])
    sol.reorderList(head4)
    print(f"Two nodes: {list_to_array(head4)}")
    assert list_to_array(head4) == [1, 2]
    
    print("\nAll test cases passed!")

