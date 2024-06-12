#include "libraryOperations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void trim(std::string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        str = "";
    } else {
        str = str.substr(first, (last - first + 1));
    }
}

// Struct to hold book information
struct Book {
    int id;
    std::string title;
    std::string author;
    int pages;
    std::string subject;
    std::string genre;
    int release_year;
    std::string type;
    std::string desc;
    bool rented;
    std::string renter;

    // For sorting and comparison
    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

// Function to parse a line from the file into a Book struct
Book parseBookLine(const std::string& line) {
    std::stringstream ss(line);
    Book book;
    std::string temp;

    std::getline(ss, temp, '-'); // Ignore the initial -
    ss >> book.id;
    std::getline(ss, temp, '-'); // Ignore the -
    std::getline(ss, book.title, '-');
    std::getline(ss, book.author, '-');
    ss >> book.pages;
    std::getline(ss, temp, '-'); // Ignore the -
    std::getline(ss, book.subject, '-');
    std::getline(ss, book.genre, '-');
    ss >> book.release_year;
    std::getline(ss, temp, '-'); // Ignore the -
    std::getline(ss, book.type, '-');
    std::getline(ss, book.desc, '-');
    std::getline(ss, temp, '-'); // Ignore the -
    std::string rented;
    ss >> rented;
    book.rented = (rented == "rented");
    std::getline(ss, temp, '-'); // Ignore the -
    std::getline(ss, book.renter, '-');

    // Trim whitespace from each field
    auto trim = [](std::string &str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos) {
            str = "";
        } else {
            str = str.substr(first, (last - first + 1));
        }
    };

    trim(book.title);
    trim(book.author);
    trim(book.subject);
    trim(book.genre);
    trim(book.type);
    trim(book.desc);
    trim(book.renter);

    return book;
}

// Function to perform binary search on a vector of books
int Search(const std::vector<Book>& books, const std::string& title) {
    int left = 0, right = books.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // Trim whitespace before comparison
        std::string trimmedSearchTitle = title;
        trim(trimmedSearchTitle); 
        std::string trimmedBookTitle = books[mid].title; 
        trim(trimmedBookTitle);

        if (trimmedBookTitle == trimmedSearchTitle) {
            return mid;
        } else if (trimmedBookTitle < trimmedSearchTitle) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Book not found
}

std::string readLastLine(const std::string filename) {
    std::ifstream file(filename);
    std::string lastLine, line;

    while (std::getline(file, line)) {
        lastLine = line;
    }
    return lastLine;
}

std::vector<Book> searchBooks(std::string filename, std::string bookTitle) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return {}; // Return an empty vector if file opening fails
    }

    std::vector<Book> books;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            books.push_back(parseBookLine(line));
        }
    }

    file.close();

    // Sort the books by title for binary search
    std::sort(books.begin(), books.end());

    std::string searchTitle = bookTitle;
    // Trim the searchTitle to remove leading/trailing whitespace
    auto trim = [](std::string &str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos) {
            str = "";
        } else {
            str = str.substr(first, (last - first + 1));
        }
    };

    trim(searchTitle);

    // Add a space to the beginning and end of the searchTitle
    searchTitle = " " + searchTitle + " ";

    std::vector<Book> foundBooks;

    int index = Search(books, searchTitle);

    if (index != -1) {
        // Correctly handle reading the previous line
        if (index > 0) {
            index--;
        }
        const Book& foundBook = books[index];
        foundBooks.push_back(foundBook);
    }

    return foundBooks;
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

    std::fstream book_database("database/book_database.txt");
    int book_id, rented = 0;
    char renter = ' ';

    int counter = 0;
    if (book_database.is_open()) { //checks last line and grabs data of the last book added
        
        std::string last_line = readLastLine("database/book_database.txt"); //grabs last line and stores it in to var
        std::getline(book_database, last_line);
        std::vector<std::string> last_book_entered;
        std::stringstream ss(readLastLine("database/book_database.txt"));
        std::string token;


        while(getline(ss, token, '-')) {  //stores each line minus the '-' into an array
            token.erase(0, token.find_first_not_of(" ")); // Trim leading spaces
            token.erase(token.find_last_not_of(" ") + 1); // Trim trailing spaces
            last_book_entered.push_back(token);    
            counter++;            
        }

        book_id = stoi(last_book_entered[1]); // adds 1 to book id
        book_id++;
        std::string lbreak = " - ";
        book_database.close();
        std::fstream book_database;
        book_database.open("database/book_database.txt", std::ios::app);
       book_database << "\n- " << book_id << lbreak  << book_title << lbreak << book_author << lbreak << book_page_count << lbreak << book_subject << lbreak << book_genre << lbreak << book_release_year << lbreak << book_type << lbreak << book_desc << lbreak << rented << lbreak << "renter";  
        book_database.close();
        std::cout << "\nAdding a book...\n";
        std::cout << "Book ID: " <<  book_id << std::endl << "Book Title: " << last_book_entered[1] << std::endl << "Book Author: " << book_author << std::endl << "Page Count: " << book_page_count << std::endl << "Subject: " << book_subject << std::endl << "Genre: " << book_genre << std::endl << "Release Year: " << book_release_year << std::endl << "Format: " << book_type << "Book Desc:" << book_desc << std::endl;    
    }else {
        std::cout << "error";
    }


}

void removeBook(std::string filename, std::string bookTitle) {
    std::cout << "\nRemoving a book...\n";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string tempFilename = "database/temp_file/temp.txt";
    std::ofstream tempFile(tempFilename);

    if(!tempFile.is_open()) {
        std::cerr << "Failed to open temp file." << std::endl;
        return;
    }

    std::string line;
    std::string searchTitle = " " + bookTitle + " ";
    bool bookFound = false;

    while(std::getline(inputFile, line)) {
        if(line.find(searchTitle) != std::string::npos) {
            bookFound = true;
            continue;
        }
        // Check if this line is not empty
        if (!line.empty()) {
            // Write the line to the temporary file
            tempFile << line << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if(bookFound) {
        if(std::remove(filename.c_str()) != 0) {
            std::cerr << "Error deleting the original file." << std::endl;
            return;
        }
        if(std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
            std::cerr << "Error renaming the temporary file." << std::endl;
        }
        std::cout << "Book Deleted successfully." << std::endl;
    }else {
        std::cout << "Book not found" << std::endl;
        std::remove(tempFilename.c_str());
    }
}

void updateBookInfo(std::string filename, Book updatedBook) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::vector<Book> books;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            books.push_back(parseBookLine(line));
        }
    }

    file.close();

    // Find and update the book
    bool bookFound = false;
    for (auto& book : books) {
        if (book.id == updatedBook.id) {
            book = updatedBook;
            bookFound = true;
            break;
        }
    }

    if (!bookFound) {
        std::cerr << "Book with ID " << updatedBook.id << " not found." << std::endl;
        return;
    }

    // Write the updated books back to the file, ignoring blank lines
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const auto& book : books) {
        outFile << "- " << book.id << " - " << book.title << " - " << book.author << " - " << book.pages << " - "<< book.subject << " - " << book.genre << " - " << book.release_year << " - " << book.type << " - "<< book.desc << " - " << (book.rented ? "rented" : "not rented") << " - " << book.renter << " - " << std::endl;
    }

    outFile.close();
}

void updateBook(std::string filename, std::string BookToUpdate) {
    std::cout << "\nUpdating book information...\n";

    std::vector result = searchBooks(filename, BookToUpdate);
    Book& Found_Book = result[0];
    
    // Check if any books were found
    if (!result.empty()) {
        std::cout << "Books to Update:" << std::endl;
        for (const auto& book : result) {
            // Access and use the data of each found book
            std::cout << "Title: " << book.title << std::endl;
            std::cout << "Author: " << book.author << std::endl;
            std::cout << "Pages: " << book.pages << std::endl;
            std::cout << "Subject: " << book.subject << std::endl;
            std::cout << "Genre: " << book.genre << std::endl;
            std::cout <<"Release Year: " << book.release_year << std::endl;
            std::cout << "Type: " << book.type << std::endl;
            std::cout << "Desc: " << book.desc << std::endl;
        }
    }

    // no idea how to convert the array to be able to use result[1], result[2].... I cant remeber how I event set it up 
    std::string y_n = " ";
    std::cout << "Would you like to update title:  " << Found_Book.title << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.title = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
    }

    std::cout << "Would you like to update author: " << Found_Book.author << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.author = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }

    y_n = " ";
    int int_update;
    std::cout << "Would you like to update pages: " << Found_Book.pages << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::cout << "Update to: ";
        std::cin >> int_update;
        Found_Book.pages = int_update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }

    y_n = " ";
    std::cout << "Would you like to update subject: " << Found_Book.subject << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.subject = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    } 

    y_n = " ";
    std::cout << "Would you like to update genre: " << Found_Book.genre << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.genre = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }   

    y_n = " ";
    std::cout << "Would you like to update release year: " << Found_Book.release_year << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.release_year = int_update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }  
    
    y_n = " ";
    std::cout << "Would you like to update book type: " << Found_Book.type << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.type = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    } 

    y_n = " ";
    std::cout << "Would you like to update desc: " << Found_Book.desc << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        Found_Book.desc = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    } 

    updateBookInfo(filename, Found_Book);

    std::cout << "Book Information Update Successfully!\n";
}

void viewAllLoans() {
    std::cout << "\nViewing all loans...\n";
}

void manageUsers() {
    std::cout << "\nManaging users...\n";
}
