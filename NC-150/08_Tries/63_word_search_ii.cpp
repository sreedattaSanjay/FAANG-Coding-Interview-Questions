/*
 * LeetCode 212: Word Search II
 * https://leetcode.com/problems/word-search-ii/
 * 
 * Given an m x n board of characters and a list of strings words, 
 * return all words on the board.
 * 
 * Each word must be constructed from letters of sequentially adjacent cells, 
 * where adjacent cells are horizontally or vertically neighboring. 
 * The same letter cell may not be used more than once in a word.
 * 
 * Approach: Build a Trie from words, then DFS on board using Trie for pruning
 * 
 * Time Complexity: O(m * n * 4^L) where L is max word length
 * Space Complexity: O(N * L) for Trie where N is number of words
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    string word;  // Store complete word at end node
    
    TrieNode() {
        word = "";
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Solution {
private:
    vector<string> result;
    
    void dfs(vector<vector<char>>& board, int row, int col, TrieNode* node) {
        // Bounds check
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) {
            return;
        }
        
        char c = board[row][col];
        
        // Already visited or no such prefix in Trie
        if (c == '#' || !node->children[c - 'a']) {
            return;
        }
        
        node = node->children[c - 'a'];
        
        // Found a word
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = "";  // Avoid duplicates
        }
        
        // Mark as visited
        board[row][col] = '#';
        
        // Explore all 4 directions
        dfs(board, row + 1, col, node);
        dfs(board, row - 1, col, node);
        dfs(board, row, col + 1, node);
        dfs(board, row, col - 1, node);
        
        // Restore cell
        board[row][col] = c;
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        result.clear();
        
        // Build Trie from words
        TrieNode* root = new TrieNode();
        for (const string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                int index = c - 'a';
                if (!node->children[index]) {
                    node->children[index] = new TrieNode();
                }
                node = node->children[index];
            }
            node->word = word;
        }
        
        // DFS from each cell
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(board, i, j, root);
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<vector<char>> board1 = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words1 = {"oath", "pea", "eat", "rain"};
    
    vector<string> result1 = sol.findWords(board1, words1);
    cout << "Test 1: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "\"" << result1[i] << "\"";
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // Expected: ["eat", "oath"]
    
    // Test case 2
    vector<vector<char>> board2 = {
        {'a','b'},
        {'c','d'}
    };
    vector<string> words2 = {"abcb"};
    
    vector<string> result2 = sol.findWords(board2, words2);
    cout << "Test 2: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "\"" << result2[i] << "\"";
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // Expected: []
    
    return 0;
}

