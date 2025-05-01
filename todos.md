# Todos

## the workflow? 😵‍💫

1. welcome 👋 login or create an account <mark>✅ works enough 💀</mark>
    - open file with user list stored
    1. login
        - username, password
        when user enter a username, it'll look for in file
        - if(username != exisitingUsername)
            try again or go back
          if (password != exsitingUserPassword ) {
            try again or go back
          }(authenticated ✅)
    2. create account
        - userId(auto gen), username, password
        - if(username == existingUsername)
            try again or go back
          else(store username and password in file, authenticated ✅)
2. display options:
    1. create 📝 <mark>✅ works enough 💀</mark>
        - fileName, privacy setting(public/private)
        - author/username, authorid/userId will automatically be assigned based on who's logged in
        - open a <cardName>.txt file
        - write
        - close
    2. review 📖 <mark>🌀 in progress</mark>
        - myNotes
            - display all file under user database
            - user will select notes based on name
            - output file
        - publicNotes
            - display all notes from database w/privacy setting set as public
            - user will select notes based on name
            - output file
        - *Issue: file with same name? I could have user rename file if file already exist OR have user type filename and the author it belongs to 
    3. quiz ❓
        - myNotes
            - display all file under user database
            - user will select notes based on name
            - . . .
                - begin quiz + grade = 0;
                    - dispaly question
                    - user will input answer based on that question and submit
                    - display the answer
                    - ask user if they got it right (grade += 1) or wrong 
                    - display grade at end, send them back
        - publicNotes
    4. delete ❌
    5. update 🙃

## so far
- login and create account :)
- create and review :)


## things to work on
- review and quiz 
    - when users select, ask for public or private, display based on input
    - function that displays all public userFiles ( displayFiles() )
        - function that display userFiles that belongs to logged in user
