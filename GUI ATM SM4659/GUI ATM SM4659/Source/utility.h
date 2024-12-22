#pragma once
#include <string>

class Utility{
    public:
        static bool isValidPassword(const std::string& password);
        static bool isValidAccountType(std::string accountType);
};