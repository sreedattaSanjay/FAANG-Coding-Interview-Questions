# Arrays & Hashing

## Pattern Overview

Arrays and Hashing problems form the foundation of algorithm interviews. The key insight is using **hash-based data structures** (Hash Sets, Hash Maps) to achieve O(1) average-time lookups, insertions, and deletions.

## When to Use This Pattern

- **Finding duplicates** → Hash Set
- **Counting frequencies** → Hash Map
- **Finding pairs/complements** → Hash Map (store value → index)
- **Grouping elements** → Hash Map with custom keys
- **O(n) lookup requirements** → Hash-based approach

## Key Techniques

1. **Hash Set for Membership**: O(1) lookup to check if element exists
2. **Hash Map for Counting**: Track frequency of each element
3. **Hash Map for Indexing**: Store element → index mappings
4. **Sorted String as Key**: Group anagrams by sorting characters
5. **Prefix/Suffix Products**: Avoid division by precomputing products
6. **Bucket Sort**: When frequency is bounded, use array indices

## Problems in This Section

| # | Problem | Difficulty | Key Technique |
|---|---------|------------|---------------|
| 1 | [Contains Duplicate](01_contains_duplicate_EXPLAINED.md) | Easy | Hash Set |
| 2 | [Valid Anagram](02_valid_anagram_EXPLAINED.md) | Easy | Character Counting |
| 3 | [Two Sum](03_two_sum_EXPLAINED.md) | Easy | Hash Map Complement |
| 4 | [Group Anagrams](04_group_anagrams_EXPLAINED.md) | Medium | Sorted Key |
| 5 | [Top K Frequent Elements](05_top_k_frequent_elements_EXPLAINED.md) | Medium | Bucket Sort |
| 6 | [Product of Array Except Self](06_product_of_array_except_self_EXPLAINED.md) | Medium | Prefix/Suffix |
| 7 | [Valid Sudoku](07_valid_sudoku_EXPLAINED.md) | Medium | Multiple Hash Sets |
| 8 | [Encode and Decode Strings](08_encode_decode_strings_EXPLAINED.md) | Medium | Length Prefix |
| 9 | [Longest Consecutive Sequence](09_longest_consecutive_sequence_EXPLAINED.md) | Hard | Hash Set + Sequence Start |

## Suggested Study Order

1. **Contains Duplicate** - Basic hash set usage
2. **Valid Anagram** - Character frequency counting
3. **Two Sum** - Hash map for complement lookup (most common interview pattern!)
4. **Group Anagrams** - Using sorted strings as hash keys
5. **Top K Frequent Elements** - Combining hash map with bucket sort
6. **Product of Array Except Self** - Prefix/suffix product technique
7. **Valid Sudoku** - Multiple hash sets for constraint checking
8. **Encode and Decode Strings** - String serialization technique
9. **Longest Consecutive Sequence** - O(n) sequence finding with hash set

## Time Complexity Cheat Sheet

| Operation | Array | Hash Set | Hash Map |
|-----------|-------|----------|----------|
| Access by index | O(1) | N/A | N/A |
| Search | O(n) | O(1) avg | O(1) avg |
| Insert | O(n) | O(1) avg | O(1) avg |
| Delete | O(n) | O(1) avg | O(1) avg |

## Common Mistakes to Avoid

1. **Forgetting hash collisions**: Worst case is O(n) for hash operations
2. **Not handling empty arrays**: Always check for edge cases
3. **Integer overflow**: Be careful with product calculations
4. **Off-by-one errors**: Array indices start at 0
5. **Modifying while iterating**: Can cause unexpected behavior

