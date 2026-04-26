#include <algorithm>
#include<iostream>
#include <queue>
using namespace std;

struct Tree{
    Tree* left;
    Tree* right;
    int val;\
    Tree():val(0),left(nullptr),right(nullptr){}
    Tree(int x): val(x),left(nullptr),right(nullptr){}
    Tree(int x, Tree* left, Tree* right): val(x),left(left),right(right){}};

bool is_sameTree(Tree *a, Tree*b){
    if(!a&&!b) return true;
    if(!a||!b) return false;
    if (a->val != b->val) return false;
    return is_sameTree(a->left, b->left) && is_sameTree(a->right, b->right);
}

bool is_same_tre_it(Tree *a,Tree *b){
    if(!a&&!b) return true;
    if(!a||!b) return false;
    queue<Tree*> q;
    q.push(a);
    q.push(b);
    while(!q.empty()){
        Tree* node1=q.front();
        q.pop();
        Tree* node2=q.front();
        q.pop();
    }
    return true;
}

int main(){
    Tree* a=new Tree(1);
    a->left=new Tree(2);
    a->right=new Tree(3);
    Tree* b=new Tree(1);
    b->left=new Tree(2);
    b->right=new Tree(3);
    cout<<is_sameTree(a,b)<<endl;
    cout<<is_same_tre_it(a,b)<<endl;
    return 0;
}