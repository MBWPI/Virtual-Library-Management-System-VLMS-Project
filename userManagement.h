#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include "user.h"

#include <string>
#include <unordered_map>
#include <vector>

// User Account Management team (Rachel Georges) work implemented here

// Hash Map Implementation
extern std::unordered_map<std::string, User> users;

// User Account Management
class UserManagement {
public:
    void saveUsersToFile(const std::string &filename);
    void loadUsersFromFile(const std::string &filename);
    void addUser(const User &user, bool showMessage = true);
    void removeUser(const std::string &username);
    User* findUser(const std::string &username);

private:
    std::vector<User> users;  // Keeping the vector if needed elsewhere
    std::unordered_map<std::string, User> userMap;  // Hash map for efficient look-up
};

// Book Management
void searchBooks();
void borrowBook();
void returnBook();
void viewBorrowedBooks();
void addBook();
void removeBook();
void updateBookInfo();
void viewAllLoans();
// Admin User Management
void login(UserManagement &userManager);
void registerUser(UserManagement &userManager);
std::string updateProfile(const std::string &currentUsername);
void addUser(const User &user);
void removeUser(const std::string &username);

#endif // USERMANAGEMENT_H
