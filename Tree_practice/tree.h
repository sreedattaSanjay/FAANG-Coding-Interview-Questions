#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

struct Tree {
    int val;
    Tree* left;
    Tree* right;
    
    Tree() : val(0), left(nullptr), right(nullptr) {}
    Tree(int x) : val(x), left(nullptr), right(nullptr) {}
    Tree(int x, Tree* left, Tree* right) : val(x), left(left), right(right) {}
};

// Alias to match LeetCode naming convention
using TreeNode = Tree;

// Helper: Print tree (inorder)
inline void printInorder(Tree* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// Helper: Print tree level by level
inline void printLevelOrder(Tree* root) {
    if (!root) return;
    queue<Tree*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Tree* node = q.front();
            q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

#endif // TREE_H

