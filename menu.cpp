#include "menu.h"
#include "userManagement.h"
#include "libraryOperations.h"
#include <iostream>
#include <limits>

void preLoginMenu() {
    int choice;
    do {
        std::cout << "\nWelcome to the Virtual Library Management System\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "\n1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "\nPlease select an option: ";

        // Validate user input
        if (!(std::cin >> choice)) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                std::cout << "\nGoodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 3);
}

void userMenu(const std::string &username) {
    int choice;
    do {
        std::cout << "\nWelcome " << username << ", you're logged in as a user.\n";
        std::cout << "--------------------------------\n";
        std::cout << "\n1. Search for Books\n";
        std::cout << "2. Borrow a Book\n";
        std::cout << "3. Return a Book\n";
        std::cout << "4. View Borrowed Books\n";
        std::cout << "5. Update Profile\n";
        std::cout << "6. Logout\n";
        std::cout << "\nPlease select an option: ";

        // Validate user input
        if (!(std::cin >> choice)) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "\nInvalid choice, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                viewBorrowedBooks();
                break;
            case 5:
                updateProfile();
                break;
            case 6:
                std::cout << "\nLogging out...\n";
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
                break;
        }
    } while (choice != 6);
}

void adminMenu() {
    int choice;
    do {
        std::cout << "\nAdmin Dashboard\n";
        std::cout << "---------------\n";
        std::cout << "\n1. Add a Book\n";
        std::cout << "2. Remove a Book\n";
        std::cout << "3. Update Book Information\n";
        std::cout << "4. View All Loans\n";
        std::cout << "5. Add/Remove User (Admins)\n";
        std::cout << "6. Logout\n";
        std::cout << "\nPlease select an option: ";

        // Validate user input
        if (!(std::cin >> choice)) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
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
                viewAllLoans();
                break;
            case 5:
                manageUsers();
                break;
            case 6:
                std::cout << "\nLogging out...\n";
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 6);
}
