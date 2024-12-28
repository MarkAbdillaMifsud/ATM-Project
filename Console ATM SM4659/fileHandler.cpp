#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <filesystem>
#include "fileHandler.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

#ifdef _WIN32
    #include <windows.h>
    #ifndef PATH_MAX
        #define PATH_MAX MAX_PATH
    #endif
#elif __APPLE__
    #include <mach-o/dyld.h>
#elif __linux__
    #include <unistd.h>
    #include <limits.h>
#endif

using namespace std;

string FileHandler::getExecutablePath(){
    char buffer[PATH_MAX];
    #ifdef _WIN32
        DWORD length = GetModuleFileNameA(NULL, buffer, sizeof(buffer));
        if (length == 0 || length == sizeof(buffer))
            return "";
    #elif __APPLE__
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) != 0)
            return "";
    #elif __linux__
        ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (length == -1)
            return "";
        buffer[length] = '\0';
    #endif
        return std::string(buffer);
}

string FileHandler::getRootDirectory()
{
    string exePath = getExecutablePath();
    if (exePath.empty())
    {
        cerr << "Failed to retrieve executable path." << std::endl;
        return "";
    }

    filesystem::path path(exePath);
    filesystem::path rootDir = path.parent_path(); // Start with executable's directory

    // Define the target root directory name
    std::string targetDirName = "SMc21467 Assignment SM4659";

    // Traverse up the directory tree to locate the root directory
    while (!rootDir.empty() && rootDir.filename().string() != targetDirName)
    {
        rootDir = rootDir.parent_path();
    }

    if (rootDir.empty())
    {
        std::cerr << "Root directory '" << targetDirName << "' not found in the path hierarchy." << std::endl;
        return "";
    }

    return rootDir.string();
}

void FileHandler::loadUsersFromCSV(unordered_map<string, User> &users, const string &filename)
{
    string rootDir = getRootDirectory();
    if (rootDir.empty()) {
        std::cerr << "Unable to determine root directory for loading users." << std::endl;
        return;
    }

    std::filesystem::path filePath = std::filesystem::path(rootDir) / filename;
    std::string absolutePath = filePath.string();

    std::ifstream file(absolutePath);
    if (!file.is_open()) {
        std::cerr << "Error opening users file: " << absolutePath << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;
    while (std::getline(file, line)) {
        if (isFirstLine) { // Skip header
            isFirstLine = false;
            continue;
        }

        if (line.empty()) {
            std::cerr << "Encountered an empty line in users.csv, skipping." << std::endl;
            continue;
        }

        std::istringstream ss(line);
        std::string username, password;
        if (std::getline(ss, username, ',') && std::getline(ss, password, ',')) {
            if (users.find(username) == users.end()) {
                users.emplace(username, User(username, password));
            } else {
                std::cerr << "Duplicate user detected: " << username << ", skipping." << std::endl;
            }
        } else {
            std::cerr << "Malformed line in users.csv: " << line << ", skipping." << std::endl;
        }
    }

    file.close();
}

void FileHandler::saveUsersToCSV(const std::unordered_map<std::string, User> &users, const std::string &filename)
{
    std::string rootDir = getRootDirectory();
    if (rootDir.empty())
    {
        std::cerr << "Unable to determine root directory for saving users." << std::endl;
        return;
    }

    std::filesystem::path filePath = std::filesystem::path(rootDir) / filename;
    std::string absolutePath = filePath.string();

    std::ofstream file(absolutePath, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening users file for writing: " << absolutePath << std::endl;
        return;
    }

    // Write header
    file << "Username,Password\n";

    // Write user data
    for (const auto &pair : users)
    {
        file << pair.first << "," << pair.second.getPassword() << "\n";
    }

    std::cout << "Users saved successfully." << std::endl;
    file.close();
}

// Load Bank Accounts from CSV
void FileHandler::loadAccountsFromCSV(std::unordered_map<int, std::shared_ptr<BankAccount>> &bankAccounts, const std::string &filename)
{
    std::string rootDir = getRootDirectory();
    if (rootDir.empty())
    {
        std::cerr << "Unable to determine root directory for loading bank accounts." << std::endl;
        return;
    }

    std::filesystem::path filePath = std::filesystem::path(rootDir) / filename;
    std::string absolutePath = filePath.string();

    std::ifstream file(absolutePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening bank accounts file: " << absolutePath << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;
    int lineNumber = 0;
    while (std::getline(file, line))
    {
        lineNumber++;
        if (isFirstLine)
        { // Skip header
            isFirstLine = false;
            continue;
        }

        if (line.empty())
        {
            std::cerr << "Encountered an empty line at line " << lineNumber << " in bankAccounts.csv, skipping." << std::endl;
            continue;
        }

        std::istringstream ss(line);
        std::string username, accountNumberStr, accountType, balanceStr;
        if (std::getline(ss, username, ',') && std::getline(ss, accountNumberStr, ',') &&
            std::getline(ss, accountType, ',') && std::getline(ss, balanceStr, ','))
        {
            try
            {
                int accountNumber = std::stoi(accountNumberStr);
                float balance = std::stof(balanceStr);

                // Check for duplicate account numbers
                if (bankAccounts.find(accountNumber) != bankAccounts.end())
                {
                    std::cerr << "Duplicate account number: " << accountNumber << " at line " << lineNumber << ", skipping." << std::endl;
                    continue;
                }

                std::shared_ptr<BankAccount> account;
                if (accountType == "SavingsAccount")
                {
                    account = std::make_shared<SavingsAccount>(accountNumber, username);
                }
                else if (accountType == "CurrentAccount")
                {
                    account = std::make_shared<CurrentAccount>(accountNumber, username);
                }
                else
                {
                    std::cerr << "Unknown account type: " << accountType << " at line " << lineNumber << ", skipping." << std::endl;
                    continue; // Skip unknown account types
                }

                account->setBalance(balance);
                bankAccounts.emplace(accountNumber, account);
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Invalid data format at line " << lineNumber << " in bankAccounts.csv: " << line << ", skipping." << std::endl;
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "Data out of range at line " << lineNumber << " in bankAccounts.csv: " << line << ", skipping." << std::endl;
            }
        }
        else
        {
            std::cerr << "Incomplete data at line " << lineNumber << " in bankAccounts.csv: " << line << ", skipping." << std::endl;
        }
    }

    file.close();
}

// Save Bank Accounts to CSV
void FileHandler::saveAccountsToCSV(const std::unordered_map<int, std::shared_ptr<BankAccount>> &bankAccounts, const std::string &filename)
{
    std::string rootDir = getRootDirectory();
    if (rootDir.empty())
    {
        std::cerr << "Unable to determine root directory for saving bank accounts." << std::endl;
        return;
    }

    std::filesystem::path filePath = std::filesystem::path(rootDir) / filename;
    std::string absolutePath = filePath.string();

    std::ofstream file(absolutePath, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening bank accounts file for writing: " << absolutePath << std::endl;
        return;
    }

    // Write header
    file << "Username,AccountNumber,AccountType,Balance\n";

    // Write account data
    for (const auto &pair : bankAccounts)
    {
        int accountNumber = pair.first;
        auto account = pair.second;

        std::string accountType = "BankAccount"; // Default type
        if (dynamic_cast<SavingsAccount *>(account.get()))
        {
            accountType = "SavingsAccount";
        }
        else if (dynamic_cast<CurrentAccount *>(account.get()))
        {
            accountType = "CurrentAccount";
        }

        std::string username = account->getUsername();
        float balance = account->getBalance();

        file << username << "," << accountNumber << "," << accountType << "," << balance << "\n";
    }
    file.close();
}