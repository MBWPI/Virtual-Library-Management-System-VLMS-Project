#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <unordered_map>
#include "user.h"

extern std::unordered_map<std::string, User> users;

void clearInput();
void login();
void registerUser();

#endif // USERMANAGEMENT_H
