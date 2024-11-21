#pragma once

#include <vector>
#include "User.h"

class FileHandler{
    public:
        static void loadFromCSV(vector<User> &users, const string &filename);
        static void saveToCSV(const vector<User>& users, const string& filename);
};