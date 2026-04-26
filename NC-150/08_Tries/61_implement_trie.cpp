/*
 * LeetCode 208: Implement Trie (Prefix Tree)
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 * 
 * A trie (pronounced as "try") or prefix tree is a tree data structure used 
 * to efficiently store and retrieve keys in a dataset of strings.
 * 
 * Implement the Trie class:
 * - Trie() Initializes the trie object.
 * - void insert(String word) Inserts the string word into the trie.
 * - boolean search(String word) Returns true if word is in the trie.
 * - boolean startsWith(String prefix) Returns true if there is a previously 
 *   inserted string that has the prefix.
 * 
 * Time Complexity: O(m) for all operations where m is word/prefix length
 * Space Complexity: O(n * m) where n is number of words, m is average length
 */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Solution 1: Using array of fixed size (26 letters)
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

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
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
        TrieNode* node = findNode(word);
        return node != nullptr && node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        return findNode(prefix) != nullptr;
    }
    
private:
    TrieNode* findNode(const string& str) {
        TrieNode* node = root;
        for (char c : str) {
            int index = c - 'a';
            if (!node->children[index]) {
                return nullptr;
            }
            node = node->children[index];
        }
        return node;
    }
};

// Solution 2: Using HashMap (more flexible for Unicode)
class TrieNodeMap {
public:
    unordered_map<char, TrieNodeMap*> children;
    bool isEndOfWord = false;
};

class TrieMap {
private:
    TrieNodeMap* root;
    
public:
    TrieMap() {
        root = new TrieNodeMap();
    }
    
    void insert(string word) {
        TrieNodeMap* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNodeMap();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNodeMap* node = findNode(word);
        return node != nullptr && node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        return findNode(prefix) != nullptr;
    }
    
private:
    TrieNodeMap* findNode(const string& str) {
        TrieNodeMap* node = root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                return nullptr;
            }
            node = node->children[c];
        }
        return node;
    }
};

int main() {
    Trie trie;
    
    trie.insert("apple");
    cout << "search('apple'): " << (trie.search("apple") ? "true" : "false") << endl;      // true
    cout << "search('app'): " << (trie.search("app") ? "true" : "false") << endl;          // false
    cout << "startsWith('app'): " << (trie.startsWith("app") ? "true" : "false") << endl;  // true
    
    trie.insert("app");
    cout << "search('app'): " << (trie.search("app") ? "true" : "false") << endl;          // true
    
    // Test TrieMap
    cout << "\nUsing HashMap Trie:" << endl;
    TrieMap trieMap;
    trieMap.insert("hello");
    cout << "search('hello'): " << (trieMap.search("hello") ? "true" : "false") << endl;   // true
    cout << "search('hell'): " << (trieMap.search("hell") ? "true" : "false") << endl;     // false
    cout << "startsWith('hel'): " << (trieMap.startsWith("hel") ? "true" : "false") << endl; // true
    
    return 0;
}

