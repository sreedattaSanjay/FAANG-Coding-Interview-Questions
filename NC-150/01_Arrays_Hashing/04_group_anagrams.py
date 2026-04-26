"""
LeetCode 49: Group Anagrams
https://leetcode.com/problems/group-anagrams/

Given an array of strings strs, group the anagrams together. 
You can return the answer in any order.

Time Complexity: O(n * k log k) where n = number of strings, k = max string length
Space Complexity: O(n * k) - storing all strings in hash map
"""

from typing import List
from collections import defaultdict


class Solution:
    # Solution 1: Sorted String as Key
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)
        
        for s in strs:
            key = ''.join(sorted(s))
            groups[key].append(s)
        
        return list(groups.values())
    
    # Solution 2: Character Count as Key (Tuple)
    # Time: O(n * k) - no sorting needed
    def groupAnagramsCount(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)
        
        for s in strs:
            count = [0] * 26
            for c in s:
                count[ord(c) - ord('a')] += 1
            
            # Use tuple as key (lists aren't hashable)
            groups[tuple(count)].append(s)
        
        return list(groups.values())
    
    # Solution 3: Using Counter (Pythonic but slower due to frozenset creation)
    def groupAnagramsCounter(self, strs: List[str]) -> List[List[str]]:
        from collections import Counter
        groups = defaultdict(list)
        
        for s in strs:
            # frozenset of items makes it hashable
            key = frozenset(Counter(s).items())
            groups[key].append(s)
        
        return list(groups.values())


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Basic case
    strs1 = ["eat", "tea", "tan", "ate", "nat", "bat"]
    print(f"Test 1: {sol.groupAnagrams(strs1)}")
    # Expected: [["eat","tea","ate"],["tan","nat"],["bat"]] (any order)
    
    # Test Case 2: Empty string
    strs2 = [""]
    print(f"Test 2: {sol.groupAnagrams(strs2)}")
    # Expected: [[""]]
    
    # Test Case 3: Single character
    strs3 = ["a"]
    print(f"Test 3: {sol.groupAnagrams(strs3)}")
    # Expected: [["a"]]
    
    # Test Case 4: No anagrams
    strs4 = ["abc", "def", "ghi"]
    print(f"Test 4: {sol.groupAnagrams(strs4)}")
    # Expected: [["abc"],["def"],["ghi"]]
    
    # Test Case 5: All same anagram
    strs5 = ["abc", "bca", "cab"]
    print(f"Test 5: {sol.groupAnagrams(strs5)}")
    # Expected: [["abc","bca","cab"]]
    
    # Test Case 6: Multiple empty strings
    strs6 = ["", ""]
    print(f"Test 6: {sol.groupAnagrams(strs6)}")
    # Expected: [["",""]]

