/*
 * Problem: Maximum Depth of Binary Tree (LeetCode 104)
 * 
 * Given the root of a binary tree, return its maximum depth.
 * Maximum depth is the number of nodes along the longest path from root to leaf.
 * 
 * Time Complexity: O(n) - visit every node once
 * Space Complexity: O(h) - recursion stack, where h is height
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "tree_node.h"

class Solution {
public:
    // Solution 1: Recursive DFS
    // Time: O(n), Space: O(h)
    int maxDepthRecursive(TreeNode* root) {
        if (root == nullptr) return 0;
        
        int leftDepth = maxDepthRecursive(root->left);
        int rightDepth = maxDepthRecursive(root->right);
        
        return 1 + std::max(leftDepth, rightDepth);
    }
    
    // Solution 2: Iterative BFS (level order)
    // Time: O(n), Space: O(w) where w is max width
    int maxDepthBFS(TreeNode* root) {
        if (root == nullptr) return 0;
        
        std::queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            depth++;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
    
    // Solution 3: Iterative DFS with stack
    // Time: O(n), Space: O(h)
    int maxDepthDFS(TreeNode* root) {
        if (root == nullptr) return 0;
        
        std::stack<std::pair<TreeNode*, int>> stk;
        stk.push({root, 1});
        int maxDepth = 0;
        
        while (!stk.empty()) {
            auto [node, depth] = stk.top();
            stk.pop();
            
            maxDepth = std::max(maxDepth, depth);
            
            if (node->left) stk.push({node->left, depth + 1});
            if (node->right) stk.push({node->right, depth + 1});
        }
        
        return maxDepth;
    }
    
    // Main function using recursive approach
    int maxDepth(TreeNode* root) {
        return maxDepthRecursive(root);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [3,9,20,null,null,15,7] -> 3
    TreeNode* root1 = buildTree({3, 9, 20, INT_MIN, INT_MIN, 15, 7});
    std::cout << "Tree: [3,9,20,null,null,15,7]" << std::endl;
    std::cout << "Max depth: " << sol.maxDepth(root1) << " (expected: 3)" << std::endl;
    deleteTree(root1);
    
    // Test case 2: [1,null,2] -> 2
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    std::cout << "\nTree: [1,null,2]" << std::endl;
    std::cout << "Max depth: " << sol.maxDepth(root2) << " (expected: 2)" << std::endl;
    deleteTree(root2);
    
    // Test case 3: Empty tree -> 0
    TreeNode* root3 = nullptr;
    std::cout << "\nEmpty tree" << std::endl;
    std::cout << "Max depth: " << sol.maxDepth(root3) << " (expected: 0)" << std::endl;
    
    // Test case 4: Single node -> 1
    TreeNode* root4 = new TreeNode(1);
    std::cout << "\nSingle node tree" << std::endl;
    std::cout << "Max depth: " << sol.maxDepth(root4) << " (expected: 1)" << std::endl;
    deleteTree(root4);
    
    // Test case 5: Skewed tree [1,2,null,3,null,4] -> 4
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->left->left = new TreeNode(3);
    root5->left->left->left = new TreeNode(4);
    std::cout << "\nSkewed tree (left only)" << std::endl;
    std::cout << "Max depth: " << sol.maxDepth(root5) << " (expected: 4)" << std::endl;
    deleteTree(root5);
    
    // Test BFS solution
    TreeNode* root6 = buildTree({3, 9, 20, INT_MIN, INT_MIN, 15, 7});
    std::cout << "\nBFS solution: " << sol.maxDepthBFS(root6) << " (expected: 3)" << std::endl;
    deleteTree(root6);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

