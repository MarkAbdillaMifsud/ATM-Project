#pragma once
#include <unordered_map>
#include "User.h"

class FileHandler{
    public:
        static void loadFromCSV(std::unordered_map<std::string, User> &users, const std::string &filename);
        static void saveToCSV(const std::unordered_map<std::string, User> &users, const std::string &filename);
};