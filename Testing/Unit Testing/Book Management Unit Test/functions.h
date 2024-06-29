#include <string>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H



void searchBooks();
void borrowBook();
void returnBook();
void viewBorrowedBooks();
void updateProfile();
void addBook(std::string book_title, std::string book_type,std::string book_subject,std::string book_desc,std::string book_genre,std::string book_author,std::string book_page_count,std::string book_release_year);
void removeBook();
void updateBookInfo();
void viewAllLoans();
void manageUsers();

#endif // LIBRARYOPERATIONS_H