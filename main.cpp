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
    
    filesystem::path root = filesystem::path(__FILE__).parent_path();
    cout << root << endl;
    filesystem::path userFiles = root / "userInfo" / "userFiles.csv"; //list of files that belong to users
    filesystem::path userList = root / "userInfo" / "userList.csv"; //list of users

    filesystem::path userData = root / "userData"; //throw all users .txt fils here.

//    data.open(userList, ios::out);
//    if(data.is_open()){
//        data << "Id, Username, Password\n";;
//        data.close();
//    } else {
//        cout << "Trouble opening file :(" << endl;
//    }
    
//    data.open(userFiles, ios::out);
//    if(data.is_open()){
//        data << "Author Id, Author Name, Note, Privacy Setting\n";;
//        data.close();
//    } else {
//        cout << "Trouble opening file :(" << endl;
//    }
    
    while (running) {
        cout << "FlashCard" << endl;
        while (userInput != 'c') {
            cout << "a. Login\nb. Create an account\nc. Exit\nd. display users" << endl;
            cout << "-> ";
            cin >> userInput;
            
            switch (userInput) {
                case 'a':
                    logIn(userList, currentUser, isAuthenticated);
                    while (isAuthenticated){
                        cout << "Hello, " << currentUser.username << endl;
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
                            displayFileList(userFiles, currentUser);
                        } else if (userInput2 == 'e'){
                            cout << "Logging out..." << endl;
                            currentUser = {0,""};
                            isAuthenticated = false;
                        }
                    }
                    break;
                case 'b':
                    createAccount(userList, currentUser);
                    break;
                case 'c':
                    cout << "Exiting..." << endl;
                    running = false;
                    break;
                case 'd':
                    displayUsers(userList);
                    break;
                default:
                    cout << "Invalid input" << endl;
                    break;
            }
        }
    }
    cout << "Bye 👋" << endl;
    return 0;
}

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
