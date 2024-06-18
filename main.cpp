// Virtual Library Management System (VLMS) Project
// Group 2 Group Project
// Jackson Hopkins - Book Management II / Project Manager
// Fadi Kanana - Data Persistence
// Ian Laabs - Book Management I
// Jonathan Jones - Interface and Navigation I
// Michael Beland - Interface and Navigation II
// Rachel Georges - User Account Management
// Instructor: Nilan Karunaratne
// Date: 05/23/2024

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>

class User {
public:
    std::string username;
    std::string password;
    std::string role;

    User() : username(""), password(""), role("user") {}  // Default constructor

    User(std::string u, std::string p, std::string r) : username(u), password(p), role(r) {}
};

std::unordered_map<std::string, User> users;

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void preLoginMenu();
void userMenu(const std::string &username);
void adminMenu();

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

void preLoginMenu() {
    int choice;
    do {
        std::cout << "Welcome to the Virtual Library Management System\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 3);
}

void searchBooks() {
    std::cout << "Searching for books...\n";
}

void borrowBook() {
    std::cout << "Borrowing a book...\n";
}

void returnBook() {
    std::cout << "Returning a book...\n";
}

void viewBorrowedBooks() {
    std::cout << "Viewing borrowed books...\n";
}

void updateProfile() {
    std::cout << "Updating profile...\n";
}

void userMenu(const std::string &username) {
    int choice;
    do {
        std::cout << "Welcome " << username << ", you're logged in as a user.\n";
        std::cout << "--------------------------------\n";
        std::cout << "1. Search for Books\n";
        std::cout << "2. Borrow a Book\n";
        std::cout << "3. Return a Book\n";
        std::cout << "4. View Borrowed Books\n";
        std::cout << "5. Update Profile\n";
        std::cout << "6. Logout\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

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
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);
}

void addBook() {
    std::cout << "Adding a book...\n";
}

void removeBook() {
    std::cout << "Removing a book...\n";
}

void updateBookInfo() {
    std::cout << "Updating book information...\n";
}

void viewAllLoans() {
    std::cout << "Viewing all loans...\n";
}

void manageUsers() {
    std::cout << "Managing users...\n";
}

void adminMenu() {
    int choice;
    do {
        std::cout << "Admin Dashboard\n";
        std::cout << "---------------\n";
        std::cout << "1. Add a Book\n";
        std::cout << "2. Remove a Book\n";
        std::cout << "3. Update Book Information\n";
        std::cout << "4. View All Loans\n";
        std::cout << "5. Add/Remove User (Admins)\n";
        std::cout << "6. Logout\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

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
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);
}

int main() {
    // Prepopulate some users for testing
    users["admin"] = User("admin", "admin", "admin");
    users["user1"] = User("user1", "password", "user");

    preLoginMenu();
    return 0;
}
