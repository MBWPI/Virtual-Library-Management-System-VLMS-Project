#include "functions.h"
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

    // no idea how to convert the array to be able to use result[1], result[2]
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

void borrowBook(std::string filename, std::string loggedInUser) {    
    std::string confirmBorrow;
    bool confirmBorrow_bool;
    std::string bookTitle;
    std::cout << "Enter a book: ";
    std::cin >> bookTitle;
    
    std::vector result = searchBooks(filename, bookTitle);
    Book& Found_Book = result[0];
    
    if (Found_Book.renter != ""){
        std::cout << "Do you want to borrow this book (Yes/No): " ;
        std::cin >> confirmBorrow;
        if (confirmBorrow == "Yes" || confirmBorrow == "yes") {
            confirmBorrow_bool = 1;
        }else {
            confirmBorrow_bool = 0;
        }
        std::cout << "\nBorrowing a book...\n";
    
        if (confirmBorrow_bool == true){
            Found_Book.rented = true;
            Found_Book.renter = loggedInUser;

            updateBookInfo(filename, Found_Book);
        }else{
            std::cout << "Error" << std::endl;
        }        
    }else{
        std::cout << "Book has already been borrowed";
    }
}

bool checkIfBookRented(std::string filename, std::string book) {
    std::vector result = searchBooks(filename, book);

    std::cout << result[0].rented << " " << result[0].renter << std::endl;

    return false;
}

// Struct to hold book information
struct user {
    int id;
    std::string username;
    std::string password;
    std::string fullName;
    std::string dob;

    // For sorting and comparison
    bool operator<(const user& other) const {
        return username < other.username;
    }
};

// Function to parse a line from the file into a Book struct
user parseUserLine(const std::string& line) {
    std::stringstream ss(line);
    user  users;
    std::string temp;

    std::getline(ss, temp, '-'); // Ignore the initial -
    ss >> users.id;
    std::getline(ss, temp, '-'); // Ignore the -
    std::getline(ss, users.username, '-');
    std::getline(ss, users.password, '-');
    std::getline(ss, users.fullName, '-');
    std::getline(ss, users.dob, '-');

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

    trim(users.username);
    trim(users.password);
    trim(users.fullName);
    trim(users.dob);

    return users;
}

// Function to perform binary search on a vector of books
int SearchUs(const std::vector<user>& user, const std::string& title) {
    int left = 0, right = user.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // Trim whitespace before comparison
        std::string trimmedSearchTitle = title;
        trim(trimmedSearchTitle); 
        std::string trimmedBookTitle = user[mid].username; 
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

std::vector<user> searchUsers(std::string filename, std::string logged_in_user) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return {}; // Return an empty vector if file opening fails
    }

    std::vector<user> users;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(parseUserLine(line));
        }
    }

    file.close();

    // Sort the books by title for binary search
    std::sort(users.begin(), users.end());

    std::string searchTitle = logged_in_user;
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

    std::vector<user> foundBooks;

    int index = SearchUs(users, searchTitle);

    if (index != -1) {
        // Correctly handle reading the previous line
        if (index > 0) {
            index--;
        }
        const user& founduser = users[index];
        foundBooks.push_back(founduser);
    } else {
        std::cerr << "Username does not exist" << std::endl;
    }

    return foundBooks;
}

bool searchUsersExist(std::string filename, std::string logged_in_user) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    std::vector<user> users;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(parseUserLine(line));
        }
    }

    file.close();

    // Sort the users by username for binary search
    std::sort(users.begin(), users.end());

    auto trim = [](std::string &str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos) {
            str = "";
        } else {
            str = str.substr(first, (last - first + 1));
        }
    };

    std::string searchUsername = logged_in_user;
    trim(searchUsername);

    user searchUser{0, searchUsername, "", "", ""};

    // Binary search to check if the username exists in the sorted list
    bool found = std::binary_search(users.begin(), users.end(), searchUser);

    return found;
}

void updateProfileInfo(std::string filename, user updatedUser) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::vector<user> users;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(parseUserLine(line));
        }
    }

    file.close();

    // Find and update the book
    bool userFound = false;
    for (auto& user : users) {
        if (user.id == updatedUser.id) {
            user = updatedUser;
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        std::cerr << "Book with ID " << updatedUser.id << " not found." << std::endl;
        return;
    }

    // Write the updated books back to the file, ignoring blank lines
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const auto& user : users) {
        outFile << "- " << user.id << " - " << user.username << " - " << user.password << " - " << user.fullName << " - " << user.dob << " - " << std::endl;
    }

    outFile.close();
}

void updateUser(std::string filename, std::string loggedInUser) {
    std::cout << "\nUpdating user information...\n";

    std::vector result = searchUsers(filename, loggedInUser);
    user& userFound = result[0];
    
    // Check if any books were found
    if (!result.empty()) {
        std::cout << "USer to Update:" << std::endl;
        for (const auto& user : result) {
            // Access and use the data of each found book
            std::cout << "Username: " << user.username << std::endl;
            std::cout << "Password: " << user.password << std::endl;
            std::cout << "Full Name: " << user.fullName << std::endl;
            std::cout << "Date Of Birth: " << user.dob << std::endl;
        }
    }

    // no idea how to convert the array to be able to use result[1], result[2]
    std::string y_n = " ";
    std::cout << "Would you like to update username:  " << userFound.username << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        userFound.username = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
    }

    std::cout << "Would you like to update password: " << userFound.password << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        userFound.password = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }

    std::cout << "Would you like to update full name: " << userFound.fullName << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        userFound.fullName = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }

    std::cout << "Would you like to update full name: " << userFound.dob << "? <Y/N> ";
    std::cin >> y_n;
    if(y_n == "Y" || y_n == "y") {
        std::string update;
        std::cout << "Update to: ";
        std::cin.ignore();
        std::getline(std::cin, update);
        userFound.dob = update;
        std:: cout << std::endl;
    }else if (y_n == "n" || y_n == "N") {
        std::cout << "No Update.\n";
    } else {
        std::cout << "Invalid Input!";
        std:: cout << std::endl;
    }

    updateProfileInfo(filename, userFound);

    std::cout << "User Information Update Successfully!\n";
}

void regUser(std::string username, std::string password, std::string fullName, std::string birthDate) {

    std::fstream user_database("database/user_data.txt");
    int user_id;

    if (user_database.is_open()) { //checks last line and grabs data of the last book added
        
        std::string last_line = readLastLine("database/user_data.txt"); //grabs last line and stores it in to var
        std::getline(user_database, last_line);
        std::vector<std::string> last_book_entered;
        std::stringstream ss(readLastLine("database/user_data.txt"));
        std::string token;

        int counter = 0;
        while(getline(ss, token, '-')) {  //stores each line minus the '-' into an array
            token.erase(0, token.find_first_not_of(" ")); // Trim leading spaces
            token.erase(token.find_last_not_of(" ") + 1); // Trim trailing spaces
            last_book_entered.push_back(token);    
            counter++;            
        }

        user_id = stoi(last_book_entered[1]); // adds 1 to book id
        user_id++;
        std::string lbreak = " - ";
        user_database.close();
        std::fstream book_database;
        book_database.open("database/user_data.txt", std::ios::app);
        book_database << "\n- " << user_id << lbreak << username << lbreak << password << lbreak << fullName << lbreak << birthDate << lbreak;
        book_database.close();
    }else {
        std::cout << "error";
    }


}

void signUp(std::string username, std::string password, std::string fullName, std::string birthDate) {
    
    int loop = 0;
    std::string newUsername = username;
    while(loop == 0) {
        if (searchUsersExist("database/user_data.txt", newUsername) == true) {
            std::cout << "Error: Username already taken. Try again!" << std::endl;
            std::cout << "Enter New Username: ";
            std::getline(std::cin, newUsername);
        } else {
            std::cout << "Registered!" << std::endl;
            regUser(newUsername, password, fullName, birthDate);
            loop = 1;
        }
    }

}

std::string logIn() {
    int loop = 0;
    std::string username;
    std::string password;

   while(loop == 0) {  
        std::cout << "\nUsername: ";
        std::getline(std::cin, username);
        std::cout << "\nPassword: ";
        std::cin >> password;
    
        if (searchUsersExist("database/user_data.txt", username) == false ){
            std::cout << "Error: User Does not Exisit";
        }else {
        
            std::vector result = searchUsers("database/user_data.txt", username);
            if (username == result[0].username && password == result[0].password) {
                std::cout << "\nLogged In!" << std::endl;
                loop = 1;
                return username;
            }else {
                std::cout << "\nLoggin Failed" << std::endl;
            }
        }
    }
    return username;
}

bool isAdminTxt(std::string filename, std::string logged_in_user) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    int offset;
    std::string line;
    
    while (!file.eof()) {
        std::getline(file, line);
        if ((offset = line.find(logged_in_user, 0)) != std::string::npos) {
            file.close();
            return true;
        } else {
            return false;
        }
    }

    return false;
}

bool isAdminVector(std::string logged_in_user, std::vector<std::string> adminList) {
    if (std::find(adminList.begin(), adminList.end(), logged_in_user) != adminList.end()) {
        return true;
    }else {
        return false;
    }

    return false;
}

void removeUser(std::string filename, std::string user) {
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
    std::string searchUser = " " + user + " ";
    bool userFound = false;

    while(std::getline(inputFile, line)) {
        if(line.find(searchUser) != std::string::npos) {
            userFound = true;
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

    if(userFound) {
        if(std::remove(filename.c_str()) != 0) {
            std::cerr << "Error deleting the original file." << std::endl;
            return;
        }
        if(std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
            std::cerr << "Error renaming the temporary file." << std::endl;
        }
        std::cout << "User Deleted successfully." << std::endl;
    }else {
        std::cout << "User not found" << std::endl;
        std::remove(tempFilename.c_str());
    }
}

static const std::vector<std::string> admins = { "esting2" , " "};

void adminRemoveUser(std::string filename, std::string logged_in_user, std::string check_admin_type, std::string userToDelete) {
    if (check_admin_type == "Text") {
        if(isAdminTxt("database/admin_users.txt", logged_in_user) == true) {
            removeUser(filename, userToDelete);
        }else {
            std::cerr << "Error: Invalid User --- No Permission" << std::endl;
        }
    }else if (check_admin_type == "Vector") {
        if(isAdminVector(filename, admins) == true) {
            removeUser(filename, userToDelete);
        }else {
            std::cerr << "Error: Invalid User --- No Permission" << std::endl;
        }
    } else {
        std::cerr << "Invalid Check Type: Try again with 'Text' or 'Vector'" << std::endl;
    }


}

void adminUpdateUser(std::string filename, std::string logged_in_user, std::string check_admin_type, std::string userToUpdate) {
    if (check_admin_type == "Text") {
        if(isAdminTxt("database/admin_users.txt", logged_in_user) == true) {
            updateUser(filename, userToUpdate);
        }else {
            std::cerr << "Error: Invalid User --- No Permission" << std::endl;
        }
    }else if (check_admin_type == "Vector") {
        if(isAdminVector(filename, admins) == true) {
            updateUser(filename, userToUpdate);
        }else {
            std::cerr << "Error: Invalid User --- No Permission" << std::endl;
        }
    } else {
        std::cerr << "Invalid Check Type: Try again with 'Text' or 'Vector'" << std::endl;
    }


}

void viewAllLoan(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        std::cout << "\nViewing all loans...\n";
        while (std::getline(file, line)) {
            // Check if the line ends with " - -"
            if (line.size() >= 4 && line.substr(line.size() - 4) != "  - ") {
                std::cout << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

void returnBook(std::string filename, std::string loggedInUser) {
    std::string bookTitle, confirmReturnAsk;
    bool confirmReturn;
    
    bool confirmBorrow;
    
    std::cout << "Enter the book you'd like to return: ";
    std::cin >> bookTitle;
    
    std::vector result = searchBooks(filename, bookTitle);
    Book& Found_Book = result[0];
    std::string borrowedUser = result[0].renter;
    std::cout << "\nReturning a book...\n";
   // if (loggedInUser == result[0].renter){
        std::cout << "Do you want to return this book (Yes/No) ";
            
        std::cin >> confirmReturnAsk;
            
        if(confirmReturnAsk == "Yes" || confirmReturnAsk == "yes"){
            Found_Book.rented = false;
            Found_Book.renter = "";
            updateBookInfo(filename, Found_Book);
        }
   // }else{
   //     std::cout << "Error" << std::endl;
   // }
}

void viewBorrowedBooks(std::string filename, std::string logged_in_user) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        std::vector<Book> borrowedBooks;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                Book book = parseBookLine(line);
                if (book.rented && book.renter == logged_in_user) {
                    borrowedBooks.push_back(book);
                }
            }
        }
        file.close();

        // Display borrowed books
        if (borrowedBooks.empty()) {
            std::cout << "No books borrowed by " << logged_in_user << ".\n";
        } else {
            std::cout << "Books borrowed by " << logged_in_user << ":\n";
            for (const auto& book : borrowedBooks) {
                std::cout << "ID: " << book.id << ", Title: " << book.title 
                          << ", Author: " << book.author << ", Pages: " << book.pages 
                          << ", Subject: " << book.subject << ", Genre: " << book.genre 
                          << ", Release Year: " << book.release_year 
                          << ", Type: " << book.type << ", Description: " << book.desc 
                          << std::endl;
            }
        }
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void viewAllLoans(std::string filename, std::string logged_in_user, std::string admin_check_type, std::string admin_file) {

    if (admin_check_type == "Text" || admin_check_type == "txt" || admin_check_type == "text") {
        bool admin_status = isAdminTxt(admin_file, logged_in_user);
        if (admin_status == true) {
            viewAllLoan(filename);
        }else {
            std::cout << "Not Admin!";
        }
    }else if(admin_check_type == "Vector" || admin_check_type == "vector") {
        bool admin_status = isAdminVector(logged_in_user, admins);
        if (admin_status == true) {
            viewAllLoan(filename);
        }else {
            std::cout << "Not Admin!";
        }
    } else {
        std::cerr << "Unable to open file";
    }
}
