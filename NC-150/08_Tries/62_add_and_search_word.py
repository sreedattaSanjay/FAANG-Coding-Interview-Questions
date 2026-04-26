"""
LeetCode 211: Design Add and Search Words Data Structure
https://leetcode.com/problems/add-and-search-word-data-structure-design/

Design a data structure that supports adding new words and finding if a 
string matches any previously added string.

Implement the WordDictionary class:
- WordDictionary() Initializes the object.
- void addWord(word) Adds word to the data structure.
- bool search(word) Returns true if there is any string in the data structure 
  that matches word or false otherwise. word may contain dots '.' where dots 
  can be matched with any letter.

Time Complexity: 
  - addWord: O(m) where m is word length
  - search: O(m) for words without '.', O(26^m) worst case with '.'
Space Complexity: O(n * m) where n is number of words
"""


class TrieNode:
    def __init__(self):
        self.children = {}  # char -> TrieNode
        self.is_end_of_word = False


class WordDictionary:
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        def search_helper(index: int, node: TrieNode) -> bool:
            if index == len(word):
                return node.is_end_of_word
            
            char = word[index]
            
            if char == '.':
                # Wildcard: try all possible children
                for child in node.children.values():
                    if search_helper(index + 1, child):
                        return True
                return False
            else:
                # Regular character
                if char not in node.children:
                    return False
                return search_helper(index + 1, node.children[char])
        
        return search_helper(0, self.root)


# Alternative solution using iterative approach with stack
class WordDictionaryIterative:
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        # Stack of (node, index) pairs
        stack = [(self.root, 0)]
        
        while stack:
            node, index = stack.pop()
            
            if index == len(word):
                if node.is_end_of_word:
                    return True
                continue
            
            char = word[index]
            
            if char == '.':
                # Add all children to stack
                for child in node.children.values():
                    stack.append((child, index + 1))
            else:
                if char in node.children:
                    stack.append((node.children[char], index + 1))
        
        return False


# Test
if __name__ == "__main__":
    word_dict = WordDictionary()
    
    word_dict.addWord("bad")
    word_dict.addWord("dad")
    word_dict.addWord("mad")
    
    print(f"search('pad'): {word_dict.search('pad')}")  # False
    print(f"search('bad'): {word_dict.search('bad')}")  # True
    print(f"search('.ad'): {word_dict.search('.ad')}")  # True
    print(f"search('b..'): {word_dict.search('b..')}")  # True
    print(f"search('b.d'): {word_dict.search('b.d')}")  # True
    print(f"search('...'): {word_dict.search('...')}")  # True
    print(f"search('..'): {word_dict.search('..')}")    # False
    
    # Test iterative version
    print("\nIterative version:")
    word_dict_iter = WordDictionaryIterative()
    word_dict_iter.addWord("bad")
    word_dict_iter.addWord("dad")
    print(f"search('.ad'): {word_dict_iter.search('.ad')}")  # True

