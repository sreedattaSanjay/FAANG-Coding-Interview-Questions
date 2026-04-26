#include<iostream>
#include <algorithm>
using namespace std;
struct Tree{
    Tree* left;
    Tree* right;
    int val;
    Tree():val(0),left(nullptr),right(nullptr){}
    Tree(int x): val(x),left(nullptr),right(nullptr){}
    Tree(int x, Tree* left, Tree* right): val(x),left(left),right(right){}};

Tree* invert_tree(Tree* root){
    if(!root) return nullptr;
    Tree * temp=root->left;
    root->left=root->right;
    root->right=temp;
    invert_tree(root->left);
    invert_tree(root->right);
    return root;
}
//traverse the tree and print the values
void print_tree(Tree* root){
    if(!root) return;
    cout<<root->val<<" ";
    print_tree(root->left);
    print_tree(root->right);
}
int main(){
    Tree* root=new Tree(4);
    root->left=new Tree(2);
    root->right=new Tree(7);
    root->left->left=new Tree(1);
    root->left->right=new Tree(3);
    root->right->left=new Tree(6);
    root->right->right=new Tree(9);
    print_tree(invert_tree(root));
    return 0;
}