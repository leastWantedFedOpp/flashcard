#include <iostream>
#include <filesystem>

#include "path.hpp"

std::filesystem::path root = std::filesystem::path(__FILE__).parent_path();
std::filesystem::path userFiles = root / "userInfo" / "userFiles.csv"; //list of files that belong to users
std::filesystem::path userList = root / "userInfo" / "userList.csv"; //list of users
std::filesystem::path userData = root / "userData"; //throw all users .txt fils here.
