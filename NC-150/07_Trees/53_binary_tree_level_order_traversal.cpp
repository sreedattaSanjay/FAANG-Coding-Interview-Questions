/*
 * LeetCode 102: Binary Tree Level Order Traversal
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * 
 * Given the root of a binary tree, return the level order traversal of its 
 * nodes' values. (i.e., from left to right, level by level).
 * 
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(n) - queue can hold at most n/2 nodes
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Solution 1: Iterative BFS
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    // Solution 2: Recursive DFS
    vector<vector<int>> levelOrderDFS(TreeNode* root) {
        vector<vector<int>> result;
        dfs(root, 0, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, int level, vector<vector<int>>& result) {
        if (!node) return;
        
        // Add new level if needed
        if (level >= result.size()) {
            result.push_back(vector<int>());
        }
        
        result[level].push_back(node->val);
        
        dfs(node->left, level + 1, result);
        dfs(node->right, level + 1, result);
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    // Test case: [3,9,20,null,null,15,7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    
    cout << "BFS: ";
    printResult(sol.levelOrder(root));  // Expected: [[3],[9,20],[15,7]]
    
    cout << "DFS: ";
    printResult(sol.levelOrderDFS(root));  // Expected: [[3],[9,20],[15,7]]
    
    return 0;
}

