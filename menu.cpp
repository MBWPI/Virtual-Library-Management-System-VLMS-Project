#include "libraryOperations.h"
#include "menu.h"
#include "userManagement.h"
#include "utility.h"

#include <iostream>
#include <limits>

extern UserManagement userManager;

void preLoginMenu(UserManagement &userManager) { // Changed from Users &users to UserManagement &userManager
    int choice;
    do {
        std::cout << "\nWelcome to the Virtual Library Management System\n";
        std::cout << "\n------------------------------------------------\n";
        std::cout << "\n1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "\nPlease select an option: ";
        
        // Validate user input
        if (!(std::cin >> choice)) {
            clearInput(); // Use the clearInput function from utility.cpp
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                login(userManager);
                break;
            case 2:
                registerUser(userManager);
                break;
            case 3:
                std::cout << "\nGoodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
                clearInput();
                break;
        }
    } while (choice != 3);
}

void userMenu(std::string username) {
    int choice;
    do {
        std::cout << "\nWelcome " << username << ", you're logged in as a user.\n";
        std::cout << "\n--------------------------------\n";
        std::cout << "\n1. Search for Books\n";
        std::cout << "2. Borrow a Book\n";
        std::cout << "3. Return a Book\n";
        std::cout << "4. View Borrowed Books\n";
        std::cout << "5. Update Profile\n";
        std::cout << "6. Logout\n";
        std::cout << "\nPlease select an option: ";

        // Validate user input
        if (!(std::cin >> choice)) {
            clearInput(); // Use the clearInput function from utility.cpp
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                LibraryOperations::searchBooks();
                break;
            case 2:
                LibraryOperations::borrowBook(username);
                break;
            case 3:
                LibraryOperations::returnBook(username);
                break;
            case 4:
                viewBorrowedBooks(username);
                break;
            case 5:
                username = updateProfile(username);
                break;
            case 6:
                std::cout << "\nLogging out...\n";
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
                clearInput();
                break;
        }
    } while (choice != 6);
}

void adminMenu() {
    int choice;
    
    do {
        std::cout << "\nAdmin Dashboard\n";
        std::cout << "\n---------------\n";
        std::cout << "\n1. Add a Book\n";
        std::cout << "2. Remove a Book\n";
        std::cout << "3. Update Book Information\n";
        std::cout << "4. View All Loans\n";
        std::cout << "5. Add/Remove User (Admins)\n";
        std::cout << "6. Logout\n";
        std::cout << "\nEnter your choice: ";
        
        // Validate user input
        if (!(std::cin >> choice)) {
            clearInput(); // Use the clearInput function from utility.cpp
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            updateBookInfo();
            break;
        case 4:
            viewAllLoans("admin");
            break;
        case 5:
            manageUsers();
            break;
        case 6:
            std::cout << "\nLogging out...\n";
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            clearInput();
            break;
        }
    } while (choice != 6);
}

void manageUsers() {
    int choice;
    std::string username, password;

    do {
        std::cout << "\nManaging users...\n";
        std::cout << "\n1. Add User\n";
        std::cout << "2. Remove User\n";
        std::cout << "3. Back to Admin Menu\n";
        std::cout << "\nEnter your choice: ";

        // Validate user input
        if (!(std::cin >> choice)) {
            clearInput(); // Use the clearInput function from utility.cpp
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            std::cin.ignore(); // Ignore remaining newline character from previous input
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            // userManager.addUser(User(username, password));
            if (!userManager.findUser(username)) {
                userManager.addUser(User(username, password, "user"), true);
                std::cout << "\nRegistration successful!\n";
                userManager.saveUsersToFile("database/users.txt");
            } else {
                std::cout << "\nUsername already exists.\n";
            }
            break;
        case 2:
            std::cin.ignore(); // Ignore remaining newline character from previous input
            std::cout << "Enter username to remove: ";
            std::getline(std::cin, username);
            userManager.removeUser(username);
            break;
        case 3:
            std::cout << "\nBack to Admin Menu...\n";
            return;
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            clearInput();
            break;
        }
    } while (choice != 3);
}
