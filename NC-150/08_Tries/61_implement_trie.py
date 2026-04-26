"""
LeetCode 208: Implement Trie (Prefix Tree)
https://leetcode.com/problems/implement-trie-prefix-tree/

A trie (pronounced as "try") or prefix tree is a tree data structure used 
to efficiently store and retrieve keys in a dataset of strings.

Implement the Trie class:
- Trie() Initializes the trie object.
- void insert(String word) Inserts the string word into the trie.
- boolean search(String word) Returns true if word is in the trie.
- boolean startsWith(String prefix) Returns true if there is a previously 
  inserted string that has the prefix.

Time Complexity: O(m) for all operations where m is word/prefix length
Space Complexity: O(n * m) where n is number of words, m is average length
"""


class TrieNode:
    def __init__(self):
        self.children = {}  # char -> TrieNode
        self.is_end_of_word = False


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        node = self._find_node(word)
        return node is not None and node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        return self._find_node(prefix) is not None
    
    def _find_node(self, s: str) -> TrieNode:
        node = self.root
        for char in s:
            if char not in node.children:
                return None
            node = node.children[char]
        return node


# Alternative: Using defaultdict for cleaner code
from collections import defaultdict


class TrieNodeDefault:
    def __init__(self):
        self.children = defaultdict(TrieNodeDefault)
        self.is_end_of_word = False


class TrieDefault:
    def __init__(self):
        self.root = TrieNodeDefault()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            node = node.children[char]  # Auto-creates if not exists
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        node = self._find_node(word)
        return node is not None and node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        return self._find_node(prefix) is not None
    
    def _find_node(self, s: str) -> TrieNodeDefault:
        node = self.root
        for char in s:
            if char not in node.children:
                return None
            node = node.children[char]
        return node


# Test
if __name__ == "__main__":
    trie = Trie()
    
    trie.insert("apple")
    print(f"search('apple'): {trie.search('apple')}")      # True
    print(f"search('app'): {trie.search('app')}")          # False
    print(f"startsWith('app'): {trie.startsWith('app')}")  # True
    
    trie.insert("app")
    print(f"search('app'): {trie.search('app')}")          # True
    
    # Test TrieDefault
    print("\nUsing defaultdict Trie:")
    trie_default = TrieDefault()
    trie_default.insert("hello")
    print(f"search('hello'): {trie_default.search('hello')}")     # True
    print(f"search('hell'): {trie_default.search('hell')}")       # False
    print(f"startsWith('hel'): {trie_default.startsWith('hel')}") # True

