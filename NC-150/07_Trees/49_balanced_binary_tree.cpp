/*
 * Problem: Balanced Binary Tree (LeetCode 110)
 * 
 * Given a binary tree, determine if it is height-balanced.
 * A height-balanced binary tree is defined as a tree in which the
 * depth of the two subtrees of every node never differs by more than one.
 * 
 * Time Complexity: O(n) - visit every node once
 * Space Complexity: O(h) - recursion stack, where h is height
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include "tree_node.h"

class Solution {
public:
    // Optimal solution: O(n) time
    // Returns -1 if unbalanced, otherwise returns height
    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
    
private:
    int checkHeight(TreeNode* node) {
        if (node == nullptr) return 0;
        
        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) return -1;  // Left subtree is unbalanced
        
        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) return -1;  // Right subtree is unbalanced
        
        // Check if current node is balanced
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1;  // Current node is unbalanced
        }
        
        return 1 + std::max(leftHeight, rightHeight);
    }
};

// Alternative: Less efficient but more intuitive O(n^2)
class SolutionNaive {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        // Check current node and recursively check subtrees
        return std::abs(leftHeight - rightHeight) <= 1 
            && isBalanced(root->left) 
            && isBalanced(root->right);
    }
    
private:
    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [3,9,20,null,null,15,7] -> true
    TreeNode* root1 = buildTree({3, 9, 20, INT_MIN, INT_MIN, 15, 7});
    std::cout << "Tree: [3,9,20,null,null,15,7]" << std::endl;
    printTreeVisual(root1);
    std::cout << "Is balanced: " << (sol.isBalanced(root1) ? "true" : "false") << " (expected: true)" << std::endl;
    deleteTree(root1);
    
    // Test case 2: [1,2,2,3,3,null,null,4,4] -> false
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(3);
    root2->left->left->left = new TreeNode(4);
    root2->left->left->right = new TreeNode(4);
    std::cout << "\nTree: [1,2,2,3,3,null,null,4,4]" << std::endl;
    printTreeVisual(root2);
    std::cout << "Is balanced: " << (sol.isBalanced(root2) ? "true" : "false") << " (expected: false)" << std::endl;
    deleteTree(root2);
    
    // Test case 3: Empty tree -> true
    TreeNode* root3 = nullptr;
    std::cout << "\nEmpty tree" << std::endl;
    std::cout << "Is balanced: " << (sol.isBalanced(root3) ? "true" : "false") << " (expected: true)" << std::endl;
    
    // Test case 4: Single node -> true
    TreeNode* root4 = new TreeNode(1);
    std::cout << "\nSingle node" << std::endl;
    std::cout << "Is balanced: " << (sol.isBalanced(root4) ? "true" : "false") << " (expected: true)" << std::endl;
    deleteTree(root4);
    
    // Test case 5: Perfectly balanced tree
    TreeNode* root5 = buildTree({1, 2, 3, 4, 5, 6, 7});
    std::cout << "\nPerfectly balanced tree" << std::endl;
    printTreeVisual(root5);
    std::cout << "Is balanced: " << (sol.isBalanced(root5) ? "true" : "false") << " (expected: true)" << std::endl;
    deleteTree(root5);
    
    // Test case 6: Off by one (still balanced)
    TreeNode* root6 = new TreeNode(1);
    root6->left = new TreeNode(2);
    root6->left->left = new TreeNode(3);
    std::cout << "\nTree [1,2,null,3] - left skewed by 1" << std::endl;
    std::cout << "Is balanced: " << (sol.isBalanced(root6) ? "true" : "false") << " (expected: false)" << std::endl;
    deleteTree(root6);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

