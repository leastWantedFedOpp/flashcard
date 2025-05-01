#include <iostream>

#ifndef createFile_hpp
#define createFile_hpp
#include "userAuth.hpp" //for User struct
#include <stdio.h>

struct File{
    string fileName;
    string privacy;
};

bool fileExist(string, fstream&, int , string);

void Create(User&);

#endif /* createFile_hpp */
