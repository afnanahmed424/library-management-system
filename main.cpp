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
int totalBooks = 0;

void saveBooks() {
    ofstream file("books.txt");
    for (int i = 0; i < totalBooks; i++) {
        file << books[i].id << endl;
        file << books[i].title << endl;
        file << books[i].author << endl;
        file << books[i].issued << endl;
    }
    file.close();
}

void loadBooks() {
    ifstream file("books.txt");
    if (!file) return;
    while (file >> books[totalBooks].id) {
        file.ignore();
        getline(file, books[totalBooks].title);
        getline(file, books[totalBooks].author);
        file >> books[totalBooks].issued;
        totalBooks++;
    }
    file.close();
}

int findBook(int id) {
    for (int i = 0; i < totalBooks; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

void addBook() {
    if (totalBooks >= 100) {
        cout << "Library is full." << endl;
        return;
    }
    Book b;
    cout << "Enter book ID: ";
    cin >> b.id;
    if (findBook(b.id) != -1) {
        cout << "This ID already exists." << endl;
        return;
    }
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, b.title);
    cout << "Enter author: ";
    getline(cin, b.author);
    b.issued = false;
    books[totalBooks] = b;
    totalBooks++;
    saveBooks();
    cout << "Book added." << endl;
}

void showBooks() {
    if (totalBooks == 0) {
        cout << "No books yet." << endl;
        return;
    }
    cout << "\n--- All Books ---" << endl;
    for (int i = 0; i < totalBooks; i++) {
        cout << books[i].id << " | " << books[i].title << " by " << books[i].author;
        if (books[i].issued) cout << " | ISSUED" << endl;
        else cout << " | Available" << endl;
    }
}

void searchBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;
    int i = findBook(id);
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
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found." << endl;
    } else if (books[i].issued) {
        cout << "This book is already issued." << endl;
    } else {
        books[i].issued = true;
        saveBooks();
        cout << "Book issued." << endl;
    }
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found." << endl;
    } else if (!books[i].issued) {
        cout << "This book was not issued." << endl;
    } else {
        books[i].issued = false;
        saveBooks();
        cout << "Book returned." << endl;
    }
}

void deleteBook() {
    int id;
    cout << "Enter book ID to delete: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found." << endl;
        return;
    }
    for (int j = i; j < totalBooks - 1; j++) {
        books[j] = books[j + 1];
    }
    totalBooks--;
    saveBooks();
    cout << "Book deleted." << endl;
}

int main() {
    loadBooks();
    int choice;
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
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: showBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
