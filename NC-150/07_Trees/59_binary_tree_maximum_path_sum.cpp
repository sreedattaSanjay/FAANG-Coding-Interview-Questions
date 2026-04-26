/*
 * LeetCode 124: Binary Tree Maximum Path Sum
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/
 * 
 * A path in a binary tree is a sequence of nodes where each pair of adjacent 
 * nodes in the sequence has an edge connecting them. A node can only appear 
 * in the sequence at most once. Note that the path does not need to pass 
 * through the root.
 * 
 * The path sum of a path is the sum of the node's values in the path.
 * Given the root of a binary tree, return the maximum path sum of any non-empty path.
 * 
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack, where h is tree height
 */

#include <iostream>
#include <algorithm>
#include <climits>
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
    int maxSum;
    
    // Returns the maximum path sum starting from this node going DOWN
    int maxGain(TreeNode* node) {
        if (!node) return 0;
        
        // Recursively get max gain from left and right subtrees
        // If gain is negative, we don't include that path (take 0 instead)
        int leftGain = max(0, maxGain(node->left));
        int rightGain = max(0, maxGain(node->right));
        
        // Path through current node: left -> node -> right
        int pathSum = node->val + leftGain + rightGain;
        
        // Update global maximum
        maxSum = max(maxSum, pathSum);
        
        // Return max gain if we continue path through this node (can only go one direction)
        return node->val + max(leftGain, rightGain);
    }
    
public:
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        maxGain(root);
        return maxSum;
    }
};

int main() {
    // Test case 1: [1,2,3] -> 6 (path: 2->1->3)
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    
    // Test case 2: [-10,9,20,null,null,15,7] -> 42 (path: 15->20->7)
    TreeNode* root2 = new TreeNode(-10);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);
    
    Solution sol;
    cout << "Test 1: " << sol.maxPathSum(root1) << endl;  // Expected: 6
    cout << "Test 2: " << sol.maxPathSum(root2) << endl;  // Expected: 42
    
    return 0;
}

