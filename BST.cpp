#include "bst.h"
#include <iostream>
#include <vector>
#include "book.h"
using namespace std;

TreeNode::TreeNode(Book val) {
    data = val;
    left = right = nullptr;
}

TreeNode* insert(TreeNode* root, Book val) {
    if (root == NULL) {
        return new TreeNode(val);
    }
    if (val.id < root->data.id) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

TreeNode* builtBST(vector<Book>& nums, int st, int end) {
    if (st > end) return nullptr;
    int mid = st + (end - st) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = builtBST(nums, st, mid - 1);
    root->right = builtBST(nums, mid + 1, end);
    return root;
}

TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (key < root->data.id) {
        return search(root->left, key);
    } else if (key > root->data.id) {
        return search(root->right, key);
    } else {
        return root;
    }
}

void inorderPrint(TreeNode* root) {
    if (root == nullptr) return;
    inorderPrint(root->left);
    root->data.print();
    inorderPrint(root->right);
}

TreeNode* getInorderSuccessor(TreeNode* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        cout << "invalid value (" << key << ") or empty tree\n";
        return nullptr;
    }
    if (key < root->data.id) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data.id) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode* IS = getInorderSuccessor(root->right);
            root->data = IS->data;
            root->right = deleteNode(root->right, IS->data.id);
        }
    }
    return root;
}
