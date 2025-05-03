#ifndef reviewNquiz_hpp
#define reviewNquiz_hpp

#include "userAuth.hpp"
#include "path.h"

#include <stdio.h>

struct Card{
    std::string question;
    std::string answer;
};

vector<map<int,Card>> createSet(string&);

void displayFileList(string , User& );

void review(User& );

void quiz(User& );


#endif /* reviewNquiz_hpp */
