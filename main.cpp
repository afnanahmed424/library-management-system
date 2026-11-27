// Library Management System
// Programming Fundamentals - Semester Project (Fall 2023)

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
};

Book books[100];
int n = 0;

void saveData() {
    ofstream f("books.txt");
    for (int i = 0; i < n; i++) {
        f << books[i].id << endl;
        f << books[i].title << endl;
        f << books[i].author << endl;
        f << books[i].issued << endl;
    }
    f.close();
}

void loadData() {
    ifstream f("books.txt");
    if (!f) return;
    while (f >> books[n].id) {
        f.ignore();
        getline(f, books[n].title);
        getline(f, books[n].author);
        f >> books[n].issued;
        n++;
    }
    f.close();
}

int search(int id) {
    for (int i = 0; i < n; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

void addBook() {
    if (n >= 100) {
        cout << "Library is full." << endl;
        return;
    }
    cout << "Enter book ID: ";
    cin >> books[n].id;
    if (search(books[n].id) != -1) {
        cout << "This ID already exists." << endl;
        return;
    }
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, books[n].title);
    cout << "Enter author: ";
    getline(cin, books[n].author);
    books[n].issued = false;
    n++;
    saveData();
    cout << "Book added." << endl;
}

void showBooks() {
    if (n == 0) {
        cout << "No books yet." << endl;
        return;
    }
    cout << "\n--- All Books ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << books[i].id << " | " << books[i].title << " by " << books[i].author;
        if (books[i].issued) cout << " | ISSUED" << endl;
        else cout << " | Available" << endl;
    }
}

void searchBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;
    int i = search(id);
    if (i == -1) {
        cout << "Book not found." << endl;
    } else {
        cout << books[i].id << " | " << books[i].title << " by " << books[i].author;
        if (books[i].issued) cout << " | ISSUED" << endl;
        else cout << " | Available" << endl;
    }
}

void issueBook() {
    int id;
    cout << "Enter book ID to issue: ";
    cin >> id;
    int i = search(id);
    if (i == -1) {
        cout << "Book not found." << endl;
    } else if (books[i].issued) {
        cout << "This book is already issued." << endl;
    } else {
        books[i].issued = true;
        saveData();
        cout << "Book issued." << endl;
    }
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;
    int i = search(id);
    if (i == -1) {
        cout << "Book not found." << endl;
    } else if (!books[i].issued) {
        cout << "This book was not issued." << endl;
    } else {
        books[i].issued = false;
        saveData();
        cout << "Book returned." << endl;
    }
}

void deleteBook() {
    int id;
    cout << "Enter book ID to delete: ";
    cin >> id;
    int i = search(id);
    if (i == -1) {
        cout << "Book not found." << endl;
        return;
    }
    for (int j = i; j < n - 1; j++) {
        books[j] = books[j + 1];
    }
    n--;
    saveData();
    cout << "Book deleted." << endl;
}

int main() {
    loadData();
    int ch;
    do {
        cout << "\n===== Library Management System =====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Show All Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Issue Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Delete Book" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(1000, '\n');
            ch = -1;
        }

        switch (ch) {
            case 1: addBook(); break;
            case 2: showBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (ch != 0);

    return 0;
}
