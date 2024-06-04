#include "user.h"

User::User() : username(""), password(""), role("user") {} // Default constructor definition

User::User(std::string u, std::string p, std::string r) : username(u), password(p), role(r) {}
