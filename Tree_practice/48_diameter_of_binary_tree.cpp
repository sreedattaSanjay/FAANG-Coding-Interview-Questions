#include "tree.h"
#include <iostream>
using namespace std;

int depth(Tree* root) {
    if (!root) return 0;
    return 1 + max(depth(root->left), depth(root->right));
}

int diameter_of_binary_tree(Tree* root) {
    if (!root) return 0;
    int left_depth = depth(root->left);
    int right_depth = depth(root->right);
    int diameter = left_depth + right_depth;
    int left_diameter = diameter_of_binary_tree(root->left);
    int right_diameter = diameter_of_binary_tree(root->right);

    return max(diameter, max(left_diameter, right_diameter));
}

int main() {
    Tree* root = new Tree(1);
    root->left = new Tree(2);
    root->right = new Tree(3);
    root->left->left = new Tree(4);
    root->left->right = new Tree(5);
    root->right->left = new Tree(6);
    root->right->right = new Tree(7);
    cout << diameter_of_binary_tree(root) << endl;
    return 0;
}
