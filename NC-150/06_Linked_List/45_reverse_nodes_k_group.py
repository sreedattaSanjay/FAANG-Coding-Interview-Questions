"""
Problem: Reverse Nodes in k-Group (LeetCode 25)

Given a linked list, reverse the nodes of a linked list k at a time
and return its modified list.

- k is a positive integer and is less than or equal to the length of the list.
- If the number of nodes is not a multiple of k, the nodes left out at the
  end should remain as-is.

Time Complexity: O(n)
Space Complexity: O(1)
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if not head or k == 1:
            return head
        
        # Dummy node to handle head changes
        dummy = ListNode(0)
        dummy.next = head
        
        prev_group_end = dummy
        
        while True:
            # Check if there are k nodes left
            kth_node = self._get_kth_node(prev_group_end, k)
            if not kth_node:
                break
            
            # Mark the boundaries
            group_start = prev_group_end.next
            next_group_start = kth_node.next
            
            # Reverse the k nodes
            self._reverse_list(group_start, kth_node)
            
            # Connect with previous and next parts
            prev_group_end.next = kth_node  # kth_node is now first in reversed group
            group_start.next = next_group_start  # group_start is now last
            
            # Move to next group
            prev_group_end = group_start
        
        return dummy.next
    
    def _get_kth_node(self, current: ListNode, k: int) -> Optional[ListNode]:
        """Get the k-th node from current position"""
        while current and k > 0:
            current = current.next
            k -= 1
        return current
    
    def _reverse_list(self, start: ListNode, end: ListNode) -> None:
        """Reverse nodes between start and end (inclusive)"""
        prev = None
        curr = start
        stop = end.next
        
        while curr != stop:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node

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
    
    # Test case 1: [1,2,3,4,5], k=2 -> [2,1,4,3,5]
    head1 = create_list([1, 2, 3, 4, 5])
    print(f"Original: {list_to_array(head1)}")
    head1 = sol.reverseKGroup(head1, 2)
    print(f"k=2: {list_to_array(head1)}")
    assert list_to_array(head1) == [2, 1, 4, 3, 5]
    
    # Test case 2: [1,2,3,4,5], k=3 -> [3,2,1,4,5]
    head2 = create_list([1, 2, 3, 4, 5])
    print(f"\nOriginal: {list_to_array(head2)}")
    head2 = sol.reverseKGroup(head2, 3)
    print(f"k=3: {list_to_array(head2)}")
    assert list_to_array(head2) == [3, 2, 1, 4, 5]
    
    # Test case 3: [1,2,3,4], k=2 -> [2,1,4,3]
    head3 = create_list([1, 2, 3, 4])
    print(f"\nOriginal: {list_to_array(head3)}")
    head3 = sol.reverseKGroup(head3, 2)
    print(f"k=2: {list_to_array(head3)}")
    assert list_to_array(head3) == [2, 1, 4, 3]
    
    # Test case 4: [1], k=1 -> [1]
    head4 = create_list([1])
    head4 = sol.reverseKGroup(head4, 1)
    print(f"\nk=1: {list_to_array(head4)}")
    assert list_to_array(head4) == [1]
    
    # Test case 5: [1,2,3,4,5], k=5 -> [5,4,3,2,1]
    head5 = create_list([1, 2, 3, 4, 5])
    head5 = sol.reverseKGroup(head5, 5)
    print(f"k=5 (entire list): {list_to_array(head5)}")
    assert list_to_array(head5) == [5, 4, 3, 2, 1]
    
    # Test case 6: [1,2,3], k=4 -> [1,2,3] (no change)
    head6 = create_list([1, 2, 3])
    head6 = sol.reverseKGroup(head6, 4)
    print(f"k=4 (k > length, no change): {list_to_array(head6)}")
    assert list_to_array(head6) == [1, 2, 3]
    
    print("\nAll test cases passed!")

