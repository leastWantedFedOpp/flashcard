#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

#include "utils/userAuth.hpp"
#include "utils/createFile.hpp"

using namespace std;

struct Card{
    string question;
    string answer;
};

//note

void review(){
    string reviewFileName = "mikey01.txt";
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

/*
 review
 |_ask my file or all file
    |_displayFileList based on input
        |_review
 
 quiz
 |_ask my file or all file
    |_displayFileList based on input
        |_quiz
 */

void quiz(){
    /*
     if(userInput == 'a'){
        displayFiles() //display notes that belong to users
     } else {
        displauFiles() //display all notes that has privacySetting set to public
     }
     */
}

//does not work, file opens but does not read
//first just have it display fileName and their author ;)
void displayFileList(string filename, fstream& data){ //"userFiles.csv"
    data.open(filename, ios::in);
    if(data.is_open()){
        string line;
        getline(data, line);
        //goes up to here but does not run while loop?
        cout << "I am here and I have access to " << filename << " file" << endl;
        while(getline(data, line, ',')){
            if(line.empty()) continue;

            User user;
            File displayFile;
            
            user.id = stoi(line); //author id
            getline(data, line, ',');
            user.username = line; //author name
            getline(data, line, ',');
            displayFile.fileName = line; //filename
            getline(data, line);
            displayFile.privacy = line; //privacy
            
            cout << displayFile.fileName << " - " << user.username << endl;

        }
        data.close();
    } else {
        cout << "Unable to open file :(" << endl;
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
            cout << "a. Login\nb. Create an account\nc. Exit\nd. Display UserList\ne. Display UserFiles" << endl;
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
                    cout << "a. Create\nb. Review\nc. Quiz\nd. Display files\ne. Logout" << endl;
                    cout << "-> ";
                    cin >> userInput;
                    if (userInput == 'a') {
                        Create(currentUser);
                    } else if(userInput == 'b'){
                        review();
                    } else if (userInput == 'c'){
                        cout << "Quiz." << endl;
                    } else if (userInput == 'd'){
//                        cout << "Display file list." << endl;
                        displayFileList("userFiles.csv", data);
                    } else if (userInput == 'e'){
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
                displayFileList("userFiles.csv", data);
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
