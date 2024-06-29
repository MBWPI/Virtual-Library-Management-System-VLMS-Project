#ifndef BOOK_H
#define BOOK_H

#pragma once
#include <string>

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

class Book {
public:
    Book(const std::string &title, const std::string &author, const std::string &isbn, int year, int quantity = 1);
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    int getYear() const;
    int getQuantity() const;
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setQuantity(int quantity);

private:
    std::string title;
    std::string author;
    std::string isbn;
    int year;
    int quantity;
};

#endif // BOOK_H
