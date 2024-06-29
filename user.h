#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>


// User Account Management team (Rachel Georges) work implemented here

class User{
    public:
        User();
        User(const std::string &u, const std::string &p, const std::string &r = "");
        std::string getUsername() const;
        std::string getPassword() const;
        std::string getRole() const;
        std::string getName() const;
        // Other getters and setters
    private:
        std::string username;
        std::string password;
        std::string role;
};

class Users{
    private:
        std::unordered_map<std::string, User> userMap; //creates hash mapping key, value pairs to create database.

    public:
        Users() {}

        void registerUser(const User& noob) {
            userMap.insert({noob.getName(), noob}); //creates potential to register new users to userMap.
        }

        bool login(const std::string& userName, const std::string& password) const {
            auto it = userMap.find(userName);
            if (it != userMap.end() && it->second.getPassword() == password) {
                return true;
            }
            return false;
        }

        const User& getUser(const std::string& userName) const { // Changed return type to User&
            return userMap.at(userName);
        }

        bool userExists(const std::string& userName) const {
            return userMap.find(userName) != userMap.end();
        }
};

#endif // USER_H
