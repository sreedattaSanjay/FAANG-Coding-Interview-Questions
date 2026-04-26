#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct Tree{
Tree* left;
Tree* right;
int val;
Tree(): val(0), left(nullptr), right(nullptr) {}
Tree(int x):val(x),left(nullptr),right(nullptr){}
Tree(int x,Tree* left,Tree* right):val(x),left(left),right(right){}
};

int max_depth(Tree* root){
if (!root){
return 0;}
return 1+max(max_depth(root->left),max_depth(root->right));
}

int max_depth_it(Tree* root){
if(!root) return 0;
queue<Tree*> q;
q.push(root);
int depth=0;

while(!q.empty())
{
int qsize=q.size();
depth++;
for(int i=0;i<qsize;i++){
Tree* node=q.front();
q.pop();
if(node->left) q.push(node->left);
if(node->right) q.push(node->right);
}
}
return depth;
}

int main(){
    Tree* root=new Tree(3);
    root->left=new Tree(9);
    root->right=new Tree(20);
    root->right->left=new Tree(15);
    root->right->right=new Tree(7);
    cout<<max_depth(root)<<endl;
    cout<<max_depth_it(root)<<endl;
    return 0;
}
