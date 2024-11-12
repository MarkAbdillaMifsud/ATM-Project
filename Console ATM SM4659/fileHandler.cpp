#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "fileHandler.h"

using namespace std;

void FileHandler::loadFromCSV(vector<User>& users){
    ifstream file("users.csv");
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

void FileHandler::saveToCSV(const vector<User>& users){
    ofstream file("users.csv");
    for(const User& user : users){
        file << user.getUsername() << "," << user.getPassword() << "\n";
    }
    file.close();
}