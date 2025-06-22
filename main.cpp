#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "book.h"
#include "BST.h"
#include "operations.h"
using namespace std;

int main() {
    const string filename = "LibraryData.dat";
    vector<Book> books;
    // 1. Check if file exists
    if (!filesystem::exists(filename)) {
        cout << "File 'LibraryData.dat' does not exist. Creating a new file...\n";
        ofstream outfile(filename, ios::binary);
        if (!outfile) {
            cerr << "Error: Could not create 'LibraryData.dat'.\n";
            return 1;
        }
        outfile.close();
    } else {
        cout << "File 'LibraryData.dat' found. Loading data...\n";
    }

    // 2. Read from binary file and populate vector<Book>
    ifstream infile(filename, ios::binary);
    if (!infile) {
        cerr << "Error: Could not open 'LibraryData.dat' for reading.\n";
        return 1;
    }
    size_t n = 0;
    infile.read(reinterpret_cast<char*>(&n), sizeof(n));
    for (size_t i = 0; i < n; ++i) {
        int id, year;
        size_t len;
        string title, author;
        // Read id
        infile.read(reinterpret_cast<char*>(&id), sizeof(id));
        // Read title
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        title.resize(len);
        infile.read(&title[0], len);
        // Read author
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        author.resize(len);
        infile.read(&author[0], len);
        // Read year
        infile.read(reinterpret_cast<char*>(&year), sizeof(year));
        books.emplace_back(id, title, author, year);
    }
    infile.close();

    // 3. Sort vector by id (descending, as per overloaded operator)
    sort(books.begin(), books.end());

    // 4. Build BST from sorted array (assuming BST.h provides buildBSTfromSortedArray)
    TreeNode* root = nullptr;
    if (!books.empty()) {
        root = builtBST(books, 0, books.size() - 1);
    }

    cout << "Loaded " << books.size() << " books from file.\n";

    // Main menu loop
    int choice;
    do {
        cout << "\nLIBRARY MANAGEMENT SYSTEM MAIN MENU:\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Search Book by ID\n";
        cout << "4. View All Books\n";
        cout << "5. Sort by Title/Author/Year\n";
        cout << "6. Search by Title/Author\n";
        cout << "7. Save\n";
        cout << "8. Save and Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }
        int id;
        switch (choice) {
            case 1:
                addBook(books, root);
                break;
            case 2:
                cout << "Enter Book ID to search: ";
                cin >> id;
                deleteBook(books, root, id);
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                searchBook(root,id);
                break;
            case 4:
                viewAllBooks(root);
                break;
            case 5: {
                int mode = getValidSortMode();
                sortAndDisplay(books, mode);
                break;
            }
            case 6: {
                int mode = getValidSearchMode();
                string query;
                cin.ignore();
                cout << "Enter search text: ";
                getline(cin, query);
                searchByTitleAuthor(books, query, mode);
                break;
            }
            case 7:
                savetoLibrary(books, filename);
                cout << "Data saved.\n";
                break;
            case 8:
                savetoLibrary(books, filename);
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != 8);
    return 0;
}
