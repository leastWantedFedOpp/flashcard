#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "utils/userAuth.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    bool isAuthenticated = false;
    bool running = true;
    CurrentUser currentUser = {{0,""}}; //id set to 0, username set to empty string
    
    cout << "Current working directory: " << filesystem::current_path() << endl;
    fstream data;
    
    while (running) {
        cout << "FlashCard" << endl;
        while (userInput != 'c') {
            cout << "a. Login\nb. Create an account\nc. Exit\nd. Display UserList" << endl;
            cout << "-> ";
            cin >> userInput;
            
            if (userInput == 'a') {
                cout << "Logging in..." << endl;
                logIn("userList.csv", data, currentUser, isAuthenticated);
                cout << isAuthenticated << endl;
                cout << currentUser.currentUser.username << endl;
                //login works-ish
                if(isAuthenticated){
                    cout << "Please select one: " << endl;
                    cout << "a. Create\nb. Review\nc. Quiz\nd. Logout" << endl;
                    cout << "-> ";
                    cin >> userInput;
                    if (userInput == 'a') {
                        cout << "Create." << endl;
                    } else if(userInput == 'b'){
                        cout << "Review." << endl;
                    } else if (userInput == 'c'){
                        cout << "Quiz." << endl;
                    } else if (userInput == 'd'){
                        cout << "Logout." << endl;
                        isAuthenticated = false;
                    }
                }
            } else if( userInput == 'b') {
                cout << "Creating account..." << endl;
                createAccount("userList.csv", data, currentUser);
            } else if( userInput == 'c') {
                cout << "Exiting..." << endl;
                running = false;
            } else if (userInput == 'd') { //just to view current users from .csv file
                displayUsers("userList.csv", data);
            } else {
                cout << "Invalid input" << endl;
            }
        }
    }
    
    cout << "youhoo 👋" << endl;
    return 0;
}
