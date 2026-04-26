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
    bool is_subtree(TreeNode* root, TreeNode* subroot) {
        if(!root) return false;
        if(is_sametree(root,subroot)) return true;
        return is_subtree(root->left,subroot) || is_subtree(root->right,subroot);
    }
    private:
    bool is_sametree(TreeNode* p, TreeNode* q) {
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;
        return is_sametree(p->left,q->left) && is_sametree(p->right,q->right);
    }
};

int main() {
    // Test case 1: root = [3,4,5,1,2], subRoot = [4,1,2] -> true
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(4);  
    root1->right = new TreeNode(5);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(2);
    TreeNode* subRoot1 = new TreeNode(4);
    subRoot1->left = new TreeNode(1);
    subRoot1->right = new TreeNode(2);
    Solution sol;
    cout << sol.is_subtree(root1, subRoot1) << endl;
    return 0;
}