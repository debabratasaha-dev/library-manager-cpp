#pragma once
#include <vector>
#include <string>
#include "book.h"
#include "bst.h"

std::string toUpperCase(std::string str);
void savetoLibrary(const std::vector<Book>& books, const std::string& filename);
void addBook(std::vector<Book>& books, TreeNode*& root);
void viewAllBooks(TreeNode* books);
void searchBook(TreeNode* root, int id);
void deleteBook(std::vector<Book>& books, TreeNode*& root, int id);
void updateBook(std::vector<Book>& books, int id);
bool cmpTitle(const Book& a, const Book& b);
bool cmpAuthor(const Book& a, const Book& b);
bool cmpYear(const Book& a, const Book& b);
double getValidSortMode();
void sortAndDisplay(std::vector<Book> books, int mode);
void searchByTitleAuthor(const std::vector<Book>& books, std::string query, int mode);
double getValidSearchMode();
