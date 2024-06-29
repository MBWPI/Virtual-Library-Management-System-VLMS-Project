#include "book.h"

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int year, int quantity)
    : title(title), author(author), isbn(isbn), year(year), quantity(quantity) {}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getISBN() const { return isbn; }
int Book::getYear() const { return year; }
int Book::getQuantity() const { return quantity; }
void Book::setTitle(const std::string& title) { this->title = title; }
void Book::setAuthor(const std::string& author) { this->author = author; }
void Book::setYear(int year) { this->year = year; }
void Book::setQuantity(int quantity) { this->quantity = quantity; }
