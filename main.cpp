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

#include "menu.h"
#include "userManagement.h"

int main() {
    Users users;
    
    // Prepopulate some users for testing
    users.registerUser(User("admin", "admin", "admin"));
    users.registerUser(User("user1", "password", "user"));

    preLoginMenu(users);
    return 0;

}
