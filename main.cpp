//test all functions

#include "functions.h"
#include "functions.cpp"
#include <iostream>
#include <vector>


int main() {
    std::string book_title = "9",  book_type = "10", book_subject = "11", book_desc = "12", book_genre = "13", book_author = "14", book_page_count = "15", book_release_year = "16";
    addBook(book_title,  book_type, book_subject, book_desc, book_genre, book_author, book_page_count, book_release_year);

    signUp("Testing1", "testing@1", "Testing Name", "00/00/0000");

    std::vector<std::string> admins = { "testingifdumb", "esting2", "Testing1"};

    bool isTrue = isAdminTxt("database/admin_users.txt", "esting2");
    bool isTrue2 = isAdminVector("Testing1", admins);

    std::cout << "Is in txt: " << isTrue << std::endl;
    std::cout << "Is in Array: " << isTrue2 << std::endl;

    checkIfBookRented("database/book_database.txt", "1984");

    borrowBook("database/book_database.txt", "esting2");
    

    viewAllLoans("database/book_database.txt", "esting2", "Text", "database/admin_users.txt");
    viewAllLoans("database/book_database.txt", "esting2", "Vector", "");

    viewBorrowedBooks("database/book_database.txt", "esting2");

    viewAllLoan("database/book_database.txt");

    returnBook("database/book_database.txt", "esting2");
    return 0;
}