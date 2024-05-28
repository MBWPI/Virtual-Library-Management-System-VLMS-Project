#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    std::string role;

    User();
    User(std::string u, std::string p, std::string r);
};

#endif // USER_H
