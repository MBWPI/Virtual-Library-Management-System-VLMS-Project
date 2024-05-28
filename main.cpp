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
    // Prepopulate some users for testing
    users["admin"] = User("admin", "admin", "admin");
    users["user1"] = User("user1", "password", "user");

    preLoginMenu();
    return 0;
}
