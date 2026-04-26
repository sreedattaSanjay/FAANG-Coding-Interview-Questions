/*
 * LeetCode 230: Kth Smallest Element in a BST
 * https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 * 
 * Given the root of a binary search tree, and an integer k, return the kth 
 * smallest value (1-indexed) of all the values of the nodes in the tree.
 * 
 * Key Insight: Inorder traversal of BST gives elements in sorted order
 * 
 * Time Complexity: O(H + k) where H is tree height
 * Space Complexity: O(H) for recursion/stack
 */

#include <iostream>
#include <stack>
#include <vector>
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
    // Solution 1: Iterative Inorder Traversal (Optimal - stops early)
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        
        while (root || !stk.empty()) {
            // Go to leftmost node
            while (root) {
                stk.push(root);
                root = root->left;
            }
            
            root = stk.top();
            stk.pop();
            
            // Found kth smallest
            if (--k == 0) {
                return root->val;
            }
            
            root = root->right;
        }
        
        return -1;  // k is larger than tree size
    }
    
    // Solution 2: Recursive Inorder (collects all elements first)
    int kthSmallestRecursive(TreeNode* root, int k) {
        vector<int> sorted;
        inorder(root, sorted);
        return sorted[k - 1];
    }
    
    // Solution 3: Optimized Recursive (stops early)
    int kthSmallestOptimized(TreeNode* root, int k) {
        int count = 0;
        int result = 0;
        inorderOptimized(root, k, count, result);
        return result;
    }
    
private:
    void inorder(TreeNode* node, vector<int>& sorted) {
        if (!node) return;
        inorder(node->left, sorted);
        sorted.push_back(node->val);
        inorder(node->right, sorted);
    }
    
    void inorderOptimized(TreeNode* node, int k, int& count, int& result) {
        if (!node) return;
        
        inorderOptimized(node->left, k, count, result);
        
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        
        inorderOptimized(node->right, k, count, result);
    }
};

int main() {
    // Test case 1: [3,1,4,null,2], k = 1 -> 1
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->right = new TreeNode(2);
    
    // Test case 2: [5,3,6,2,4,null,null,1], k = 3 -> 3
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->left->left->left = new TreeNode(1);
    
    Solution sol;
    cout << "Test 1 (k=1): " << sol.kthSmallest(root1, 1) << endl;  // 1
    cout << "Test 2 (k=3): " << sol.kthSmallest(root2, 3) << endl;  // 3
    cout << "Test 2 (k=3, Optimized): " << sol.kthSmallestOptimized(root2, 3) << endl;  // 3
    
    return 0;
}

