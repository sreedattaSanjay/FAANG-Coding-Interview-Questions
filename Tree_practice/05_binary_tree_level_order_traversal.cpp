#include <iostream>
#include<vector>
#include "tree.h"
using namespace std;
vector<vector<int>> level_order_traversal(Tree *root){
    vector<vector<int>> result;
    if(!root) return result;

    queue<Tree*> q;
    q.push(root);

    while(!q.empty()){
        int qsize=q.size();
        vector<int> current_level;
        for(int i=0;i<qsize;i++){
            Tree* node=q.front();
            q.pop();
            current_level.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        result.push_back(current_level);
    }
    return result;
}
int main(){
    Tree* root=new Tree(3);
    root->left=new Tree(9);
    root->right=new Tree(20);
    root->right->left=new Tree(15);
    root->right->right=new Tree(7);
    vector<vector<int>> result=level_order_traversal(root);
    for(int i=0;i<result.size();i++){

        for(int j=0;j<result[i].size();j++){
            cout<<result[i][j]<<" ";
        }

    }
    return 0;
}   