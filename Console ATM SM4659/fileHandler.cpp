#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "fileHandler.h"

using namespace std;

void FileHandler::loadFromCSV(vector<User> &users, const string &filename)
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
            users.emplace_back(username, password);
        }
    }
    file.close();
}

void FileHandler::saveToCSV(const vector<User>& users, const string& filename){
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for(const User& user : users){
        file << user.getUsername() << "," << user.getPassword() << "\n";
    }
    file.close();
}