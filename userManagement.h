#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <unordered_map>
#include "user.h"
#include <string>

extern std::unordered_map<std::string, User> users;

void clearInput();
void login(Users &users);
void registerUser(Users &users);

#endif // USERMANAGEMENT_H
