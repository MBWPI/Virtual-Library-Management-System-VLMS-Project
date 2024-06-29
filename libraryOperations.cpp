#include "bookDatabase.h"
#include "bst.h"
#include "libraryOperations.h"
#include "queue.h"
#include "userManagement.h"
#include "utility.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

// A global LibraryOperations instance to use transactions
LibraryOperations libraryOps;

void logTransaction(const std::string &transaction) {
    std::ofstream file("database/transactions.txt", std::ios::app);
    if (file.is_open()) {
        file << transaction << "\n";
        file.close();
    } else {
        std::cerr << "Failed to open transaction log file.\n";
    }
}

bool isTransactionExists(const std::string& transaction) {
    std::ifstream file("database/transactions.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == transaction) {
            return true;
        }
    }
    return false;
}

bool isBookAvailable(const std::string& bookTitle, int& availableQuantity) {
    std::ifstream file("database/book_database.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, author, isbn, year, quantityStr;
        int quantity;
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, year, ',');
        std::getline(ss, quantityStr);
        if (title == bookTitle) {
            quantity = std::stoi(quantityStr);
            if (quantity > 0) {
                availableQuantity = quantity;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void LibraryOperations::searchBooks() {
    std::cout << "\nSearching for books...\n";

    // Load the book database
    BookDatabase bookDb;

    // Insert books into a Binary Search Tree for efficient searching
    BST bookTree;
    for (const auto& book : bookDb.getAllBooks()) {
        bookTree.insert(book);
    }

    // Get the search term from the user
    std::string searchTitle;
    std::cout << "\nEnter the title of the book to search: ";
    std::cin.ignore(); // Ignore any remaining newline character in the input buffer
    std::getline(std::cin, searchTitle);

    // Perform a search in the BST
    std::vector<Book> foundBooks = bookTree.search(searchTitle);

    if (foundBooks.empty()) {
        std::cout << "\nNo books found matching the query.\n";
    } else {
        std::cout << "\nBooks found:\n";
        for (const auto& book : foundBooks) {
            std::cout << "Title: " << book.getTitle() << "\n";
            std::cout << "Author: " << book.getAuthor() << "\n";
            std::cout << "ISBN: " << book.getISBN() << "\n";
            std::cout << "Year: " << book.getYear() << "\n";
            std::cout << "Quantity: " << book.getQuantity() << "\n\n";
        }
    }
}

void LibraryOperations::borrowBook(const std::string &username) {
    std::cout << "\nBorrowing a book...\n";
    std::string bookTitle;
    std::cout << "\nEnter the title of the book to borrow: ";
    std::cin.ignore();
    std::getline(std::cin, bookTitle);

    int availableQuantity;
    if (isBookAvailable(bookTitle, availableQuantity)) {
        std::string transaction = "Borrowed: " + bookTitle + " by " + username;
        std::ofstream file("database/transactions.txt", std::ios::app);
        file << transaction << std::endl;
        BookDatabase bookDb;
        Book* book = bookDb.searchBook(bookTitle);
        if (book) {
            book->setQuantity(book->getQuantity() - 1);
            bookDb.updateBook(*book);
            std::cout << "\nYou have successfully borrowed the book." << std::endl;
        }
    } else {
        std::cout << "\nBook is not available!" << std::endl;
    }
}

bool isLastTransactionBorrowedByUser(const std::string &bookTitle, const std::string &username) {
    std::ifstream file("database/transactions.txt");
    std::string line;
    std::string lastTransaction;

    while (std::getline(file, line)) {
        if (line.find("Borrowed: " + bookTitle) != std::string::npos || line.find("Returned: " + bookTitle) != std::string::npos) {
            lastTransaction = line;
        }
    }

    std::string borrowTransaction = "Borrowed: " + bookTitle + " by " + username;
    return lastTransaction == borrowTransaction;
}

void LibraryOperations::returnBook(const std::string &username) {
    std::cout << "\nReturning a book...\n";
    std::string bookTitle;
    std::cout << "\nEnter the title of the book to return: ";
    std::cin.ignore();
    std::getline(std::cin, bookTitle);

    if (isLastTransactionBorrowedByUser(bookTitle, username)) {
        std::string returnTransaction = "Returned: " + bookTitle + " by " + username;
        std::ofstream file("database/transactions.txt", std::ios::app);
        file << returnTransaction << std::endl;
        BookDatabase bookDb;
        Book* book = bookDb.searchBook(bookTitle);
        if (book) {
            book->setQuantity(book->getQuantity() + 1);
            bookDb.updateBook(*book);
            std::cout << "\nBook returned successfully.\n";
        }
    } else {
        std::cout << "\nYou cannot return this book because you\n haven't borrowed it or you have already returned it.\n";
    }
}

void viewBorrowedBooks(const std::string &username) {
    std::cout << "\nViewing " << username << " borrowed books\n";
    std::ifstream file("database/transactions.txt");
    std::string line;
    std::unordered_set<std::string> borrowedBooks;

    while (std::getline(file, line)) {
        if (line.find("Borrowed:") != std::string::npos && line.find(" by " + username) != std::string::npos) {
            std::string bookTitle = line.substr(9, line.find(" by ") - 9);
            borrowedBooks.insert(bookTitle);
        }
        if (line.find("Returned:") != std::string::npos && line.find(" by " + username) != std::string::npos) {
            std::string bookTitle = line.substr(9, line.find(" by ") - 9);
            borrowedBooks.erase(bookTitle);
        }
    }

    if (borrowedBooks.empty()) {
        std::cout << "\nNo books borrowed currently.\n";
    } else {
        std::cout << "\nCurrently borrowed books:\n";
        for (const auto &title : borrowedBooks) {
            std::cout << "Title: " << title << "\n";
        }
    }
}

void addBook() {
    std::cout << "\nAdding a book...\n";
    std::string title, author, isbn, yearStr, quantityStr;
    int year, quantity;

    std::cout << "Enter book title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    std::cout << "Enter ISBN (13 characters): ";
    while (true) {
        std::cin >> isbn;
        if (isbn.length() == 13 && std::all_of(isbn.begin(), isbn.end(), ::isdigit)) {
            break;
        } else {
            std::cout << "\nISBN must be 13 digits long. Try again: ";
            clearInput();
        }
    }
    std::cout << "Enter year (4 digits): ";
    while (true) {
        std::cin >> yearStr;
        if (yearStr.length() == 4 && std::all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
            year = std::stoi(yearStr);
            break;
        } else {
            std::cout << "\nYear must be 4 digits long. Try again: ";
            clearInput();
        }
    }
    std::cout << "Enter quantity: ";
    while (true) {
        std::cin >> quantityStr;
        if (!quantityStr.empty() && std::all_of(quantityStr.begin(), quantityStr.end(), ::isdigit)) {
            quantity = std::stoi(quantityStr);
            break;
        } else {
            std::cout << "\nQuantity must be a positive integer. Try again: ";
            clearInput();
        }
    }

    Book book(title, author, isbn, year, quantity);
    BookDatabase bookDb;
    bookDb.addBook(book);
    std::cout << "\nBook added successfully.\n";
}

void removeBook() {
    std::cout << "\nRemoving a book...\n";
    std::string isbn;
    std::cout << "\nEnter the ISBN of the book to remove: ";
    std::cin.ignore(); // Clear any leftover newline character in the input buffer
    std::getline(std::cin, isbn);

    BookDatabase bookDb;
    bookDb.removeBook(isbn);
    std::cout << "\nBook removed successfully.\n";
}


void updateBookInfo() {
    std::cout << "\nUpdating book information...\n";
    std::string isbn, title, author, yearStr, quantityStr;
    int year, quantity;

    std::cout << "\nEnter ISBN (13 characters): ";
    while (true) {
        std::cin >> isbn;
        std::cin.ignore(); // Clear the newline character left in the input buffer
        if (isbn.length() == 13 && std::all_of(isbn.begin(), isbn.end(), ::isdigit)) {
            break;
        } else {
            std::cout << "ISBN must be 13 digits long. Try again: ";
            clearInput();
        }
    }

    BookDatabase bookDb;
    Book* book = bookDb.searchBookByISBN(isbn);
    if (book) {
        std::cout << "Enter the new title of the book: ";
        std::getline(std::cin, title);
        std::cout << "Enter the new author of the book: ";
        std::getline(std::cin, author);
        std::cout << "Enter year (4 digits): ";
        while (true) {
            std::getline(std::cin, yearStr); // Use std::getline to get the input as a string
            if (yearStr.length() == 4 && std::all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
                try {
                    year = std::stoi(yearStr);
                    break;
                } catch (const std::invalid_argument&) {
                    std::cout << "\nInvalid input. Year must be a 4-digit number. Try again: ";
                } catch (const std::out_of_range&) {
                    std::cout << "\nYear is out of range. Try again: ";
                }
            } else {
                std::cout << "\nYear must be 4 digits long. Try again: ";
            }
        }
        std::cout << "Enter quantity: ";
        while (true) {
            std::getline(std::cin, quantityStr); // Use std::getline to get the input as a string
            if (!quantityStr.empty() && std::all_of(quantityStr.begin(), quantityStr.end(), ::isdigit)) {
                try {
                    quantity = std::stoi(quantityStr);
                    break;
                } catch (const std::invalid_argument&) {
                    std::cout << "\nInvalid input. Quantity must be a positive integer. Try again: ";
                } catch (const std::out_of_range&) {
                    std::cout << "\nQuantity is out of range. Try again: ";
                }
            } else {
                std::cout << "\nQuantity must be a positive integer. Try again: ";
            }
        }

        book->setTitle(title);
        book->setAuthor(author);
        book->setYear(year);
        book->setQuantity(quantity);
        bookDb.updateBook(*book);
        std::cout << "\nBook information updated successfully.\n";
    } else {
        std::cout << "\nBook not found.\n";
    }
}

void viewAllLoans(const std::string &username) {
std::cout << "\nViewing all loans...\n";
    std::cout << "\nAll transactions:\n";
    std::ifstream file("database/transactions.txt");
    std::string line;
    bool hasTransactions = false;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        hasTransactions = true;
    }

    if (!hasTransactions) {
        std::cout << "\nNo transactions" << std::endl;
    }
}

Book* LibraryOperations::getNextBorrowedBook() {
    return borrowedBooks.empty() ? nullptr : &borrowedBooks.front();
}

// Data Persistence in Book Management
void LibraryOperations::saveBooksToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    // Serialize book data
    file.close();
}

void LibraryOperations::loadBooksFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }
    // Deserialize book data
    file.close();
}
