#include "userManagement.h"
#include "menu.h"
#include <iostream>
#include <limits>

std::unordered_map<std::string, User> users;

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void login() {
    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (users.find(username) != users.end() && users[username].password == password) {
        if (users[username].role == "admin") {
            adminMenu();
        } else {
            userMenu(username);
        }
    } else {
        std::cout << "Invalid username or password.\n";
    }
}

void registerUser() {
    std::string username, password;
    std::cout << "Enter new username: ";
    std::cin >> username;
    std::cout << "Enter new password: ";
    std::cin >> password;

    if (users.find(username) == users.end()) {
        users[username] = User(username, password, "user");
        std::cout << "Registration successful!\n";
    } else {
        std::cout << "Username already exists.\n";
    }
}
