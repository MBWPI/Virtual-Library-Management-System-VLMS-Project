#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>


// Rachel Georges - User Account Management

class User{
    private:
        std::string username;
        std::string password;
        std::string role;
    public:
        User();
        User(std::string u, std::string p, std::string r);
        std::string getName() const {
            return username;
        } // gets stored name for the user and provides it.
        std::string getPassword() const {
            return password;
        } // gets stored password for the user and provides it.
        std::string getRole() const {
            return role;
        } // gets stored role for the user and provides it.
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
