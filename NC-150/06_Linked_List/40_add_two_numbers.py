"""
Problem: Add Two Numbers (LeetCode 2)

You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order, and each node contains a single digit.
Add the two numbers and return the sum as a linked list.

Time Complexity: O(max(n, m))
Space Complexity: O(max(n, m)) for the result list
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        curr = dummy
        carry = 0
        
        while l1 or l2 or carry:
            total = carry
            
            if l1:
                total += l1.val
                l1 = l1.next
            
            if l2:
                total += l2.val
                l2 = l2.next
            
            carry = total // 10
            curr.next = ListNode(total % 10)
            curr = curr.next
        
        return dummy.next

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

def list_to_number(head):
    """Convert reversed list to actual number for display"""
    result = 0
    multiplier = 1
    while head:
        result += head.val * multiplier
        multiplier *= 10
        head = head.next
    return result

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: 342 + 465 = 807
    l1 = create_list([2, 4, 3])
    l2 = create_list([5, 6, 4])
    result1 = sol.addTwoNumbers(l1, l2)
    print(f"342 + 465 = {list_to_number(result1)}")
    print(f"Result list: {list_to_array(result1)}")
    assert list_to_array(result1) == [7, 0, 8]
    
    # Test case 2: 0 + 0 = 0
    l3 = create_list([0])
    l4 = create_list([0])
    result2 = sol.addTwoNumbers(l3, l4)
    print(f"\n0 + 0 = {list_to_number(result2)}")
    assert list_to_array(result2) == [0]
    
    # Test case 3: 9999999 + 9999 = 10009998
    l5 = create_list([9, 9, 9, 9, 9, 9, 9])
    l6 = create_list([9, 9, 9, 9])
    result3 = sol.addTwoNumbers(l5, l6)
    print(f"\n9999999 + 9999 = {list_to_number(result3)}")
    assert list_to_array(result3) == [8, 9, 9, 9, 0, 0, 0, 1]
    
    # Test case 4: 99 + 1 = 100
    l7 = create_list([9, 9])
    l8 = create_list([1])
    result4 = sol.addTwoNumbers(l7, l8)
    print(f"\n99 + 1 = {list_to_number(result4)}")
    assert list_to_array(result4) == [0, 0, 1]
    
    print("\nAll test cases passed!")

