#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Struct for user information
struct user {
    std::string username;
    std::string password;
    std::string fullName;
    std::string dob;

    bool operator<(const user& other) const {
        return username < other.username;
    }
};

// Struct for book information
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
    std::string renter;
};

// Function declarations
int SearchUs(const std::vector<user>& user, const std::string& title);
void viewBooks(std::string filename, std::string logged_in_user);
bool isAdminTxt(std::string filename, std::string logged_in_user);
bool isAdminVector(std::string logged_in_user, std::vector<user> admins);
void viewAllLoan(std::string filename);
void viewAllLoans(std::string filename, std::string logged_in_user, std::string admin_check_type, std::string admin_file);
void viewBorrowedBooks(std::string filename, std::string logged_in_user);

#endif // FUNCTIONS_H
