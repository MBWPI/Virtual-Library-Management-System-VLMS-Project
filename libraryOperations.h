#ifndef LIBRARYOPERATIONS_H
#define LIBRARYOPERATIONS_H

#pragma once

#include "book.h"
#include "queue.h"

#include <queue>
#include <string>

void viewBorrowedBooks(const std::string &username);
void removeBook();
void viewAllLoans(const std::string &username);
void updateBookInfo();

// Data Persistence
void saveBooksToFile(const std::string &filename);
void loadBooksFromFile(const std::string &filename);

class LibraryOperations {
public:
    Book* getNextBorrowedBook();
    void saveBooksToFile(const std::string &filename);
    void loadBooksFromFile(const std::string &filename);
    static void borrowBook(const std::string &username);
    static void returnBook(const std::string &username);
    static void searchBooks();
    static void addBook();
    static void updateBookInfo();

    Queue transactions;

private:
    std::queue<Book> borrowedBooks;
};

bool isLastTransactionBorrowedByUser(const std::string &bookTitle, const std::string &username);

#endif // LIBRARYOPERATIONS_H
