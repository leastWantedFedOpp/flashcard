#include <iostream>

#ifndef createFile_hpp
#define createFile_hpp
#include "userAuth.hpp" //for User struct
#include <stdio.h>

struct File{
    string fileName;
    string privacy;
};

bool fileExist(string , string, bool, int);

void Create(User&);

#endif /* createFile_hpp */
