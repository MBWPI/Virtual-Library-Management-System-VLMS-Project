#include "userManagement.h"
#include "menu.h"
#include <iostream>
#include <limits>
#include <vector>

std::unordered_map<std::string, User> users;

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void login(Users &users) {
    std::string username, password;
    std::cout << "\nUsername: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

        if (users.login(username, password)) {
        if (users.getUser(username).getRole() == "admin") {
            adminMenu();
        } else {
            userMenu(username);
        }
    } else {
        std::cout << "\nInvalid username or password.\n";
    }
}

void registerUser(Users &users) {
    std::string username, password;
    std::cout << "\nEnter new username: ";
    std::cin >> username;
    std::cout << "Enter new password: ";
    std::cin >> password;

    if (!users.userExists(username)) {
        users.registerUser(User(username, password, "user"));
        std::cout << "\nRegistration successful!\n";
    } else {
        std::cout << "\nUsername already exists.\n";
    }
}
