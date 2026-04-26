/*
 * Problem: Invert Binary Tree (LeetCode 226)
 * 
 * Given the root of a binary tree, invert the tree, and return its root.
 * Invert means swap left and right children at every node.
 * 
 * Time Complexity: O(n) - visit every node once
 * Space Complexity: O(h) - recursion stack, where h is height
 */

#include <iostream>
#include <queue>
#include "tree_node.h"

class Solution {
public:
    // Solution 1: Recursive DFS
    // Time: O(n), Space: O(h)
    TreeNode* invertTreeRecursive(TreeNode* root) {
        if (root == nullptr) return nullptr;
        
        // Swap left and right children
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        // Recursively invert subtrees
        invertTreeRecursive(root->left);
        invertTreeRecursive(root->right);
        
        return root;
    }
    
    // Solution 2: Iterative BFS
    // Time: O(n), Space: O(w) where w is max width
    TreeNode* invertTreeBFS(TreeNode* root) {
        if (root == nullptr) return nullptr;
        
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Swap children
            TreeNode* temp = node->left;
            node->left = node->right;
            node->right = temp;
            
            // Add children to queue
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        return root;
    }
    
    // Solution 3: Iterative DFS (using stack)
    // Time: O(n), Space: O(h)
    TreeNode* invertTreeDFS(TreeNode* root) {
        if (root == nullptr) return nullptr;
        
        std::stack<TreeNode*> stk;
        stk.push(root);
        
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            
            // Swap children
            std::swap(node->left, node->right);
            
            // Add children to stack
            if (node->left) stk.push(node->left);
            if (node->right) stk.push(node->right);
        }
        
        return root;
    }
    
    // Main function using recursive approach
    TreeNode* invertTree(TreeNode* root) {
        return invertTreeRecursive(root);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [4,2,7,1,3,6,9]
    TreeNode* root1 = buildTree({4, 2, 7, 1, 3, 6, 9});
    std::cout << "Original tree:" << std::endl;
    printTreeVisual(root1);
    root1 = sol.invertTree(root1);
    std::cout << "\nInverted tree:" << std::endl;
    printTreeVisual(root1);
    deleteTree(root1);
    
    // Test case 2: [2,1,3]
    TreeNode* root2 = buildTree({2, 1, 3});
    std::cout << "\nOriginal tree: ";
    printTree(root2);
    root2 = sol.invertTree(root2);
    std::cout << "Inverted tree: ";
    printTree(root2);
    deleteTree(root2);
    
    // Test case 3: Empty tree
    TreeNode* root3 = nullptr;
    root3 = sol.invertTree(root3);
    std::cout << "\nEmpty tree: ";
    printTree(root3);
    
    // Test case 4: Single node
    TreeNode* root4 = new TreeNode(1);
    root4 = sol.invertTree(root4);
    std::cout << "Single node: ";
    printTree(root4);
    deleteTree(root4);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

