#ifndef BOOKDATABASE_H
#define BOOKDATABASE_H

#include "book.h"

#include <string>
#include <vector>

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

class BookDatabase {
public:
    BookDatabase();
    void addBook(const Book &book);
    void removeBook(const std::string &isbn);
    std::vector<Book> getAllBooks() const;
    Book* searchBook(const std::string &title);
    Book* searchBookByISBN(const std::string& isbn);
    void updateBook(const Book& updatedBook);

private:
    std::vector<Book> books;
    void loadBooksFromFile(const std::string &filename);
    void saveBooksToFile(const std::string &filename) const;
};

#endif // BOOKDATABASE_H
