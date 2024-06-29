#ifndef MENU_H
#define MENU_H

#include "user.h"
#include "userManagement.h"

#include <string>

void preLoginMenu(UserManagement &userManager);
void userMenu(std::string username);
void adminMenu();
void manageUsers();

extern UserManagement userManager;

#endif // MENU_H
