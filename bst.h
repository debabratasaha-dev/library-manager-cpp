#pragma once
#include <vector>
#include "book.h"

class TreeNode {
public:
    Book data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Book val);
};

TreeNode* insert(TreeNode* root, Book val);
TreeNode* builtBST(std::vector<Book>& nums, int st, int end);
TreeNode* search(TreeNode* root, int key);
void inorderPrint(TreeNode* root);
TreeNode* getInorderSuccessor(TreeNode* root);
TreeNode* deleteNode(TreeNode* root, int key);
