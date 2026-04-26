/*
 * LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 * 
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) 
 * node of two given nodes in the BST.
 * 
 * Key Insight: In a BST, we can use the BST property to efficiently find LCA:
 * - If both p and q are less than root, LCA is in left subtree
 * - If both p and q are greater than root, LCA is in right subtree
 * - Otherwise, current node is the LCA (split point)
 * 
 * Time Complexity: O(h) where h is tree height
 * Space Complexity: O(1) for iterative, O(h) for recursive
 */

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Solution 1: Iterative (Optimal)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val) {
                // Both nodes in left subtree
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                // Both nodes in right subtree
                root = root->right;
            } else {
                // Found the split point (LCA)
                return root;
            }
        }
        return nullptr;
    }
    
    // Solution 2: Recursive
    TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestorRecursive(root->left, p, q);
        }
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestorRecursive(root->right, p, q);
        }
        
        return root;
    }
};

int main() {
    // Test case: [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8 -> 6
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    
    TreeNode* p1 = root->left;        // node 2
    TreeNode* q1 = root->right;       // node 8
    TreeNode* p2 = root->left;        // node 2
    TreeNode* q2 = root->left->right; // node 4
    
    Solution sol;
    
    TreeNode* lca1 = sol.lowestCommonAncestor(root, p1, q1);
    cout << "LCA(2,8): " << lca1->val << endl;  // Expected: 6
    
    TreeNode* lca2 = sol.lowestCommonAncestor(root, p2, q2);
    cout << "LCA(2,4): " << lca2->val << endl;  // Expected: 2
    
    return 0;
}

