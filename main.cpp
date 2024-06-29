// Virtual Library Management System (VLMS) Project
// Group 2 Group Project

// Version 4
// Stable version
// Book Management added

// Jackson Hopkins - Book Management II / Project Manager
// Fadi Kanana - Data Persistence
// Ian Laabs - Book Management I
// Jonathan Jones - Interface and Navigation I
// Michael Beland - Interface and Navigation II
// Rachel Georges - User Account Management

// Instructor: Nilan Karunaratne
// Date: 06/28/2024

#include "libraryOperations.h"
#include "menu.h"
#include "userManagement.h"
#include "utility.h"

#include <iostream>
#include <limits>

UserManagement userManager;

int main() {
    userManager.addUser(User("admin", "admin", "admin"), false);
    userManager.loadUsersFromFile("database/users.txt");
    preLoginMenu(userManager);
    userManager.saveUsersToFile("database/users.txt");
    
    return 0;
}
