#include "libraryOperations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::string readLastLine(const std::string filename) { // this grabs the last line of the database allowing me to generate the id, this can be manipulated to use in other functions, just keep this the same copy/paste if needed
    std::ifstream file(filename); // opens file
    std::string lastLine, line; 

    while (std::getline(file, line)) {
        lastLine = line;
    }
    return lastLine;
}

void searchBooks() {
    std::cout << "\nSearching for books...\n";
    
}

void borrowBook(UserManagement && userManager, BookDatabase && findBookByTitle){
    std::cout << "\nBorrowing a book...\n";
    // Load the book database
    BookDatabase bookDb;
    // Get the username from the user
    std::string username;
    std::cout << "\nEnter your username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
    // Find the user in the user management system
    User* user = userManager.findUser(username);
    if (!user) {
        std::cout << "User not found.\n";
        return;}
    else{
        std::cout << "User found.\n";
        }
    // Get the book title from the user
    std::string Title;
    std::cout << "\nEnter the title of the book to borrow: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, Title);
    // Find the book in the book database
    Book* book = bookDb.findBookByTitle(Title);
        if (!book) {
            std::cout << "Book not found.\n";
            return;
        } else {
            std::cout << "Book found.\n";
            std::cout << "Title: " << book->getTitle() << "\n";
            std::cout << "Would you like to borrow this book? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                if (bookDb.borrowBook(book->getTitle(), username)) {
                    std::cout << "Book borrowed successfully.\n";
                } else {
                    std::cout << "Failed to borrow the book.\n";
                }
            } else if (choice == 'n' || choice == 'N') {
                std::cout << "Book not borrowed.\n";
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
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

    std::fstream book_database("database/book_database.txt"); // opens database
    int book_id, rented = 0; // book_id is generated based of what was the last id + 1, default rented status 0
    char renter = ' '; // default renter null

    int counter = 0;
    if (book_database.is_open()) { //checks last line and grabs data of the last book added
        
        std::string last_line = readLastLine("database/book_database.txt"); //grabs last line and stores it in to var
        std::getline(book_database, last_line); // grabs line of databse
        std::vector<std::string> last_book_entered; // creates a vector for that line
        std::stringstream ss(readLastLine("database/book_database.txt")); // puts the line into the vector
        std::string token;


        while(getline(ss, token, '-')) {  //stores each line minus the '-' into an array
            token.erase(0, token.find_first_not_of(" ")); // Trim leading spaces
            token.erase(token.find_last_not_of(" ") + 1); // Trim trailing spaces
            last_book_entered.push_back(token);    
            counter++;            
        }

        book_id = stoi(last_book_entered[9]); // adds 1 to book id
        book_id++; // makes id
        std::string lbreak = " - "; //This is the identifier for the separation of data in the database
        book_database.close(); // for some reason, it only works if I close the database and reopen it in app status 
        std::fstream book_database;
        book_database.open("database/book_database.txt", std::ios::app);
        book_database << std::endl << "- " << book_title << lbreak << book_author << lbreak << book_page_count << lbreak << book_subject << lbreak << book_genre << lbreak << book_release_year << lbreak << book_type << lbreak <<  book_desc << lbreak << book_id << lbreak << rented << lbreak << renter;  
        book_database.close(); // gota close it again
        std::cout << "\nAdding a book...\n"; // shows user the book they added
        std::cout << "Book ID: " <<  book_id << std::endl << "Book Title: " << last_book_entered[1] << std::endl << "Book Author: " << book_author << std::endl << "Page Count: " << book_page_count << std::endl << "Subject: " << book_subject << std::endl << "Genre: " << book_genre << std::endl << "Release Year: " << book_release_year << std::endl << "Format: " << book_type << "Book Desc:" << book_desc << std::endl;    
    }else {
        std::cout << "error"; // if failed to open the database file
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
