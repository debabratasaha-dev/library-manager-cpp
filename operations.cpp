#include <vector>
#include "book.h"
#include "BST.h"
#include "operations.h"
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

// string Uppercase conversion
string toUpperCase(string str) {
    for (auto &charecter : str)
    {
        charecter = toupper(charecter);
    }
    return str;
}


// Save the current vector<Book> to library.dat (binary)
void savetoLibrary(const vector<Book>& books, const string& filename) {
    ofstream ofs(filename, ios::binary | ios::trunc);
    if (!ofs) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    size_t n = books.size();
    ofs.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (const auto& book : books) {
        ofs.write(reinterpret_cast<const char*>(&book.id), sizeof(book.id));
        size_t len = book.title.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(book.title.c_str(), len);
        len = book.author.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(book.author.c_str(), len);
        ofs.write(reinterpret_cast<const char*>(&book.year), sizeof(book.year));
    }
    ofs.close();
}

// Add a new book
void addBook(vector<Book>& books, TreeNode*& root) {
    int id, year;
    string title, author;
    cout << "Enter Book ID: ";
    cin >> id;
    for (const auto& b : books) if (b.id == id) { cout << "ID already exists!\n"; return; }
    cin.ignore();
    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Year: "; cin >> year;
    Book newBook(id, title, author, year);

    // Add to vector
    books.push_back(newBook);

    // Insert into BST (simple insert)
    root = insert(root, newBook);
    cout << "Book added!\n";
}

// View all books sorted by ID
void viewAllBooks(TreeNode* books) {
    if (books == nullptr) {
        cout << "No books available.\n";
        return;
    }
    inorderPrint(books); // This will print all books in preorder traversal
}

// Search by ID using BST for O(log n) time complexity
void searchBook(TreeNode* root, int id) {
    TreeNode* result = search(root, id);
    if (result) {
        result->data.print();
    } else {
        cout << "Book not found!\n";
    }
}

// Delete book by ID
void deleteBook(vector<Book>& books, TreeNode*& root, int id) {
    cout << "Deleting book with ID: " << id << endl;
    auto it = find_if(books.begin(), books.end(), [id](const Book& b){ return b.id == id; });
    if (it == books.end()) { cout << "Book not found!\n"; return; }
    books.erase(it);
    // deleting from BST
    root = deleteNode(root, id);
    if (root == nullptr) {
        cout << "The list is completely empty after this deletion.\n";
        return;
    } else cout << "Book deleted!\n";
}

// Update book by ID
void updateBook(vector<Book>& books, int id) {
    for (auto& b : books) if (b.id == id) {
        cout << "Enter new Title: "; cin.ignore(); getline(cin, b.title);
        cout << "Enter new Author: "; getline(cin, b.author);
        cout << "Enter new Year: "; cin >> b.year;
        cout << "Book updated!\n"; return;
    }
    cout << "Book not found!\n";
}

// Comparators for sorting
bool cmpTitle(const Book& a, const Book& b) { return a.title < b.title; }
bool cmpAuthor(const Book& a, const Book& b) { return a.author < b.author; }
bool cmpYear(const Book& a, const Book& b) { return a.year < b.year; }

// Sort and display by Title/Author/Year
double getValidSortMode() {
    int mode;
    while (true) {
        cout << "Sort by: 1. Title  2. Author  3. Year\nEnter option: ";
        if (!(cin >> mode) || mode < 1 || mode > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter 1, 2, or 3.\n";
        } else {
            break;
        }
    }
    return mode;
}

void sortAndDisplay(vector<Book> books, int mode) {
    if (mode == 1) sort(books.begin(), books.end(), cmpTitle);
    else if (mode == 2) sort(books.begin(), books.end(), cmpAuthor);
    else if (mode == 3) sort(books.begin(), books.end(), cmpYear);
    for (const auto& b : books) b.print();
}

// advance search by Title/Author (case-insensitive)
void searchByTitleAuthor(const vector<Book>& books, string query, int mode) {
    vector<const Book*> results;
    query = toUpperCase(query);
    for (const auto& b : books) {
        if ((mode == 1 && toUpperCase(b.title).find(query) != string::npos) ||
            (mode == 2 && toUpperCase(b.author).find(query) != string::npos)) {
            results.push_back(&b);
        }
    }
    if (results.empty()) {
        cout << "No books found matching the query.\n";
    } else {
        for (const Book* bookPtr : results) {
            bookPtr->print();
        }
    }
}

double getValidSearchMode() {
    int mode;
    while (true) {
        cout << "Search by: 1. Title  2. Author\nEnter option: ";
        if (!(cin >> mode) || mode < 1 || mode > 2) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter 1 or 2.\n";
        } else {
            break;
        }
    }
    return mode;
}