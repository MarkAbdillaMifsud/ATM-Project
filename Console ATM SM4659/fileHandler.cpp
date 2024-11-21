#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "fileHandler.h"

using namespace std;

void FileHandler::loadFromCSV(unordered_map<string, User> &users, const string &filename)
{
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        istringstream ss(line);
        string username, password;
        if(getline(ss, username, ',') && getline(ss, password)){
            users.emplace(username, User(username, password));
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}

void FileHandler::saveToCSV(const unordered_map<string, User>& users, const string& filename){
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for(const auto& pair : users){
        const User& user = pair.second;
        file << user.getUsername() << "," << user.getPassword() << "\n";
        if (file.fail()) {
            cerr << "Error writing to file: " << filename << endl;
            file.close();
        }
    }
    file.close();
}