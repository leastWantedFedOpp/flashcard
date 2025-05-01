#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <utility>

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
    do {
        cout <<  "-> ";
        cin >> privacy;
    } while (privacy != "a" || privacy != "b");
    
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
            cout << "Question " + to_string(count)  + ": ";
            getline(cin, question);
            data << question << "\n";
            cout << "Answer: " + to_string(count)  + ": ";
            getline(cin, answer);
            data << answer; //removed "\n" incase user decide to exit :(
            cout << "Type 'c' to continue or 'e' to exit" << endl;
            cout << "-> ";
            cin >> userInput;
            if(userInput == 'e') {
                cout << "Total cards created: " << (count == 1 ? count = 1: count - 1) << endl;
            } else { //if user doest exit, create a new line for user too add info on ;)
                data << "\n";
            }
            count++;
    }
    
        cout << (fileName + ".txt") << " successfully created" << endl;
     data.close();
     }
}

void review(){
    string reviewFileName = "MikeyQNA.txt";
    vector<map<int,Card>> mySet; //list of map
    map<int,Card> cardMap; //map with int, and card struct
    Card myCard; //card struct w/question n answer
    
    cout << "File name " << reviewFileName << endl;
    
    fstream data;
    data.open(reviewFileName, ios::in);
    if(data.is_open()){
        string line;
        string line2;
        int lineNo = 1;
        while(!data.eof()){
            getline(data, line);
            getline(data, line2);
            myCard.question = line;
            myCard.answer = line2;
            
            cardMap.insert(make_pair(lineNo, Card{myCard.question, myCard.answer})); //create a map with pair of int and Card struct that holds question and answer
            mySet.push_back(cardMap); //add the card inse the vector
            cardMap.clear();
            lineNo++;
        }
    } else {
        cout << "Trouble opening file :(" << endl;
    }
    
    for (const auto& cardmap:mySet) { //for loop for a vector that holds map
        for (const auto& card:cardmap) { //for loop for map that holds key(int) and value(question, answer)
            cout << card.first << ". " << "Question: " << card.second.question << endl;
            cout << "Answer: " << card.second.answer << endl;
        }
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
                if(isAuthenticated){ //use a while loop dumbass
                    cout << "Please select one: " << endl;
                    cout << "a. Create\nb. Review\nc. Quiz\nd. Logout" << endl;
                    cout << "-> ";
                    cin >> userInput;
                    if (userInput == 'a') {
//                        Create(currentUser);
                    } else if(userInput == 'b'){
                        cout << "Review." << endl;
                        review();
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
