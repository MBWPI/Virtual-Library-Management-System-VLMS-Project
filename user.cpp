#include "user.h"

// User Account Management team (Rachel Georges) work implemented here

User::User() : username(""), password(""), role("") {}

User::User(const std::string &u, const std::string &p, const std::string &r)
    : username(u), password(p), role(r) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getRole() const {
    return role;
}

std::string User::getName() const {
    return username;
}
