# 08 - Tries (Prefix Trees)

## Problems in this section (NeetCode-150 #61-63):

| # | Problem | Difficulty | Key Concepts |
|---|---------|------------|--------------|
| 61 | Implement Trie (Prefix Tree) | Medium | Trie Design |
| 62 | Design Add and Search Words Data Structure | Medium | Trie, Backtracking |
| 63 | Word Search II | Hard | Trie, Backtracking, Matrix |

## Pattern: Trie (Prefix Tree)

A Trie is a tree-like data structure used for efficient retrieval of keys in a dataset of strings.

### Key Operations:
- **Insert**: Add a word to the trie
- **Search**: Check if a word exists
- **StartsWith**: Check if any word starts with a prefix

### Time Complexity:
- Insert/Search/StartsWith: O(m) where m = length of word
- Space: O(n * m) where n = number of words

