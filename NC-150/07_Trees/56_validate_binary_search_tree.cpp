/*
 * LeetCode 98: Validate Binary Search Tree
 * https://leetcode.com/problems/validate-binary-search-tree/
 * 
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * A valid BST is defined as follows:
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 * 
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack, where h is tree height
 */

#include <iostream>
#include <climits>
#include <stack>
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
    // Solution 1: Recursive with range validation
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    
    // Solution 2: Inorder traversal (should be strictly increasing)
    bool isValidBSTInorder(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        
        while (root || !stk.empty()) {
            // Go to leftmost node
            while (root) {
                stk.push(root);
                root = root->left;
            }
            
            root = stk.top();
            stk.pop();
            
            // Check if current value is greater than previous
            if (prev && root->val <= prev->val) {
                return false;
            }
            
            prev = root;
            root = root->right;
        }
        
        return true;
    }
    
private:
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        
        // Current node must be within valid range
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        // Left subtree must be less than current, right must be greater
        return validate(node->left, minVal, node->val) &&
               validate(node->right, node->val, maxVal);
    }
};

// Alternative: Using pointers instead of long values
class SolutionPointer {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }
    
private:
    bool validate(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        if (!node) return true;
        
        if (minNode && node->val <= minNode->val) return false;
        if (maxNode && node->val >= maxNode->val) return false;
        
        return validate(node->left, minNode, node) &&
               validate(node->right, node, maxNode);
    }
};

int main() {
    // Test case 1: [2,1,3] -> true
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);
    
    // Test case 2: [5,1,4,null,null,3,6] -> false (4 is in right subtree but < 5)
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);
    
    Solution sol;
    cout << "Test 1 (Recursive): " << (sol.isValidBST(root1) ? "true" : "false") << endl;   // true
    cout << "Test 1 (Inorder): " << (sol.isValidBSTInorder(root1) ? "true" : "false") << endl;
    cout << "Test 2 (Recursive): " << (sol.isValidBST(root2) ? "true" : "false") << endl;   // false
    cout << "Test 2 (Inorder): " << (sol.isValidBSTInorder(root2) ? "true" : "false") << endl;
    
    return 0;
}

