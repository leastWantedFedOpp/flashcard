#include <iostream>
#include <fstream>
#include <map>
#include "reviewNquiz.hpp"
#include "userAuth.hpp"
#include "createFile.hpp"
#include "path.h"

using namespace std;
 
vector<map<int,Card>> createSet(string& filename){
     vector<map<int,Card>> mySet; //list of map
     map<int,Card> cardMap; //map with int, and card struct
     Card myCard; //card struct w/question n answer
     
    fstream data((filename + ".txt"), ios::in);
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
    return mySet;
}

void displayFileList(filesystem::path filename, User& currentUser){
    fstream data(filename, ios::in);
    char userInput = '\0';
    cout << "a. My notes\nb. All notes" << endl;
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
            
            if(user.id == currentUser.id){
                myFiles.push_back(displayFile.fileName);
            } else if(displayFile.privacy == "public"){
                publicFiles.push_back(displayFile.fileName + " - " + user.username);
            }
        }
        
        if (userInput == 'a') {
            cout << "My Notes" << endl;
            cout << "* * *" << endl;
            
            if (myFiles.empty()) {
                cout << "no files created" << endl;
            } else {
                for (const auto& file:myFiles) {
                    cout << file << " - " << currentUser.username << endl;
                }
            }
            cout << "- - -" << endl;
        } else if (userInput == 'b') {
            cout << "My Notes" << endl;
            cout << "* * *" << endl;
            if (myFiles.empty()) {
                cout << "no files created" << endl;
            } else {
                for (const auto& file:myFiles) {
                    cout << file << " - " << currentUser.username << endl;
                }
            }
            cout << "- - -" << endl;
            cout << "Public Notes" << endl;
            cout << "* * *" << endl;
            
            if (publicFiles.empty()) {
                cout << "no public files found" << endl;
            } else {
                for (const auto& file:publicFiles) {
                    cout << file << endl;
                }
            }
            cout << "- - -" << endl;
        }
        data.close();
    } else {
        cout << "Unable to open file :(" << endl;
    }
}

void review(User& currentUser){
    string reviewFileName;
    bool thisFileExist;
    vector<map<int,Card>> mySet;
    
    cout << "+*+ Review +*+" << endl;
    displayFileList(userFiles, currentUser);
    cout << "Type the name of file you want to review from" << endl;
    
    do {
        cout << "-> ";
        cin >> reviewFileName;
        thisFileExist = fileExist(userFiles, reviewFileName, false,  currentUser.id);
        
        if(!thisFileExist){ //true
            cout << reviewFileName << " does not exist. Try again!" << endl;
        }
    } while (!thisFileExist);
        
    cout << "Opening " << (reviewFileName + ".txt") << endl;
    
    mySet = createSet(reviewFileName);
    
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
    bool thisFileExist;
    
    vector<map<int,Card>> mySet; //list of map
    
    cout << "+*+ Quiz +*+" << endl;
    displayFileList(userFiles, currentUser);
    cout << "Type the name of file you want to quiz from" << endl;
    
    do {
        cout << "-> ";
        cin >> quizFileName;
        thisFileExist = fileExist(userFiles, quizFileName, false,  currentUser.id);
        
        if(!thisFileExist){ //true
            cout << quizFileName << " does not exist. Try again!" << endl;
        }
    } while (!thisFileExist);
    
    fileExist(userFiles, quizFileName, false,  currentUser.id);
    cout << "Opening " << (quizFileName + ".txt") << endl;
    mySet = createSet(quizFileName);
    
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
