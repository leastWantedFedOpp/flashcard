#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

#include "utils/userAuth.hpp"
#include "utils/createFile.hpp"
#include "utils/reviewNquiz.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    char userInput2 = '\0';
    bool isAuthenticated = false;
    bool running = true;
    User currentUser = {0,""}; //id set to 0, username set to empty string
    
    cout << "Current working directory: " << filesystem::current_path() << endl;
    fstream data;

//  to reset
//    data.open("userFiles.csv", ios::out);
//    if(data.is_open()){
//        data << "Author Id, Author Name, Note, Privacy Setting\n";;
//        data.close();
//        cout << "Successfully Created :)" << endl;
//    }

    while (running) {
        cout << "FlashCard" << endl;
        while (userInput != 'c') {
            cout << "a. Login\nb. Create an account\nc. Exit\nd. Display UserList\ne. Display UserFiles" << endl;
            cout << "-> ";
            cin >> userInput;
            
            if (userInput == 'a') {
                cout << "Logging in..." << endl;
                logIn("userList.csv", data, currentUser, isAuthenticated);
                cout << isAuthenticated << endl;
                cout << currentUser.username << endl;
                //login works-ish
                while (isAuthenticated){
                    cout << "Please select one: " << endl;
                    cout << "a. Create\nb. Review\nc. Quiz\nd. Display files\ne. Logout" << endl;
                    cout << "-> ";
                    cin >> userInput2;
                    if (userInput2 == 'a') {
                        Create(currentUser);
                    } else if(userInput2 == 'b'){
                        review(currentUser);
                    } else if (userInput2 == 'c'){
                        quiz(currentUser);
                    } else if (userInput2 == 'd'){
//                        cout << "Display file list." << endl;
                        displayFileList("userFiles.csv", currentUser);
                    } else if (userInput2 == 'e'){
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
            } else if (userInput == 'e') {
                displayFileList("userFiles.csv", currentUser);
            } else {
                cout << "Invalid input" << endl;
            }
        }
    }
    
    cout << "youhoo 👋" << endl;
    return 0;
}

/*
 manage file/folder
 |_data
    |_.csv
    |_.txt
 |_utils
 |_main.cpp and others
 */

/*
 work on:
    - validate fileName? (if there are spaces - ask user to type again etc.)
 
    - fixing fileExist()
    - privacy setting (userinput == "public" || "private")
    - while loop for q n a
 
    Review branch
    - display file name, use similar function to fileExist()
        - display file name but filter based on user
 
    for all function
        - remove data from paramater and just call fstream again to avoid issues
 */
