"""
Problem: Reverse Linked List (LeetCode 206)

Given the head of a singly linked list, reverse the list, and return the reversed list.

Time Complexity: O(n) - single pass through the list
Space Complexity: O(1) for iterative, O(n) for recursive
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """Iterative approach - O(1) space"""
        prev = None
        curr = head
        
        while curr:
            next_temp = curr.next  # Save next
            curr.next = prev       # Reverse the link
            prev = curr            # Move prev forward
            curr = next_temp       # Move curr forward
        
        return prev
    
    def reverseListRecursive(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """Recursive approach - O(n) space due to call stack"""
        # Base case: empty list or single node
        if not head or not head.next:
            return head
        
        # Reverse the rest of the list
        new_head = self.reverseListRecursive(head.next)
        
        # Put the first element at the end
        head.next.next = head
        head.next = None
        
        return new_head

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

def print_list(head):
    values = list_to_array(head)
    print(" -> ".join(map(str, values)) if values else "Empty")

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [1,2,3,4,5] -> [5,4,3,2,1]
    head1 = create_list([1, 2, 3, 4, 5])
    print("Original:", list_to_array(head1))
    head1 = sol.reverseList(head1)
    print("Reversed:", list_to_array(head1))
    assert list_to_array(head1) == [5, 4, 3, 2, 1]
    
    # Test case 2: [1,2] -> [2,1]
    head2 = create_list([1, 2])
    print("\nOriginal:", list_to_array(head2))
    head2 = sol.reverseList(head2)
    print("Reversed:", list_to_array(head2))
    assert list_to_array(head2) == [2, 1]
    
    # Test case 3: [] -> []
    head3 = create_list([])
    print("\nOriginal:", list_to_array(head3))
    head3 = sol.reverseList(head3)
    print("Reversed:", list_to_array(head3))
    assert list_to_array(head3) == []
    
    # Test case 4: [1] -> [1]
    head4 = create_list([1])
    print("\nOriginal:", list_to_array(head4))
    head4 = sol.reverseList(head4)
    print("Reversed:", list_to_array(head4))
    assert list_to_array(head4) == [1]
    
    # Test recursive solution
    head5 = create_list([1, 2, 3, 4, 5])
    head5 = sol.reverseListRecursive(head5)
    print("\nRecursive result:", list_to_array(head5))
    assert list_to_array(head5) == [5, 4, 3, 2, 1]
    
    print("\nAll test cases passed!")
