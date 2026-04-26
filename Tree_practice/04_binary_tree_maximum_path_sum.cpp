#include<iostream>
#include<algorithm>
#include "tree.h"
using namespace std;
class Solution {
    int maxSum;
    
    int maxGain(Tree* root) {
        if (!root) return 0;
        int left = max(0, maxGain(root->left));
        int right = max(0, maxGain(root->right));
        maxSum = max(maxSum, root->val + left + right);
        return root->val + max(left, right);
    }
    
public:
    int maxPathSum(Tree* root) {
        maxSum = INT_MIN;  // Initialize before recursion
        maxGain(root);
        return maxSum;
    }
};
int main(){
    Tree* root=new Tree(1);
    root->left=new Tree(2);
    root->right=new Tree(3);
    root->left->left=new Tree(4);
    root->left->right=new Tree(5);
    root->right->left=new Tree(6);
    root->right->right=new Tree(7);
    Solution sol;
    cout<<sol.maxPathSum(root)<<endl;
    return 0;
}