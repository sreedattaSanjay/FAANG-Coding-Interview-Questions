#include "tree.h"
#include<iostream>

using namespace std;


int depth(Tree* root){
    if(!root) return 0;
    int left= depth(root->left);
    int right= depth(root->right);
    return max(left,right)+1;
} 
bool isTreeBalanced(Tree* root){
    if(!root) return true;
    int left_depth=depth(root->left);
    int right_depth=depth(root->right);
    if(abs(left_depth-right_depth)>1) return false;
    return isTreeBalanced(root->left) && isTreeBalanced(root->right);
}



void runTest(int testNum, Tree* root, bool expected, const string& description) {
    bool result = isTreeBalanced(root);
    cout << "Test " << testNum << ": " << description << endl;
    cout << "  Expected: " << (expected ? "true" : "false") 
         << " | Got: " << (result ? "true" : "false")
         << " | " << (result == expected ? "✓ PASS" : "✗ FAIL") << endl;
}

int main(){
    cout << "=== Balanced Binary Tree Test Cases ===" << endl << endl;
    
    // Test 1: Balanced complete tree
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    Tree* t1 = new Tree(1);
    t1->left = new Tree(2);
    t1->right = new Tree(3);
    t1->left->left = new Tree(4);
    t1->left->right = new Tree(5);
    t1->right->left = new Tree(6);
    t1->right->right = new Tree(7);
    runTest(1, t1, true, "Balanced complete tree");
    
    // Test 2: Empty tree (null)
    Tree* t2 = nullptr;
    runTest(2, t2, true, "Empty tree (null)");
    
    // Test 3: Single node
    Tree* t3 = new Tree(1);
    runTest(3, t3, true, "Single node");
    
    // Test 4: Left-skewed unbalanced tree
    //    1
    //   /
    //  2
    // /
    // 3
    Tree* t4 = new Tree(1);
    t4->left = new Tree(2);
    t4->left->left = new Tree(3);
    runTest(4, t4, false, "Left-skewed unbalanced tree");
    
    // Test 5: Right-skewed unbalanced tree
    // 1
    //  \
    //   2
    //    \
    //     3
    Tree* t5 = new Tree(1);
    t5->right = new Tree(2);
    t5->right->right = new Tree(3);
    runTest(5, t5, false, "Right-skewed unbalanced tree");
    
    // Test 6: Unbalanced at root (LeetCode Example 2)
    //        1
    //       / \
    //      2   2
    //     / \
    //    3   3
    //   / \
    //  4   4
    Tree* t6 = new Tree(1);
    t6->left = new Tree(2);
    t6->right = new Tree(2);
    t6->left->left = new Tree(3);
    t6->left->right = new Tree(3);
    t6->left->left->left = new Tree(4);
    t6->left->left->right = new Tree(4);
    runTest(6, t6, false, "Unbalanced at root (depth diff = 2)");
    
    // Test 7: Balanced but not complete
    //      1
    //     / \
    //    2   3
    //   /
    //  4
    Tree* t7 = new Tree(1);
    t7->left = new Tree(2);
    t7->right = new Tree(3);
    t7->left->left = new Tree(4);
    runTest(7, t7, true, "Balanced but not complete (diff = 1 is OK)");
    
    // Test 8: Two nodes - left child only
    //   1
    //  /
    // 2
    Tree* t8 = new Tree(1);
    t8->left = new Tree(2);
    runTest(8, t8, true, "Two nodes - left child only");
    
    // Test 9: Unbalanced deep in the tree
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    //   /
    //  6
    // /
    // 7
    Tree* t9 = new Tree(1);
    t9->left = new Tree(2);
    t9->right = new Tree(3);
    t9->left->left = new Tree(4);
    t9->left->right = new Tree(5);
    t9->left->left->left = new Tree(6);
    t9->left->left->left->left = new Tree(7);
    runTest(9, t9, false, "Unbalanced deep in left subtree");
    
    // Test 10: Perfectly balanced 3-level tree
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Tree* t10 = new Tree(1);
    t10->left = new Tree(2);
    t10->right = new Tree(3);
    t10->left->left = new Tree(4);
    t10->left->right = new Tree(5);
    runTest(10, t10, true, "Balanced tree with uneven leaves");
    
    cout << endl << "=== All tests completed ===" << endl;
    
    return 0;
}