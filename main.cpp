#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

//.h or .hpp files
#include "utils/path.hpp"
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
    
    fstream data(userList, ios::out);
    cout << userList << " cant open?" << endl;
    if(data.is_open()){
        data << "Id, Username, Password\n";;
        data.close();
    } else {
        cout << "Trouble opening file :(" << endl;
    }
    
//    fstream data(userFiles, ios::out);
//    if(data.is_open()){
//        data << "Author Id, Author Name, Note, Privacy Setting\n";;
//        data.close();
//    } else {
//        cout << "Trouble opening file :(" << endl;
//    }
//    
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
                        
                        switch (userInput2) {
                            case 'a':
                                Create(currentUser);
                                break;
                            case 'b':
                                review(currentUser);
                                break;
                            case 'c':
                                quiz(currentUser);
                                break;
                            case 'd':
                                displayFileList(userFiles, currentUser);
                                break;
                            case 'e':
                                cout << "Logging out..." << endl;
                                currentUser = {0,""};
                                isAuthenticated = false;
                                break;
                            default:
                                cout << "Invalid Input" << endl;
                                break;
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
