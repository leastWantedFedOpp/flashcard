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

//does not work, file opens but does not read
//first just have it display fileName and their author ;)
void displayFileList(string filename, User& currentUser){ //"userFiles.csv" , currentUser, userInput
    fstream data(filename, ios::in);
    char userInput = '\0';
    cout << "a. My notes\nb. All notes" << endl; //when user select all nots first display their notes then All notes. if usere select my notes only display thri notes;
    do {
        cout << "-> ";
        cin >> userInput;
        
        if(userInput != 'a' && userInput != 'b'){
            cout << "Invalid input! Type 'a' to view your notes or 'b' to view all notes" << endl;
        }
    } while (userInput != 'a' && userInput != 'b');
    
    if(data.is_open()){
        vector<string> myFiles;
        vector<string> publicFiles;
        string line;
        getline(data, line);
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
             //users will be authenticated
            
            if(user.id == currentUser.id){
                myFiles.push_back(displayFile.fileName);
            } else if(displayFile.privacy == "public"){
                publicFiles.push_back(displayFile.fileName + " - " + user.username);
            }
        }
        
        
        //display here
        if (userInput == 'a') {
            cout << "My Notes" << endl;
            cout << "* * *" << endl;
            for (const auto& file:myFiles) {
                cout << file << " - " << currentUser.username << endl;
            }
            cout << "- - -" << endl;
        } else if (userInput == 'b') {
            cout << "My Notes" << endl;
            cout << "* * *" << endl;
            for (const auto& file:myFiles) {
                cout << file << " - " << currentUser.username << endl;
            }
            
            cout << "- - -" << endl;
            
            cout << "Public Notes" << endl;
            cout << "* * *" << endl;
            for (const auto& file:publicFiles) {
                cout << file << endl;
            }
            cout << "- - -" << endl;
        }
        data.close();
    } else {
        cout << "Unable to open file :(" << endl;
    }
}

//void createSet(){
//    
//}

void review(User& currentUser){
    string reviewFileName;
    vector<map<int,Card>> mySet; //list of map
    map<int,Card> cardMap; //map with int, and card struct
    Card myCard; //card struct w/question n answer
    
    cout << "+*+ Review +*+" << endl;
    displayFileList("userFiles.csv", currentUser);
    cout << "Type the name of file you want to review from" << endl;
    cout << "-> ";
    cin >> reviewFileName;
    
//    fileExist("userFiles.csv", currentUser.id, reviewFileName); //check if reviewFileName exist
    
    cout << "Opening " << (reviewFileName + ".txt") << endl;
    fstream data;
    data.open((reviewFileName + ".txt"), ios::in);
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
    cout << "~ ~ ~ ~ ~ ~ " << endl;
    for (const auto& cardmap:mySet) { //for loop for a vector that holds map
        for (const auto& card:cardmap) { //for loop for map that holds key(int) and value(question, answer)
            cout << "Question " << card.first << " : " << card.second.question << endl;
            cout << "Answer: " << card.second.answer << endl;
            cout << "~ ~ ~ ~ ~ ~ " << endl;

        }
    }
    
}


void quiz(User& currentUser){
    string quizFileName;
    string userAnswer;
    char selfGrade = '\0';
    int scoreCount = 0;
    
    vector<map<int,Card>> mySet; //list of map
    map<int,Card> cardMap; //map with int, and card struct
    Card myCard; //card struct w/question n answer
    
    cout << "+*+ Quiz +*+" << endl;
    displayFileList("userFiles.csv", currentUser);
    cout << "Type the name of file you want to quiz from" << endl;
    cout << "-> ";
    cin >> quizFileName;
    
    //make this a func ->
    fileExist("userFiles.csv", currentUser.id, quizFileName);
//    cout << "Opening " << (quizFileName + ".txt") << endl;
    fstream data;
    data.open((quizFileName + ".txt"), ios::in);
    if(data.is_open()){
        string line;
        string line2;
        int lineNo = 1;
        while(!data.eof()){
            getline(data, line);
            getline(data, line2);
            myCard.question = line;
            myCard.answer = line2;
            cardMap.insert(make_pair(lineNo, Card{myCard.question, myCard.answer}));
            mySet.push_back(cardMap);
            cardMap.clear();
            lineNo++;
        }
    } else {
        cout << "Trouble opening file :(" << endl;
    }
    // <-
    
    cout << "\nYour answers are graded based on an honor system.\nAfter you type in your answer. The program will display the correct answer.\nYou'll be asked to compare your answer with the correct answer.\n" <<  endl;
    cout << "Do your best. Good luck!\n" << endl;
    for (const auto& cardmap:mySet) {
        for (const auto& card:cardmap) {
            cout << "~ ~ ~ ~ ~ ~ " << endl;
            cout << "Question " << card.first << " : " << card.second.question << endl;
            cout << "Your answer: ";
            cin.ignore();
            getline(cin, userAnswer);
            cout << "~ ~ ~ ~ ~ ~ " << endl;
            cout << "Correct answer: " << card.second.answer << endl;
            cout << "Did you get it right? (y)yes | (n)no" << endl;
            do {
                cout << "-> ";
                cin >> selfGrade;
            } while (selfGrade != 'y' && selfGrade != 'n');
           
            if(selfGrade == 'y'){
                scoreCount++;
            }
        }
    }
    cout << "+ + +" << endl;
    cout << "You scored " << scoreCount << " / " << mySet.size() << endl;
    cout << "+ + +" << endl;
}


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

/*
 prefered result:
 for 'a':
     My Notes
        - display myNote1
        - display myNote3
        - display myNote3
 
 for 'b':
     My Notes
        - display myNote1
        - display myNote3
        - display myNote3
 
     All Notes
        - display publicNote1
        - display publicNote2
        - display publicNote3
 ===
 
 //first display logged in user note, then display rest of the notes
 //do i store all notes in vector and filter later?
 //or
 //create 2 vecotor?
    - i can create 2 vector called myNotes and allNote
    - myNote vector, if(user.id == currentUser.id) - push file in myNote vector
    - allNote vector, push rest of the files
 */
