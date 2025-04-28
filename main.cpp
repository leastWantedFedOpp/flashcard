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

struct Card{
    string question;
    string answer;
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
    string fileName; //for struct
    string privacy;
    string question, answer; //for QnA to append inside a text file
    fstream data;
    
    cout << "Create." << endl;
    cout << "Name of file: ";
    cin >> fileName;
    
//    if(fileExist("userFiles.csv", data, currentUser.id, currentUser.username, fileName)){
//        cout << "you're gud. continue 😘" << endl;
//    } else {
//        cout << "file already exist, try again 🙃" << endl;
//    }
    
    cout << "Privacy setting:\na. public\nb. private " << endl;
//    while (privacy != 'a' || privacy != 'b') {
        cout <<  "-> ";
        cin >> privacy;
//    };
    
    //append file name
    data.open("userFiles.csv", ios::out | ios::app);
     
     if(data.is_open()){
         data << to_string(currentUser.id) + "," + currentUser.username + "," + (fileName + ".txt")+ "," + (privacy == "a" ? privacy = "public" : privacy = "private") + "\n";
         cout << "File successfully added :)" << endl;
     data.close();
     } else {
         cout << "Trouble opening file :(" << endl;
     }
    
    //store inside its own function 🥹?
    //create file
     data.open((fileName + ".txt"), ios::out | ios::app);
    if(data.is_open()){
        char userInput = '\0';
        while (userInput != 'e'){
            cin.ignore();
            int count = 1;
//            cout << "Question " + to_string(count)  + ": ";
//            getline(cin, question);
//            data << question << "\n";
//            cout << "Answer: " + to_string(count)  + ": ";
//            getline(cin, answer);
//            data << answer << "\n";
            cout << "Question " + to_string(count)  + ": ";
            getline(cin, question);
            data <<  "{?" << question << "?}";
            cout << "Answer: " + to_string(count)  + ": ";
            getline(cin, answer);
            data << "[-" << answer << "-]";
            cout << "Type 'c' to continue or 'e' to exit" << endl;
            cout << "-> ";
            cin >> userInput;
            if(userInput == 'e') {
                cout << "Total cards created: " << (count == 1 ? count = 1: count - 1) << endl;
            }
            count++;
    }
    
        cout << (fileName + ".txt") << " successfully created" << endl;
     data.close();
     }
}

void review(){
    string reviewFileName;
    cout << "Name the file you would like to review: ";
    cout << "-> ";
    cin >> reviewFileName;
    
    fstream data;
    data.open(reviewFileName, ios::in);
    if(data.is_open()){
        /*
         read file, get len of file, start disecting, input info inside the struct, then vector, repeat till the end of file.
         */
    } else {
        cout << "Trouble opening file :(" << endl;
    }
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
 
 */

 //alternative to writing question and answer into txt file
 //explanation:
 /*
  might have to remove '\n\' after data << question << '\n' (same from answer)
  the plan now:
  first wrap question with '[?' and '?]'
  qStartingPoint and qEndingPoint
  
  wrap answer with '{-' and '-}'
  aStartingPoint and aEndingPoint
  
  card 1;
  initial starting point will be from 0
  end at the answer ending point aEndingPoint;
  
  card2:
  starting point will be from prev answer ending point (aEndingPoint + 1) //using substr till the end of the text file
  
  end of the text file means i have to count char of text
  
  use substring to extract the info btwn each
  store question and answer inside a struct inside vector
  
  
  read the entire fil
 */

/*
 
 string question = "[?Is this a questions??]"; //len = 24
 string answer = "{-Thi is the answer, i think.-}";
 int startPoint = unsigned( question.find("[?") ) + 2;
 int endPoint = unsigned( question.find("?]") - 2 );
 cout << question.find("[?") << endl;
 cout << question.find("?]") << endl;

 cout << "Starting point (index) : " << startPoint << endl;
 cout << "End point (index) : " << endPoint << endl;
 
 cout << question << endl;
 cout << question.substr(startPoint, endPoint) << endl;
 
 */
