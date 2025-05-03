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

void displayUsers(filesystem::path );

bool userExist(filesystem::path , string , string , User& , bool );

void logIn(filesystem::path , User& , bool& );

void createAccount(filesystem::path , User& );

#endif /* userAuth_hpp */
