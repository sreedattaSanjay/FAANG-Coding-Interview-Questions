/*
 * LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * 
 * Given two integer arrays preorder and inorder where preorder is the preorder 
 * traversal of a binary tree and inorder is the inorder traversal of the same tree, 
 * construct and return the binary tree.
 * 
 * Key Insight:
 * - Preorder: [root, left subtree, right subtree]
 * - Inorder: [left subtree, root, right subtree]
 * - First element in preorder is always the root
 * - Find root in inorder to split left and right subtrees
 * 
 * Time Complexity: O(n) with hashmap for inorder lookup
 * Space Complexity: O(n) for hashmap and recursion stack
 */

#include <iostream>
#include <vector>
#include <unordered_map>
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
private:
    unordered_map<int, int> inorderMap;  // value -> index mapping
    int preorderIdx;
    
    TreeNode* buildHelper(vector<int>& preorder, int inLeft, int inRight) {
        if (inLeft > inRight) return nullptr;
        
        // Pick the current root from preorder
        int rootVal = preorder[preorderIdx++];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find root position in inorder
        int inorderIdx = inorderMap[rootVal];
        
        // Build left subtree first (preorder is root-left-right)
        root->left = buildHelper(preorder, inLeft, inorderIdx - 1);
        root->right = buildHelper(preorder, inorderIdx + 1, inRight);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        preorderIdx = 0;
        
        // Build hashmap for O(1) lookup of inorder indices
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return buildHelper(preorder, 0, inorder.size() - 1);
    }
};

// Alternative: Without using class member variables
class SolutionAlt {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preIdx = 0;
        return build(preorder, inorderMap, preIdx, 0, inorder.size() - 1);
    }
    
private:
    TreeNode* build(vector<int>& preorder, unordered_map<int, int>& inorderMap,
                    int& preIdx, int inLeft, int inRight) {
        if (inLeft > inRight) return nullptr;
        
        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);
        
        int mid = inorderMap[rootVal];
        
        root->left = build(preorder, inorderMap, preIdx, inLeft, mid - 1);
        root->right = build(preorder, inorderMap, preIdx, mid + 1, inRight);
        
        return root;
    }
};

void printLevelOrder(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    cout << "[";
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node) {
            cout << node->val << " ";
            q.push(node->left);
            q.push(node->right);
        }
    }
    cout << "]" << endl;
}

int main() {
    // Test case: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    // Expected output: [3,9,20,null,null,15,7]
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    Solution sol;
    TreeNode* root = sol.buildTree(preorder, inorder);
    
    cout << "Constructed tree: ";
    printLevelOrder(root);  // [3 9 20 15 7 ]
    
    return 0;
}

