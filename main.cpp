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

int genUserid(){
    srand(unsigned(time(0)));
    int randGenUserId = rand() % 9000 + 1000;
    return randGenUserId;
}

void authUser(char userInput){
    int id;
    string username, password;
    if(userInput == 'a'){
        cout << "Log in" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        //look in userData.csv
    } else if (userInput == 'b'){
        cout << "Create an account" << endl;
        id = genUserid();
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        //append to userData.csv
        User newUser = {id, username, password};
    } else {
        cout << "Invalid input" << endl;
    }
}

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    //working on logIn/create account
    cout << "FlashCard" << endl;
    cout << "a. Login\nb.Create an account" << endl;
    cin >> userInput;
    switch (userInput) {
        case 'a':
            //log in
            break;
        case 'b':
            //create an account
            break;
        default:
            break;
    }
    return 0;
}


//login or create an account
/*
 main func
    |_ auth func
        |_log func that return bool isUserLoggedIn ? authenticated == true : cout << "try again or create account";
        |_createAcc func - after user create account, they'll be redirected to auth func, where they'll have to log in, creating account != authenticated
 
 */
