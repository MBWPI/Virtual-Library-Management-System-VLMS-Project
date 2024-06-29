#include "bookDatabase.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

BookDatabase::BookDatabase() {
    loadBooksFromFile("database/book_database.txt");
}

void BookDatabase::addBook(const Book &book) {
    books.push_back(book);
    saveBooksToFile("database/book_database.txt");
}

void BookDatabase::removeBook(const std::string &isbn) {
    auto it = std::remove_if(books.begin(), books.end(),
                             [&](const Book &b) { return b.getISBN() == isbn; });
    if (it != books.end()) {
        books.erase(it, books.end());
        saveBooksToFile("database/book_database.txt");
    }
}

void BookDatabase::updateBook(const Book& updatedBook) {
    for (auto& book : books) {
        if (book.getISBN() == updatedBook.getISBN()) {
            book = updatedBook;
            saveBooksToFile("database/book_database.txt");
            return;
        }
    }
}

Book* BookDatabase::searchBook(const std::string &title) {
    for (auto &book : books) {
        if (book.getTitle() == title) {
            return &book;
        }
    }
    return nullptr;
}

Book* BookDatabase::searchBookByISBN(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

std::vector<Book> BookDatabase::getAllBooks() const {
    return books;
}

void BookDatabase::loadBooksFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    books.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, author, isbn, yearStr, quantityStr;
        int year, quantity;

        // Read title
        if (!std::getline(ss, title, ',')) {
            std::cerr << "Failed to read title" << std::endl;
            continue;
        }

        // Read author
        if (!std::getline(ss, author, ',')) {
            std::cerr << "Failed to read author" << std::endl;
            continue;
        }

        // Read ISBN
        if (!std::getline(ss, isbn, ',')) {
            std::cerr << "Failed to read ISBN" << std::endl;
            continue;
        }

        // Read year
        if (!std::getline(ss, yearStr, ',')) {
            std::cerr << "Failed to read year" << std::endl;
            continue;
        }

        // Read quantity
        if (!std::getline(ss, quantityStr)) {
            std::cerr << "Failed to read quantity" << std::endl;
            continue;
        }

        try {
            year = std::stoi(yearStr);
            quantity = std::stoi(quantityStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << " in line: " << line << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << " in line: " << line << std::endl;
            continue;
        }

        books.emplace_back(title, author, isbn, year, quantity);
    }
    file.close();
}

void BookDatabase::saveBooksToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto &book : books) {
        file << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getISBN() << ","
             << book.getYear() << ","
             << book.getQuantity() << "\n";
    }
    file.close();
}
