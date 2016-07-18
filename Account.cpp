//
//  Account.cpp
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "Account.h"

Account::Account() : nameOfAccount(""),accountPassword(""){}

Account::Account(std::string accountName,std::string accountPass) : nameOfAccount(accountName),accountPassword(accountPass) {}

Account::~Account() {}

void Account::addItem(std::string where,std::string login,std::string password)
{
    std::pair<std::pair<std::string,std::string>,std::string> p;
    p.first.first = where;
    p.first.second = login;
    p.second = password;
    listOfData.push_back(p);
}

std::pair<std::pair<std::string,std::string>,std::string>* Account::returnItemToChange(int index)
{
    if (index > listOfData.size()-1 || index < 0)
    {
        invalidIndex except;
        throw except;
    }
    else
    {
        return &listOfData[index];
    }
}

std::string encrypted(std::string toEncrypt)
{
    char key = 's';
    std::string encryptToReturn = "";
    for (size_t i = 0; i < toEncrypt.length(); i++)
    {
        encryptToReturn += (toEncrypt[i] ^ (int(key) + i) % 255);
    }
    return encryptToReturn;
}
//encrypted += original[temp] ^ (int(key) + temp) % 255;
std::string Account::returnEncryptedString()
{
    std::stringstream ss;
    ss << encrypted(nameOfAccount) << "\n";
    ss << encrypted(accountPassword) << "\n";
    for (size_t i = 0; i < listOfData.size(); i++)
    {
        ss << encrypted(listOfData[i].first.first) << "\n";
        ss << encrypted(listOfData[i].first.second) << "\n";
        ss << encrypted(listOfData[i].second) << "\n";
    }
    ss << encrypted("EOF") << std::endl;
    return ss.str();
}

std::string Account::displayAll()
{
    std::stringstream ss;
    ss << nameOfAccount << "\n";
    for (size_t i = 0; i < listOfData.size(); i++)
    {
        ss << "(" << i << ")\n";
        ss << "where: ";
        ss << listOfData[i].first.first << "\n";
        ss << "login: ";
        ss << listOfData[i].first.second << "\n";
        ss << "password: ";
        ss << listOfData[i].second << "\n";
    }
    return ss.str();
}

std::string Account::password()
{
    return accountPassword;
}

std::string Account::name()
{
    return nameOfAccount;
}

void Account::removeItem(int indexIntoVector)
{
    if (indexIntoVector > listOfData.size()-1 || indexIntoVector < 0)
    {
        invalidIndex except;
        throw except;
    }
    else
    {
        listOfData.erase(listOfData.begin() + indexIntoVector);
    }
}
