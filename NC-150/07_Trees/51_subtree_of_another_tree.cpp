/*
 * LeetCode 572: Subtree of Another Tree
 * https://leetcode.com/problems/subtree-of-another-tree/
 * 
 * Given the roots of two binary trees root and subRoot, return true if there 
 * is a subtree of root with the same structure and node values of subRoot 
 * and false otherwise.
 * 
 * Time Complexity: O(m * n) where m and n are sizes of root and subRoot trees
 * Space Complexity: O(h) recursion stack where h is height of root tree
 */

#include <iostream>
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // Empty subRoot is always a subtree
        if (!subRoot) return true;
        // Empty root cannot contain a non-empty subtree
        if (!root) return false;
        
        // Check if trees match at current position, or check subtrees
        if (isSameTree(root, subRoot)) return true;
        
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
    
private:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        if (p->val != q->val) return false;
        
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

// Alternative solution using string serialization
class SolutionStringMatch {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string rootStr = serialize(root);
        string subStr = serialize(subRoot);
        
        return rootStr.find(subStr) != string::npos;
    }
    
private:
    string serialize(TreeNode* node) {
        if (!node) return ",#";
        
        // Use comma prefix to avoid false matches (e.g., 12 vs 2)
        return "," + to_string(node->val) + serialize(node->left) + serialize(node->right);
    }
};

int main() {
    // Test case 1: root = [3,4,5,1,2], subRoot = [4,1,2] -> true
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(4);
    root1->right = new TreeNode(5);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(2);
    
    TreeNode* sub1 = new TreeNode(4);
    sub1->left = new TreeNode(1);
    sub1->right = new TreeNode(2);
    
    // Test case 2: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2] -> false
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(4);
    root2->right = new TreeNode(5);
    root2->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(2);
    root2->left->right->left = new TreeNode(0);  // Extra node makes it different
    
    Solution sol;
    cout << "Test 1: " << (sol.isSubtree(root1, sub1) ? "true" : "false") << endl;  // true
    cout << "Test 2: " << (sol.isSubtree(root2, sub1) ? "true" : "false") << endl;  // false
    
    SolutionStringMatch sol2;
    cout << "Test 1 (String): " << (sol2.isSubtree(root1, sub1) ? "true" : "false") << endl;
    
    return 0;
}

