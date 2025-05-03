#ifndef path_h
#define path_h

filesystem::path root = filesystem::path(__FILE__).parent_path();
filesystem::path userFiles; //list of files that belong to users
filesystem::path userList; //list of users
filesystem::path userData; //throw all users .txt fils here.

#endif /* path_h */
