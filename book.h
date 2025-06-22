#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int year;

    Book() : id(0), year(0) {}
    Book(int id, const string& title, const string& author, int year)
        : id(id), title(title), author(author), year(year) {}

    void print() const {
        cout << "ID-" << id << ": Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
    bool operator<(const Book& other) const {
        return id < other.id;
    }
};
