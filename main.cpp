#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct UserTemplate{
    int id;
    string username;
};

struct User{ //for creating newUser and foundUser
    UserTemplate user; //id, username
    string password;
};

//remove currentUser struct and use one of other struct?
struct CurrentUser{ //for when user is found from db
    UserTemplate currentUser; //id, username
//    bool isAuthenticated; //if authenticated == true has access :) if not no access :(
};

int genUserid(){
    srand(unsigned(time(0)));
    int randGenUserId = rand() % 9000 + 1000;
    return randGenUserId;
}

/*
userExist function is going to be used to assign currentUser (login) and see if users exist (signup)
|_ for login
    - takes userName - if username already exist, check password that's attatched to username, if user input correct password then assign currentUser
|_ for signup
    - takes userName - if usernme already exist,tell user username aready exist and try again
 
add username, password and currentUser struct as additional argument?
ex. void userExist(string filename, fstream& data, string nameInput, string passwordInput, CurrentUser currentUser)
 - + nameInput - from login and signup - compare to see if username exist
 - + passwordInput - from login - compare to see if password match with username
 - + currentUser - assgin currentUser if user logs in successfully
*/

void userExist(string filename, fstream& data){
    data.open(filename, ios::in);
    if(data.is_open()){
        string line;
        getline(data, line);
        cout << line <<  "\n";
        while(getline(data, line, ',')){
            if(line.empty()) continue;
            User user;
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

void logIn(){
    string username, password;
    cout << "Log in" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    //look in userData.csv
    //if user is found then take that users info (id, name) and set it to CurrentUser?
    /*
    login
        |_username == foundUser.userName
            |_password == foundUser.password
                |_try again
                |_go back
            |_authenticated == true
                |_ if (authenticated)
                    |_struct CurrentUser(username.username, password.password)
                    |_CurrentUser currentUser = {id, username}
     */
}

void createAccount(string filename, fstream& data){
    int id;
    string username, password;
    
    data.open(filename, ios::out | ios::app); //open file to append
        
    cout << "Create an account" << endl;
    id = genUserid();
    cout << "Username: ";
    cin >> username;
    //check if username already exist here :/
    cout << "Password: ";
    cin >> password;
    User newUser = {id, username, password}; //new user is created
    if(data.is_open()){
        data << to_string(newUser.user.id) + "," + newUser.user.username + "," + newUser.password + "\n";//add new user info inside userList.csv
        cout << "User successfully created" << endl;
        data.close(); //close file
    } else {
        cout << "Unable to open file :(" << endl;
    }
    
    /*
    createAccount
        |_if username == foundUser.userName
            |_username already exist try again
        |_username = username;
        |_password = password;
        |_confirmation ('user created')
        |_send user back to login page
        |_break and run auth()
     */
}

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    bool isAuthenticated = false;
    CurrentUser currentUser;
    
    //file
    cout << "Current working directory: " << filesystem::current_path() << endl;
    fstream data;
    data.open("userList.csv", ios::out | ios::app); //open file
    
    cout << "FlashCard" << endl;
    while (userInput != 'c' ) {
        cout << "a. Login\nb. Create an account\nc. Exit\nd. Display UserList" << endl;
        cout << "-> ";
        cin >> userInput;
        
        if (userInput == 'a') {
            cout << "Logging in..." << endl;
            /*
             run auth();
                - pass currentUser struct (and isAuthenticated?) by reference
                - inside auth, if user is found, then fill currentUser data with id, userName and set isAuthenticated to true
                - exit
                - if (isAuthenticated == true) then exits the while loop
             */
            
        } else if( userInput == 'b') {
            cout << "Creating account..." << endl;
            createAccount("userList.csv", data);
        } else if( userInput == 'c') {
            cout << "Exiting..." << endl;
        } else if (userInput == 'd') { //just to view current users from .csv file
            userExist("userList.csv", data);
        } else {
            cout << "Invalid input" << endl;
        }
    }
    
    if(isAuthenticated){
        cout << "Please select one: " << endl;
        cout << "a. Create\nb. Review\nc.Quiz" << endl;
        cout << "-> ";
        cin >> userInput;
    }
        
    return 0;
}


//Breaking it down
/*
 plan c - current ✨
 in main function, program ask user to login, creat account, or exit
    |_if user logs in successfully then then authenticated = true
        |_contunue to a while loop that says as long as user is auth give acces, if user log out auth = false
    |_if user says create account, creat account, save info in list "user created", go back to log in page
    |_exit will exist :P
 */

/*
 //bool isAuthenticated = false;
 authUser(); //bool return true/false
    |_logIn();
    |_createAccount();
 
 if(authUser()){ //runs if user has logged in
    create();
    review();
    quiz();
 }
 */
