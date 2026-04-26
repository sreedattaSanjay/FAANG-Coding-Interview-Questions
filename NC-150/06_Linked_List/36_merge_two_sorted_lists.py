"""
Problem: Merge Two Sorted Lists (LeetCode 21)

Merge two sorted linked lists and return it as a sorted list.
The list should be made by splicing together the nodes of the first two lists.

Time Complexity: O(n + m) where n, m are lengths of the two lists
Space Complexity: O(1) for iterative, O(n + m) for recursive
"""

from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        """Iterative approach with dummy node - O(1) space"""
        dummy = ListNode(0)
        tail = dummy
        
        while list1 and list2:
            if list1.val <= list2.val:
                tail.next = list1
                list1 = list1.next
            else:
                tail.next = list2
                list2 = list2.next
            tail = tail.next
        
        # Attach remaining nodes
        tail.next = list1 if list1 else list2
        
        return dummy.next
    
    def mergeTwoListsRecursive(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        """Recursive approach - O(n+m) space due to call stack"""
        # Base cases
        if not list1:
            return list2
        if not list2:
            return list1
        
        # Choose smaller value as head, recurse for the rest
        if list1.val <= list2.val:
            list1.next = self.mergeTwoListsRecursive(list1.next, list2)
            return list1
        else:
            list2.next = self.mergeTwoListsRecursive(list1, list2.next)
            return list2

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
    
    # Test case 1: [1,2,4] + [1,3,4] = [1,1,2,3,4,4]
    l1 = create_list([1, 2, 4])
    l2 = create_list([1, 3, 4])
    merged1 = sol.mergeTwoLists(l1, l2)
    print(f"Merged: {list_to_array(merged1)}")
    assert list_to_array(merged1) == [1, 1, 2, 3, 4, 4]
    
    # Test case 2: [] + [] = []
    l3 = create_list([])
    l4 = create_list([])
    merged2 = sol.mergeTwoLists(l3, l4)
    print(f"Merged: {list_to_array(merged2)}")
    assert list_to_array(merged2) == []
    
    # Test case 3: [] + [0] = [0]
    l5 = create_list([])
    l6 = create_list([0])
    merged3 = sol.mergeTwoLists(l5, l6)
    print(f"Merged: {list_to_array(merged3)}")
    assert list_to_array(merged3) == [0]
    
    # Test case 4: Different lengths
    l7 = create_list([1, 3, 5, 7])
    l8 = create_list([2, 4])
    merged4 = sol.mergeTwoLists(l7, l8)
    print(f"Merged: {list_to_array(merged4)}")
    assert list_to_array(merged4) == [1, 2, 3, 4, 5, 7]
    
    # Test recursive solution
    l9 = create_list([1, 2, 4])
    l10 = create_list([1, 3, 4])
    merged5 = sol.mergeTwoListsRecursive(l9, l10)
    print(f"Recursive merged: {list_to_array(merged5)}")
    assert list_to_array(merged5) == [1, 1, 2, 3, 4, 4]
    
    print("\nAll test cases passed!")

