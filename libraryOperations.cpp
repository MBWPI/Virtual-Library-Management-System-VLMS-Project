#include "libraryOperations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void searchBooks() {
    std::cout << "\nSearching for books...\n";
    
}

void borrowBook() {
    std::cout << "\nBorrowing a book...\n";
}

void returnBook() {
    std::cout << "\nReturning a book...\n";
}

void viewBorrowedBooks() {
    std::cout << "\nViewing borrowed books...\n";
}

void updateProfile() {
    std::cout << "\nUpdating profile...\n";
}

void addBook(std::string book_title, std::string book_type,std::string book_subject,std::string book_desc,std::string book_genre,std::string book_author,std::string book_page_count,std::string book_release_year) {

    std::ifstream book_database;
    book_database.open("database/book_database.txt");
    int book_id;
    
    int counter = 0;
    if (book_database.is_open()) { //checks last line and grabs data of the last book added

        book_database.seekg(-1,std::ios_base::end);
        bool check_line = true;
        while (check_line) {
            char ch;
            book_database.get(ch);

            if ((int)book_database.tellg() <= 1) {
                book_database.seekg(0);
                check_line = false;
            } else if (ch == '\n') {
                check_line = true;
            } else {
                book_database.seekg(-2, std::ios_base::cur);
            }
        }
        std::string last_line; //grabs last line and stores it in to var
        std::getline(book_database, last_line);
        std::vector<std::string> last_book_entered;
        std::stringstream ss(last_line);
        std::string token;


        while(getline(ss, token, '-')) {  //stores each line minus the '-' into an array
            token.erase(0, token.find_first_not_of(" ")); // Trim leading spaces
            token.erase(token.find_last_not_of(" ") + 1); // Trim trailing spaces
            last_book_entered.push_back(token);    
            counter++;            
        }

        book_id = stoi(last_book_entered[9]); // adds 1 to book id
        book_id++;
        std::string lbreak = " - ";



        book_database.close();
        std::fstream book_database;
        book_database.open("database/book_database.txt", std::ios::app);
        book_database << std::endl << lbreak << book_title << lbreak << book_author << lbreak << book_page_count << lbreak << book_subject << lbreak << book_genre << lbreak << book_release_year << lbreak << book_type << lbreak <<  book_desc << std::endl << lbreak << book_id;  
        book_database.close();
        std::cout << "\nAdding a book...\n";
        std::cout << "Book ID: " <<  book_id << std::endl << "Book Title: " << book_title << std::endl << "Book Author: " << book_author << std::endl << "Page Count: " << book_page_count << std::endl << "Subject: " << book_subject << std::endl << "Genre: " << book_genre << std::endl << "Release Year: " << book_release_year << std::endl << "Format: " << book_type << "Book Desc:" << book_desc << std::endl;    
    }


}

void removeBook() {
    std::cout << "\nRemoving a book...\n";
}

void updateBookInfo() {
    std::cout << "\nUpdating book information...\n";
}

void viewAllLoans() {
    std::cout << "\nViewing all loans...\n";
}

void manageUsers() {
    std::cout << "\nManaging users...\n";
}
