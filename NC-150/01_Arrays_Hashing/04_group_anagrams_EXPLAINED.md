# Group Anagrams (LeetCode #49)

## Problem Statement

Given an array of strings `strs`, group the **anagrams** together. You can return the answer in **any order**.

An **Anagram** is a word formed by rearranging the letters of a different word, using all the original letters exactly once.

### Examples

```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Input: strs = [""]
Output: [[""]]

Input: strs = ["a"]
Output: [["a"]]
```

### Constraints
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] consists of lowercase English letters

## Intuition

Anagrams have the **same characters in the same frequencies** - they just differ in order.

Key insight: If we **normalize** each string (e.g., by sorting), all anagrams will have the **same normalized form**. This normalized form becomes our **hash key**.

Two approaches to create the key:
1. **Sorted string**: "eat" → "aet", "tea" → "aet", "ate" → "aet" (all same!)
2. **Character count**: "eat" → "a1e1t1", "tea" → "a1e1t1" (all same!)

## Approach

### Approach 1: Sorted String as Key

```
1. Create hash map: sorted_string → list of original strings
2. For each string s:
   a. Sort s to get key
   b. Add s to groups[key]
3. Return all values from hash map
```

### Approach 2: Character Count as Key

```
1. Create hash map: count_tuple → list of original strings
2. For each string s:
   a. Count frequency of each character
   b. Convert count array to tuple/string as key
   c. Add s to groups[key]
3. Return all values from hash map
```

## Visual Walkthrough

### Example: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

```
Using sorted string as key:

"eat" → sort → "aet"  →  groups["aet"] = ["eat"]
"tea" → sort → "aet"  →  groups["aet"] = ["eat", "tea"]
"tan" → sort → "ant"  →  groups["ant"] = ["tan"]
"ate" → sort → "aet"  →  groups["aet"] = ["eat", "tea", "ate"]
"nat" → sort → "ant"  →  groups["ant"] = ["tan", "nat"]
"bat" → sort → "abt"  →  groups["abt"] = ["bat"]

Final groups:
{
  "aet": ["eat", "tea", "ate"],
  "ant": ["tan", "nat"],
  "abt": ["bat"]
}

Result: [["eat","tea","ate"], ["tan","nat"], ["bat"]]
```

### Character Count Method

```
"eat" → count = [1,0,0,0,1,0,...,1,...] → key = (1,0,0,0,1,...,1,...)
                 a       e           t

"tea" → count = [1,0,0,0,1,0,...,1,...] → same key!
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty string | `[""]` | `[[""]]` | Empty sorts to empty |
| Single char | `["a"]` | `[["a"]]` | Single element group |
| Multiple empty | `["", ""]` | `[["", ""]]` | Both have same key |
| No anagrams | `["a","b","c"]` | `[["a"],["b"],["c"]]` | Each in own group |
| All anagrams | `["abc","bca","cab"]` | `[["abc","bca","cab"]]` | One big group |
| Different lengths | `["a","ab","abc"]` | `[["a"],["ab"],["abc"]]` | Can't be anagrams |

## Complexity Analysis

### Sorted String Approach
- **Time Complexity**: O(n × k log k)
  - n = number of strings
  - k = maximum length of a string
  - Sorting each string takes O(k log k)
  
- **Space Complexity**: O(n × k)
  - Storing all strings in the hash map

### Character Count Approach
- **Time Complexity**: O(n × k)
  - Counting characters is O(k), no sorting needed
  
- **Space Complexity**: O(n × k)
  - Same as above, plus O(26) = O(1) for count array

## Common Mistakes

1. **Using list as dictionary key**: Lists aren't hashable in Python; use tuple
2. **Forgetting to handle empty strings**: Empty string is valid input
3. **Case sensitivity**: Problem says lowercase only, but clarify in interviews
4. **Modifying original strings**: Sorting should be on a copy

## Related Problems

- [Valid Anagram](02_valid_anagram_EXPLAINED.md) - Check if two strings are anagrams
- [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) - Sliding window + anagram check
- [Anagram Mappings](https://leetcode.com/problems/find-anagram-mappings/)

## Key Takeaways

1. **Normalization for grouping**: Transform items so equivalent ones have same key
2. **Sorted string as canonical form**: Classic technique for anagram problems
3. **Character count avoids sorting**: O(k) vs O(k log k) per string
4. **defaultdict simplifies code**: No need to check if key exists
5. **Tuple for hashable keys**: Convert lists/arrays to tuples for dict keys

