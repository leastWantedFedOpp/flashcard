#include <iostream>
#include <fstream>
#include "createFile.hpp"

//this currenly check when user tries to create a file, see if file already exist under same user
//have this also just check if file exist
bool fileExist(string filename, string checkFileName, bool forCreate  ,int checkId ){
    fstream data(filename, ios::in);
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
            
            //the purpose of this is to check if the currentUser already has a file named x to avoid duplication
            
            //check is user exist and if the fileName currently readin matches with checkFileName is same line :P
            if(forCreate){
                if(authorId == checkId && viewFile.fileName == (checkFileName + ".txt")){
                    data.close();
                    return true;
                }
            } else {
                if(viewFile.fileName == (checkFileName + ".txt")){
                    data.close();
                    return true;
                }
            }
        
        }
    } else {
        cout << "Unable to open file :(" << endl;
    }
    return false;
}


void Create(User& currentUser){
    string fileName; //for structa
    string privacy;
    string question, answer; //for QnA to append inside a text file
    bool thisFileExist;
    
    fstream data;
    
    cout << "Create." << endl;
    
    do {
        cout << "Name of file: ";
        cin >> fileName;
        thisFileExist = fileExist("userFiles.csv",  fileName, true, currentUser.id);
        
        if(thisFileExist){ //true
            cout << fileName << " already exist. Try again!" << endl;
        }
    } while (thisFileExist);
    
    cout << "Privacy setting:\na. public\nb. private " << endl;
    do {
        cout <<  "-> ";
        cin >> privacy;
        
        if (privacy != "a" && privacy != "b") {
            cout << "Invalid input! Type 'a' for public or 'b' for private" << endl;
        }
        
    } while (privacy != "a" && privacy != "b");
    
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
        int count = 1;
        while (userInput != 'e'){
            cin.ignore();
            cout << "Question " + to_string(count)  + ": ";
            getline(cin, question);
            data << question << "\n";
            cout << "Answer: " + to_string(count)  + ": ";
            getline(cin, answer);
            data << answer; //removed "\n" incase user decide to exit :(
            do {
                cout << "Type 'c' to continue or 'e' to exit" << endl;
                cout << "-> ";
                cin >> userInput;
                
                if (userInput != 'e' && userInput != 'c') {
                    cout << "Invalid input! ";
                }
                
            } while (userInput != 'e' && userInput != 'c');
            
            if(userInput == 'e') {
                cout << "Total cards created: " << count << endl;
            } else { //if user doest exit, create a new line for user too add info on ;)
                data << "\n";
                count++;
            }
    }
    
    cout << (fileName + ".txt") << " successfully created" << endl;
     data.close();
     }
}
