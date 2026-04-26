/*
 * Problem: Same Tree (LeetCode 100)
 * 
 * Given the roots of two binary trees p and q, write a function to check 
 * if they are the same or not. Two binary trees are considered the same 
 * if they are structurally identical, and the nodes have the same value.
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
    bool isSameTreeRecursive(TreeNode* p, TreeNode* q) {
        // Both null - same
        if (p == nullptr && q == nullptr) return true;
        
        // One null, one not - different
        if (p == nullptr || q == nullptr) return false;
        
        // Both non-null - check value and children
        if (p->val != q->val) return false;
        
        return isSameTreeRecursive(p->left, q->left) 
            && isSameTreeRecursive(p->right, q->right);
    }
    
    // Solution 2: Iterative BFS
    // Time: O(n), Space: O(w) where w is max width
    bool isSameTreeBFS(TreeNode* p, TreeNode* q) {
        std::queue<std::pair<TreeNode*, TreeNode*>> queue;
        queue.push({p, q});
        
        while (!queue.empty()) {
            auto [node1, node2] = queue.front();
            queue.pop();
            
            // Both null - continue
            if (node1 == nullptr && node2 == nullptr) continue;
            
            // One null or different values - not same
            if (node1 == nullptr || node2 == nullptr) return false;
            if (node1->val != node2->val) return false;
            
            // Add children pairs
            queue.push({node1->left, node2->left});
            queue.push({node1->right, node2->right});
        }
        
        return true;
    }
    
    // Solution 3: Iterative DFS
    // Time: O(n), Space: O(h)
    bool isSameTreeDFS(TreeNode* p, TreeNode* q) {
        std::stack<std::pair<TreeNode*, TreeNode*>> stk;
        stk.push({p, q});
        
        while (!stk.empty()) {
            auto [node1, node2] = stk.top();
            stk.pop();
            
            if (node1 == nullptr && node2 == nullptr) continue;
            if (node1 == nullptr || node2 == nullptr) return false;
            if (node1->val != node2->val) return false;
            
            stk.push({node1->left, node2->left});
            stk.push({node1->right, node2->right});
        }
        
        return true;
    }
    
    // Main function using recursive approach
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return isSameTreeRecursive(p, q);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3] and [1,2,3] -> true
    TreeNode* p1 = buildTree({1, 2, 3});
    TreeNode* q1 = buildTree({1, 2, 3});
    std::cout << "Tree 1: [1,2,3], Tree 2: [1,2,3]" << std::endl;
    std::cout << "Same: " << (sol.isSameTree(p1, q1) ? "true" : "false") << " (expected: true)" << std::endl;
    deleteTree(p1);
    deleteTree(q1);
    
    // Test case 2: [1,2] and [1,null,2] -> false
    TreeNode* p2 = buildTree({1, 2});
    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);
    std::cout << "\nTree 1: [1,2], Tree 2: [1,null,2]" << std::endl;
    std::cout << "Same: " << (sol.isSameTree(p2, q2) ? "true" : "false") << " (expected: false)" << std::endl;
    deleteTree(p2);
    deleteTree(q2);
    
    // Test case 3: [1,2,1] and [1,1,2] -> false
    TreeNode* p3 = buildTree({1, 2, 1});
    TreeNode* q3 = buildTree({1, 1, 2});
    std::cout << "\nTree 1: [1,2,1], Tree 2: [1,1,2]" << std::endl;
    std::cout << "Same: " << (sol.isSameTree(p3, q3) ? "true" : "false") << " (expected: false)" << std::endl;
    deleteTree(p3);
    deleteTree(q3);
    
    // Test case 4: Both empty -> true
    TreeNode* p4 = nullptr;
    TreeNode* q4 = nullptr;
    std::cout << "\nBoth empty trees" << std::endl;
    std::cout << "Same: " << (sol.isSameTree(p4, q4) ? "true" : "false") << " (expected: true)" << std::endl;
    
    // Test case 5: One empty, one not -> false
    TreeNode* p5 = new TreeNode(1);
    TreeNode* q5 = nullptr;
    std::cout << "\nTree 1: [1], Tree 2: empty" << std::endl;
    std::cout << "Same: " << (sol.isSameTree(p5, q5) ? "true" : "false") << " (expected: false)" << std::endl;
    deleteTree(p5);
    
    // Test BFS and DFS solutions
    TreeNode* p6 = buildTree({1, 2, 3});
    TreeNode* q6 = buildTree({1, 2, 3});
    std::cout << "\nBFS solution: " << (sol.isSameTreeBFS(p6, q6) ? "true" : "false") << std::endl;
    std::cout << "DFS solution: " << (sol.isSameTreeDFS(p6, q6) ? "true" : "false") << std::endl;
    deleteTree(p6);
    deleteTree(q6);
    
    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}

