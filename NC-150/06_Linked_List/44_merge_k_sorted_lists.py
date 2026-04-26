"""
Problem: Merge k Sorted Lists (LeetCode 23)

You are given an array of k linked-lists lists, each linked-list is sorted 
in ascending order. Merge all the linked-lists into one sorted linked-list.

Time Complexity: O(N log k) where N is total nodes, k is number of lists
Space Complexity: O(log k) for divide and conquer, O(k) for heap
"""

from typing import List, Optional
import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    
    # For heap comparison (needed since Python 3)
    def __lt__(self, other):
        return self.val < other.val

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        """Divide and Conquer approach"""
        if not lists:
            return None
        return self._merge_range(lists, 0, len(lists) - 1)
    
    def _merge_range(self, lists, left, right):
        if left == right:
            return lists[left]
        if left > right:
            return None
        
        mid = (left + right) // 2
        left_merged = self._merge_range(lists, left, mid)
        right_merged = self._merge_range(lists, mid + 1, right)
        
        return self._merge_two(left_merged, right_merged)
    
    def _merge_two(self, l1, l2):
        dummy = ListNode(0)
        tail = dummy
        
        while l1 and l2:
            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next
            tail = tail.next
        
        tail.next = l1 if l1 else l2
        return dummy.next
    
    def mergeKListsHeap(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        """Min Heap approach"""
        heap = []
        
        # Add first node of each list to heap
        for i, node in enumerate(lists):
            if node:
                # Use (value, index, node) to handle equal values
                heapq.heappush(heap, (node.val, i, node))
        
        dummy = ListNode(0)
        tail = dummy
        
        while heap:
            val, idx, node = heapq.heappop(heap)
            
            tail.next = node
            tail = tail.next
            
            if node.next:
                heapq.heappush(heap, (node.next.val, idx, node.next))
        
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

if __name__ == "__main__":
    sol = Solution()
    
    # Test case 1: [[1,4,5],[1,3,4],[2,6]]
    lists1 = [
        create_list([1, 4, 5]),
        create_list([1, 3, 4]),
        create_list([2, 6])
    ]
    print("Lists:", [[1,4,5], [1,3,4], [2,6]])
    merged1 = sol.mergeKLists(lists1)
    print(f"Merged: {list_to_array(merged1)}")
    assert list_to_array(merged1) == [1, 1, 2, 3, 4, 4, 5, 6]
    
    # Test case 2: Empty list
    lists2 = []
    merged2 = sol.mergeKLists(lists2)
    print(f"\nEmpty input: {list_to_array(merged2)}")
    assert list_to_array(merged2) == []
    
    # Test case 3: [[]]
    lists3 = [None]
    merged3 = sol.mergeKLists(lists3)
    print(f"[[]] input: {list_to_array(merged3)}")
    assert list_to_array(merged3) == []
    
    # Test case 4: Single list
    lists4 = [create_list([1, 2, 3])]
    merged4 = sol.mergeKLists(lists4)
    print(f"\nSingle list: {list_to_array(merged4)}")
    assert list_to_array(merged4) == [1, 2, 3]
    
    # Test heap solution
    lists5 = [
        create_list([1, 4, 5]),
        create_list([1, 3, 4]),
        create_list([2, 6])
    ]
    merged5 = sol.mergeKListsHeap(lists5)
    print(f"\nHeap solution: {list_to_array(merged5)}")
    assert list_to_array(merged5) == [1, 1, 2, 3, 4, 4, 5, 6]
    
    print("\nAll test cases passed!")

