#include <iostream>

#ifndef userAuth_hpp
#define userAuth_hpp

using namespace std;

struct User{
    int id;
    string username;
};

struct UserAuth{
    User user;
    string password;
};

void displayUsers(string, fstream&);

bool userExist(string , fstream& , string , string , User& , bool );

void logIn(string , fstream& , User& , bool& );

void createAccount(string , fstream& , User& );

#endif /* userAuth_hpp */
