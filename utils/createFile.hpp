#ifndef createFile_hpp
#define createFile_hpp
#include "userAuth.hpp" //for User struct
#include "path.h"
#include <stdio.h>

struct File{
    string fileName;
    string privacy;
};

bool fileExist(filesystem::path , string, bool, int);

void Create(User&);

#endif /* createFile_hpp */
