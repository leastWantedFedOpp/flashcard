#include <iostream>

#ifndef userAuth_hpp
#define userAuth_hpp

using namespace std;

struct UserTemplate{
    int id;
    string username;
};

struct User{
    UserTemplate user;
    string password;
};

struct CurrentUser{
    UserTemplate currentUser;
};

void displayUsers(string, fstream&);

bool userExist(string , fstream& , string , string , CurrentUser& , bool );

void logIn(string , fstream& , CurrentUser& , bool& );

void createAccount(string , fstream& , CurrentUser& );


#endif /* userAuth_hpp */
