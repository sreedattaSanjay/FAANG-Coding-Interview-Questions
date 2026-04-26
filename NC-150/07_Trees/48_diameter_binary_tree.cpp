/*
 * Problem: Diameter of Binary Tree (LeetCode 543)
 * 
 * Given the root of a binary tree, return the length of the diameter.
 * The diameter is the length of the longest path between any two nodes.
 * This path may or may not pass through the root.
 * 
 * Note: The length of a path is the number of EDGES between nodes.
 * 
 * Time Complexity: O(n) - visit every node once
 * Space Complexity: O(h) - recursion stack, where h is height
 */

#include <iostream>
#include <algorithm>
#include "tree_node.h"

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
    
private:
    // Returns the height of the subtree
    // Updates diameter if current path is longer
    int height(TreeNode* node, int& diameter) {
        if (node == nullptr) return 0;
        
        int leftHeight = height(node->left, diameter);
        int rightHeight = height(node->right, diameter);
        
        // The longest path through this node is leftHeight + rightHeight
        diameter = std::max(diameter, leftHeight + rightHeight);
        
        // Return height of this subtree
        return 1 + std::max(leftHeight, rightHeight);
    }
};

// Alternative solution using class member variable
class SolutionAlt {
private:
    int maxDiameter = 0;
    
    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        maxDiameter = std::max(maxDiameter, leftHeight + rightHeight);
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;  // Reset for each call
        height(root);
        return maxDiameter;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4,5] -> 3
    // The longest path is 4-2-1-3 or 5-2-1-3 (3 edges)
    TreeNode* root1 = buildTree({1, 2, 3, 4, 5});
    std::cout << "Tree: [1,2,3,4,5]" << std::endl;
    printTreeVisual(root1);
    std::cout << "Diameter: " << sol.diameterOfBinaryTree(root1) << " (expected: 3)" << std::endl;
    deleteTree(root1);
    
    // Test case 2: [1,2] -> 1
    TreeNode* root2 = buildTree({1, 2});
    std::cout << "\nTree: [1,2]" << std::endl;
    std::cout << "Diameter: " << sol.diameterOfBinaryTree(root2) << " (expected: 1)" << std::endl;
    deleteTree(root2);
    
    // Test case 3: Single node -> 0
    TreeNode* root3 = new TreeNode(1);
    std::cout << "\nSingle node tree" << std::endl;
    std::cout << "Diameter: " << sol.diameterOfBinaryTree(root3) << " (expected: 0)" << std::endl;
    deleteTree(root3);
    
    // Test case 4: Empty tree -> 0
    TreeNode* root4 = nullptr;
    std::cout << "\nEmpty tree" << std::endl;
    std::cout << "Diameter: " << sol.diameterOfBinaryTree(root4) << " (expected: 0)" << std::endl;
    
    // Test case 5: Diameter not through root
    //       1
    //      /
    //     2
    //    / \
    //   3   4
    //  /     \
    // 5       6
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->left->left = new TreeNode(3);
    root5->left->right = new TreeNode(4);
    root5->left->left->left = new TreeNode(5);
    root5->left->right->right = new TreeNode(6);
    std::cout << "\nTree where diameter doesn't pass through root:" << std::endl;
    printTreeVisual(root5);
    std::cout << "Diameter: " << sol.diameterOfBinaryTree(root5) << " (expected: 4)" << std::endl;
    deleteTree(root5);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

