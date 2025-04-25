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
    UserTemplate user;
    string password;
};

struct CurrentUser{ //for when user is found from db
    UserTemplate currentUser; //id, username
    bool isAuthenticated; //if authenticated == true has access :) if not no access :(
};

int genUserid(){
    srand(unsigned(time(0)));
    int randGenUserId = rand() % 9000 + 1000;
    return randGenUserId;
}

void userExist(){
    
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
    User newUser = {{id, username}, password}; //new user is created
    if(data.is_open()){
        data << to_string(newUser.user.id) + "," + newUser.user.username + "," + newUser.password + "\n"; //add new user info inside userList.csv
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


void authUser(){
    //open a file called userList.csv
    //read
    char userInput = '\0';
    bool isAuthenticated = false;
//    string usersFileName = "userList.csv";
    
    fstream data;
    data.open("userList.csv", ios::out | ios::app); //open file
    
//    if(data.is_open()){
//        data << "UserId, UserName, Password" << endl;
//        data.close();
//    }
    
    cout << "a. Login\nb. Create an account\nc. Exit" << endl;
    cout << "-> ";
    cin >> userInput;
    
    switch (userInput) {
        case 'a':
            logIn(); //pass csv file
            break;
        case 'b':
            createAccount("userList.csv", data); //pass csv file
            break;
        case 'c':
            cout << "Exit" << endl;
            break;
        default:
            cout << "Invalid Input >:(" << endl;
            break;
    }
}

int main(int argc, const char * argv[]) {
    char userInput = '\0';
    bool isAuthenticated = false;
    CurrentUser currentUser;
    
    cout << "Current working directory: " << filesystem::current_path() << endl;
    cout << "FlashCard" << endl;
    do {
        cout << "a. Login\nb. Create an account\nc. Exit" << endl;
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
            cout << "auth will return bool" << endl;
            cout << "auth() then access to create, review, quiz" << endl;
        } else if( userInput == 'b') {
            cout << "Creating an account..." << endl;
            cout << "some function and break" << endl;
        } else if( userInput == 'c') {
            cout << "Exiting..." << endl;
        }
    } while (userInput != 'c' || isAuthenticated);
    
    if(!isAuthenticated){
        cout << "Please select one: " << endl;
        cout << "a. Create\nb. Review\nc.\ncQuiz";
        cout << "-> ";
        cin >> userInput;
    }
        
    return 0;
}


//Breaking it down
/*
 plan a
 main func
    |_ auth func
        |_log func that return bool isUserLoggedIn ? authenticated == true : cout << "try again or create account";
        |_createAcc func - after user create account, they'll be redirected to auth func, where they'll have to log in, creating account != authenticated
 */

/*
 plan b
 first run auth()
    - users log in, if users dont have account, create accout, then log in
    - the information of user that logged in is save in a currentUser struct
    - exit auth funct
 */

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
