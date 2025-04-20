#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct User{
    int id;
    string username;
    string password;
};

struct CurrentUser{
    int id;
    string username;
};

int genUserid(){
    srand(unsigned(time(0)));
    int randGenUserId = rand() % 9000 + 1000;
    return randGenUserId;
}

void logIn(){
    int id;
    string username, password;
    cout << "Log in" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    //look in userData.csv
    //if user is found then take that users info (id, name) and set it to CurrentUser?
}

void createAccount(){
    int id;
    string username, password;
    cout << "Create an account" << endl;
    id = genUserid();
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    //append to userData.csv
    User newUser = {id, username, password};
}


void authUser(){
    //open a file called Users.csv
    //read
    char userInput = '\0';
    cout << "a. Login\nb.Create an account" << endl;
    cin >> userInput;
    switch (userInput) {
        case 'a':
            logIn(); //pass csv file
            break;
        case 'b':
            createAccount(); //pass csv file
            break;
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    //working on logIn/create account
    cout << "FlashCard" << endl;
    authUser();
    return 0;
}


//login or create an account
/*
 main func
    |_ auth func
        |_log func that return bool isUserLoggedIn ? authenticated == true : cout << "try again or create account";
        |_createAcc func - after user create account, they'll be redirected to auth func, where they'll have to log in, creating account != authenticated
 
 */
