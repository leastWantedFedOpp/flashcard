#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "utils/userAuth.hpp"

using namespace std;

struct File{
    string fileName;
    string privacy; //true or false?
};

 //pass userFiles.csv
 bool fileExist(string filename, fstream& data, int checkId, string checkUsername, string checkFileName){
     data.open(filename, ios::in);
     if(data.is_open()){
         string line;
         getline(data, line);
    //        cout << line <<  "\n";
         while(getline(data, line, ',')){
             if(line.empty()) continue;
             File viewFile;
             int authorId = stoi(line); //author id
             getline(data, line, ',');
             string authorName = line; //author name
             getline(data, line, ',');
             viewFile.fileName = line; //filename
             getline(data, line);
             viewFile.privacy = line; //privacy
             
             if(authorId == checkId && authorName == checkUsername) {
                 if(viewFile.fileName == filename){
                     return true; //yes it does exist
                 } else {
                     return false;
                 }
             }
         }
         data.close();
     } else {
         cout << "Unable to open file :(" << endl;
     }
     return false;
 }

void Create(User& currentUser){
//    User author;
    string fileName, privacy;
    fstream data;
    
    cout << "Create." << endl;
    cout << "Name of file: ";
    cin >> fileName;
    //check if a filename alerady exist user under the current user
    
//    if(fileExist("userFiles.csv", data, currentUser.id, currentUser.username, fileName)){
//        cout << "you're gud. continue 😘" << endl;
//    } else {
//        cout << "file already exist, try again 🙃" << endl;
//    }
    
    cout << "Privacy setting (public/private): ";
    cin >> privacy;
    
    data.open("userFiles.csv", ios::out | ios::app);
     
     if(data.is_open()){
         data << to_string(currentUser.id) + "," + currentUser.username + "," + (fileName + ".txt")+ "," + privacy + "\n";
         cout << "File successfully added :)" << endl;
     data.close();
     } else {
         cout << "Trouble opening file :(" << endl;
     }
    
    /*
     fstream data;
     data.open(fileName + ".txt", ios::out | ios::app);
     
     if(data.is_open()){
     //while loop
     cout << "Question" << endl;
     data << question << "\n";
     cout << "Answer" << endl;
     data << answer << "\n";
     if user types ceratin character, break loop
     cout << "Successfully created" << endl;
     data.close();
     }
     
     
     }
     */
     /*
     first create existing file called userFiles.csv
     
     struct File{
     int id; //from currentUser
     string author; //from currentUser
     string name;
     string privacy; //private or public
     }
     
     create() - workflow
     |_currentUser
     data << "userId (AuthorId), username(Author), FileName, Pivacy Setting << endl;
     //set info for file
     |_create a txt file based on file name user inputted
     |_write on file
     |_question: *user types question* + '\n' // set char limit?
     |_answer: *user types answer* + '\n' // set char limit?
     |_data << qustion << '\n' << answer;
     |_if user types 'x' << cancel;
     
     
     
     */
}

int main(int argc, const char * argv[]) {
    char userInput = '\0';
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
            cout << "a. Login\nb. Create an account\nc. Exit\nd. Display UserList" << endl;
            cout << "-> ";
            cin >> userInput;
            
            if (userInput == 'a') {
                cout << "Logging in..." << endl;
                logIn("userList.csv", data, currentUser, isAuthenticated);
                cout << isAuthenticated << endl;
                cout << currentUser.username << endl;
                //login works-ish
                if(isAuthenticated){
                    cout << "Please select one: " << endl;
                    cout << "a. Create\nb. Review\nc. Quiz\nd. Logout" << endl;
                    cout << "-> ";
                    cin >> userInput;
                    if (userInput == 'a') {
                        cout << "Create." << endl;
                        Create(currentUser);
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
