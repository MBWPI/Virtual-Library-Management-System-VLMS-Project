#include "userManagement.h"
#include "menu.h"
#include "user.h"
#include "utility.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

// User Account Management team (Rachel Georges) work implemented here

// Hash Map Implementation
std::unordered_map<std::string, User> users;

void login(UserManagement &userManager) {
    std::string username, password;
    std::cout << "\nUsername: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    User *user = userManager.findUser(username);
    if (user && user->getPassword() == password) {
        if (user->getRole() == "admin") {
            adminMenu();
        } else {
            userMenu(username);
        }
    } else {
        std::cout << "\nInvalid username or password.\n";
    }
}

void registerUser(UserManagement &userManager) {
    std::string username, password;
    std::cout << "\nEnter new username: ";
    std::cin >> username;
    std::cout << "Enter new password: ";
    std::cin >> password;

    if (!userManager.findUser(username)) {
        userManager.addUser(User(username, password, "user"), true);
        std::cout << "\nRegistration successful!\n";
        userManager.saveUsersToFile("database/users.txt");
    } else {
        std::cout << "\nUsername already exists.\n";
    }
}

std::string updateProfile(const std::string &currentUsername) {
    std::cout << "\nUpdating profile...\n";
    std::string newUsername, newPassword;
    std::cout << "\nEnter new username: ";
    std::cin >> newUsername;
    std::cout << "Enter new password: ";
    std::cin >> newPassword;

    std::ifstream infile("database/users.txt");
    std::ofstream outfile("database/temp.txt");
    std::string line;
    bool userUpdated = false;
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::string username, password, role;
        ss >> username >> password >> role;
        if (username == currentUsername) {
            outfile << newUsername << " " << newPassword << " " << role << std::endl;
            userUpdated = true;
        } else {
            outfile << line << std::endl;
        }
    }
    infile.close();
    outfile.close();
    std::remove("database/users.txt");
    std::rename("database/temp.txt", "database/users.txt");

    if (userUpdated) {
        userManager.removeUser(currentUsername);
        userManager.addUser(User(newUsername, newPassword, "user"), false);
        userManager.saveUsersToFile("database/users.txt");

        // Update transactions
        std::ifstream transfile("database/transactions.txt");
        std::ofstream transtemp("database/temp_transactions.txt");
        std::string transLine;
        while (std::getline(transfile, transLine)) {
            if (transLine.find(currentUsername) != std::string::npos) {
                size_t pos = transLine.find(currentUsername);
                if (pos != std::string::npos) {
                    transLine.replace(pos, currentUsername.length(), newUsername);
                }
            }
            transtemp << transLine << std::endl;
        }
        transfile.close();
        transtemp.close();
        std::remove("database/transactions.txt");
        std::rename("database/temp_transactions.txt", "database/transactions.txt");

        return newUsername;
    } else {
        std::cout << "\nFailed to update profile. User not found.\n";
        return currentUsername;
    }
}

/*
 * UserManagement class:
 * We use an unordered_map (hash map) named userMap to store users for efficient look-up.
 * This allows for average O(1) complexity for insertions, deletions, and access operations.
 * 
 * - saveUsersToFile: Serializes user data to a file.
 * - loadUsersFromFile: Deserializes user data from a file.
 * - addUser: Adds a user to the hash map and optional vector.
 * - findUser: Efficiently finds a user by username using the hash map.
 */

void UserManagement::saveUsersToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto &pair : userMap) {
        const User &user = pair.second;
        file << user.getUsername() << " " << user.getPassword() << " " << user.getRole() << "\n";
    }
    file.close();
}

void UserManagement::loadUsersFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }
    std::string username, password, role;
    while (file >> username >> password >> role) {
        User user(username, password, role);
        userMap[username] = user;
    }
    file.close();
}

void UserManagement::addUser(const User &user, bool showMessage) { // Removed default argument
    if (userMap.find(user.getUsername()) != userMap.end()) {
        std::cout << "\nUser already exists.\n";
        return;
    }
    userMap[user.getUsername()] = user;
    users.push_back(user);
    if (showMessage) {
        std::cout << "\nUser added successfully.\n";
    }
}

void UserManagement::removeUser(const std::string &username) {
    auto it = userMap.find(username);
    if (it == userMap.end()) {
        std::cout << "\nUser not found.\n";
        return;
    }
    userMap.erase(it);
    users.erase(std::remove_if(users.begin(), users.end(), [&](const User &u) { return u.getUsername() == username; }), users.end());
    std::cout << "\nUser removed successfully.\n";
    saveUsersToFile("database/users.txt");  // Save users after removal
}

User* UserManagement::findUser(const std::string &username) {
    auto it = userMap.find(username);
    if (it != userMap.end()) {
        return &it->second;
    }
    return nullptr;
}
