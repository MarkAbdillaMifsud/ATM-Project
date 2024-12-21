#pragma once
#include <unordered_map>
#include "User.h"

class FileHandler{
    public:
        static void loadUsersFromCSV(std::unordered_map<std::string, User>& users, const std::string& filename);
        static void saveUsersToCSV(const std::unordered_map<std::string, User>& users, const std::string& filename);
        static void loadAccountsFromCSV(std::unordered_map<std::string, User>& users, const std::string& filename);
        static void saveAccountsToCSV(const std::unordered_map<std::string, User>& users, const std::string& filename);
};