/*
 * LeetCode 297: Serialize and Deserialize Binary Tree
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 * 
 * Design an algorithm to serialize and deserialize a binary tree. 
 * Serialization is the process of converting a data structure into a 
 * sequence of bits so that it can be stored or transmitted.
 * 
 * Time Complexity: O(n) for both serialize and deserialize
 * Space Complexity: O(n) for storing the tree representation
 */

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // Solution 1: Level Order (BFS) approach
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "null";
        
        string result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                result += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            } else {
                result += "null,";
            }
        }
        
        // Remove trailing nulls for cleaner output
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "null" || data.empty()) return nullptr;
        
        stringstream ss(data);
        string token;
        
        getline(ss, token, ',');
        TreeNode* root = new TreeNode(stoi(token));
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty() && getline(ss, token, ',')) {
            TreeNode* node = q.front();
            q.pop();
            
            // Left child
            if (token != "null") {
                node->left = new TreeNode(stoi(token));
                q.push(node->left);
            }
            
            // Right child
            if (getline(ss, token, ',') && token != "null") {
                node->right = new TreeNode(stoi(token));
                q.push(node->right);
            }
        }
        
        return root;
    }
};

// Alternative: DFS Preorder approach
class CodecDFS {
public:
    string serialize(TreeNode* root) {
        string result;
        serializeHelper(root, result);
        return result;
    }
    
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return deserializeHelper(ss);
    }
    
private:
    void serializeHelper(TreeNode* node, string& result) {
        if (!node) {
            result += "null,";
            return;
        }
        
        result += to_string(node->val) + ",";
        serializeHelper(node->left, result);
        serializeHelper(node->right, result);
    }
    
    TreeNode* deserializeHelper(stringstream& ss) {
        string token;
        getline(ss, token, ',');
        
        if (token == "null" || token.empty()) return nullptr;
        
        TreeNode* node = new TreeNode(stoi(token));
        node->left = deserializeHelper(ss);
        node->right = deserializeHelper(ss);
        
        return node;
    }
};

// Helper to print tree (for verification)
void printTree(TreeNode* root) {
    if (!root) {
        cout << "null" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    cout << "[";
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node) {
            cout << node->val << ",";
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null,";
        }
    }
    cout << "]" << endl;
}

int main() {
    // Test case: [1,2,3,null,null,4,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    
    Codec codec;
    
    cout << "Original tree: ";
    printTree(root);
    
    string serialized = codec.serialize(root);
    cout << "Serialized: " << serialized << endl;
    
    TreeNode* deserialized = codec.deserialize(serialized);
    cout << "Deserialized tree: ";
    printTree(deserialized);
    
    return 0;
}

