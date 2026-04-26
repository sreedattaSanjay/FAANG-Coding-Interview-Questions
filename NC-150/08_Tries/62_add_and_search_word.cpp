/*
 * LeetCode 211: Design Add and Search Words Data Structure
 * https://leetcode.com/problems/add-and-search-word-data-structure-design/
 * 
 * Design a data structure that supports adding new words and finding if a 
 * string matches any previously added string.
 * 
 * Implement the WordDictionary class:
 * - WordDictionary() Initializes the object.
 * - void addWord(word) Adds word to the data structure.
 * - bool search(word) Returns true if there is any string in the data structure 
 *   that matches word or false otherwise. word may contain dots '.' where dots 
 *   can be matched with any letter.
 * 
 * Time Complexity: 
 *   - addWord: O(m) where m is word length
 *   - search: O(m) for words without '.', O(26^m) worst case with '.'
 * Space Complexity: O(n * m) where n is number of words
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class WordDictionary {
private:
    TrieNode* root;
    
    bool searchHelper(const string& word, int index, TrieNode* node) {
        if (index == word.length()) {
            return node->isEndOfWord;
        }
        
        char c = word[index];
        
        if (c == '.') {
            // Wildcard: try all possible children
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && searchHelper(word, index + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        } else {
            // Regular character
            int childIndex = c - 'a';
            if (!node->children[childIndex]) {
                return false;
            }
            return searchHelper(word, index + 1, node->children[childIndex]);
        }
    }
    
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
    
    bool search(string word) {
        return searchHelper(word, 0, root);
    }
};

int main() {
    WordDictionary wordDict;
    
    wordDict.addWord("bad");
    wordDict.addWord("dad");
    wordDict.addWord("mad");
    
    cout << "search('pad'): " << (wordDict.search("pad") ? "true" : "false") << endl;  // false
    cout << "search('bad'): " << (wordDict.search("bad") ? "true" : "false") << endl;  // true
    cout << "search('.ad'): " << (wordDict.search(".ad") ? "true" : "false") << endl;  // true
    cout << "search('b..'): " << (wordDict.search("b..") ? "true" : "false") << endl;  // true
    cout << "search('b.d'): " << (wordDict.search("b.d") ? "true" : "false") << endl;  // true
    cout << "search('...'): " << (wordDict.search("...") ? "true" : "false") << endl;  // true
    cout << "search('..'): " << (wordDict.search("..") ? "true" : "false") << endl;    // false
    
    return 0;
}

