#ifndef MENU_H
#define MENU_H

#include "user.h"
#include <string>

void preLoginMenu(Users &users);
void userMenu(const std::string& username);
void adminMenu();

#endif // MENU_H
