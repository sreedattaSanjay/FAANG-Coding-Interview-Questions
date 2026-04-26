#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <vector>
#include <queue>
#include <iostream>
#include <string>

// Standard TreeNode definition
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// Build tree from level-order array (using -1 for null, or INT_MIN)
TreeNode* buildTree(const std::vector<int>& values, int nullValue = INT_MIN) {
    if (values.empty() || values[0] == nullValue) return nullptr;
    
    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        // Left child
        if (i < values.size() && values[i] != nullValue) {
            node->left = new TreeNode(values[i]);
            q.push(node->left);
        }
        i++;
        
        // Right child
        if (i < values.size() && values[i] != nullValue) {
            node->right = new TreeNode(values[i]);
            q.push(node->right);
        }
        i++;
    }
    
    return root;
}

// Print tree in level-order format
void printTree(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "[]" << std::endl;
        return;
    }
    
    std::queue<TreeNode*> q;
    q.push(root);
    std::cout << "[";
    bool first = true;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (!first) std::cout << ", ";
        first = false;
        
        if (node == nullptr) {
            std::cout << "null";
        } else {
            std::cout << node->val;
            q.push(node->left);
            q.push(node->right);
        }
    }
    std::cout << "]" << std::endl;
}

// Print tree in a visual format
void printTreeVisual(TreeNode* root, std::string prefix = "", bool isLeft = true) {
    if (root == nullptr) return;
    
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << root->val << std::endl;
    
    printTreeVisual(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTreeVisual(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

// Delete tree and free memory
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

#endif // TREE_NODE_H

