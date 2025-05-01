#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "userAuth.hpp"

using namespace std;

int genUserId(){
    srand(unsigned(time(0)));
    int randGenUserId = rand() % 9000 + 1000;
    return randGenUserId;
}

void displayUsers(string filename, fstream& data){
    data.open(filename, ios::in);
    if(data.is_open()){
        string line;
        getline(data, line);
        cout << line <<  "\n";
        while(getline(data, line, ',')){
            if(line.empty()) continue;
            UserAuth user;
            user.user.id = stoi(line);
            getline(data, line, ',');
            user.user.username = line;
            getline(data, line);
            user.password = line;
            cout << user.user.id << " " << user.user.username << " " << user.password << endl;
        }
        data.close();
    } else {
        cout << "Unable to open file :(" << endl;
    }
}

bool userExist(string filename, fstream& data, string nameInput, string passwordInput, User& currentUser, bool login){
    data.open(filename, ios::in);
    if(data.is_open()){
        string line;
        getline(data, line);
//        cout << line <<  "\n";
        while(getline(data, line, ',')){
            if(line.empty()) continue;
            UserAuth user;
            user.user.id = stoi(line);
            getline(data, line, ',');
            user.user.username = line;
            getline(data, line);
            user.password = line;
            
            //check if user exist
            if(user.user.username == nameInput){ //user exist
                if(login){ //if users is trying to log in
                    if(user.password == passwordInput){ //compare if password matches with username
                        currentUser.id = user.user.id;
                        currentUser.username = user.user.username;
                        return true;
                    } else {
                        return false;
                    }
                }
                return true;
            }
        }
        data.close();
    } else {
        cout << "Unable to open file :(" << endl;
    }
    return false;
}

void logIn(string filename, fstream& data, User& currentUser, bool& isAuthenticated){
    string username, password;
    cout << "Log in" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if(!userExist(filename, data, username, password, currentUser , true)){
        cout << "Unable to Log in. Please try again." << endl;
    } else {
        isAuthenticated = true;
        cout << "Log in successfull" << endl;
    }
}

void createAccount(string filename, fstream& data, User& currentUser){
    int id;
    string username, password;
            
    cout << "Create an account" << endl;
    id = genUserId();
    cout << "Username: ";
    cin >> username;
    
    if(!userExist(filename, data, username, "", currentUser, false)){ //if user exist, userExist() return true
        data.open(filename, ios::out | ios::app); //open file to append

        cout << "Password: ";
        cin >> password; //create password
        UserAuth newUser = {{id, username}, password}; //new user is created
        if(data.is_open()){ //open data
            data << to_string(newUser.user.id) + "," + newUser.user.username + "," + newUser.password + "\n";//add new user info inside userList.csv
            cout << "User successfully created" << endl;
            data.close(); //close file
        } else {
            cout << "Unable to open file :(" << endl;
        }
    } else {
        cout << "User already exist :(" << endl;
    }
}
