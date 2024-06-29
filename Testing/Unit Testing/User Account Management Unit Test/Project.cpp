//Rachel Georges
//Project: User Account Management
//05/30/2024

using namespace std;
#include <iostream>
#include <map>
#include <iomanip>
#include <cstring>


class User{
    private:
        string name;
        string password;
    public:
        User() : name(""), password(""){
        } //default constructor to assign to empty strings.
        User(string name, string password) : name(name), password(password){
        } // assigns the parameters when given values.
        string getName(){
            return name;
        } // gets stored name for the user and provides it.
        string getPassword(){
            return password;
        } // gets stored password for the user and provides it.
};

class Users{
    private:
        map<string, User> userMap; //creates hash mapping key, value pairs to create database.
        User getUser(string userName){
            return userMap[userName];
        }
    public:
        Users(){
        }
        void registerUser(User noob){
            userMap.insert({noob.getName(), noob}); //creates potential to register new users to userMap.
        }
        bool login(string userName, string password){ // checks to see if user() matches the login username and password
            User oldie = getUser(userName); // the attempted login
            if (password == oldie.getPassword()){ // does the password associated with attempted username match the password
                return true;
            }
            return false;
        }
};

int main(){
    User user("bob", "123");
    cout << user.getName();
    Users users;
    users.registerUser(user);
    cout << users.login("bobb", "123");
    return 0;
} // The above function ran a test to ensure bool works.