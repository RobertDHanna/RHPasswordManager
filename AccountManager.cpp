//
//  AccountManager.cpp
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "AccountManager.h"

AccountManager::AccountManager() {}

AccountManager::~AccountManager(){writeToEncryptedFile();}

void AccountManager::addAccount(Account newAccount)
{
    //need to validate that account doesn't already exist
    accountMap[newAccount.name()] = newAccount;
}

bool AccountManager::validAccountReturn(std::string name, std::string u_password)
{
    if (accountMap[name].password() == u_password)
    {
        return true;
    }
    return false;
}
void AccountManager::deleteAccount(std::string accountName)
{
    accountMap.erase(accountName);
}

const std::string filename = "/Users/robertdonaverhanna/Documents/cpp/RHPasswordManager/RHPasswordManager/data.dat";

void AccountManager::writeToEncryptedFile()
{
    std::ofstream writeFile(filename.c_str());
    for (std::pair<std::string,Account> p : accountMap)
    {
        writeFile << p.second.returnEncryptedString();
    }
    writeFile.close();
}

std::string decrypted(std::string toDecrypt)
{
    char key = 's';
    std::string decryptToReturn = "";
    for (size_t i = 0; i < toDecrypt.length(); i++)
    {
        decryptToReturn += (toDecrypt[i] ^ (int(key) + i) % 255);
    }
    return decryptToReturn;
}

void AccountManager::readFromEncryptedFile()
{
    //extract existing account from data file upon execution
    std::ifstream readFile(filename.c_str());
    
    if (!readFile.is_open()) return;
    //if the file is open, read in account name and password.
    std::string username = "";
    std::string password = "";
    while(getline(readFile,username))
    {
        if (decrypted(username) == "EOF") break;
        getline(readFile,password);
        Account oldAccount(decrypted(username),decrypted(password));
        std::string where = "";
        //add existing passwords to account
        while (getline(readFile,where))
        {
            if (decrypted(where) == "EOF")
            {
                break;
            }
            
            std::string login = "";
            getline(readFile,login);
            std::string password = "";
            getline(readFile,password);
            
            oldAccount.addItem(decrypted(where), decrypted(login), decrypted(password));
        }
        accountMap[oldAccount.name()] = oldAccount;
    }
}

bool AccountManager::accountExists(std::string accountName)
{
    if (accountMap.count(accountName))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Account& AccountManager::getAccount(std::string accountName)
{
    if (accountMap.count(accountName))
    {
        return accountMap[accountName];
    }
    fatalError except = accountName;
    throw except;
    
}

void AccountManager::addItemToAccount(std::string nameOfAccount,std::string where,std::string login, std::string password)
{
    if (accountMap.find(nameOfAccount) != accountMap.end())
    {
        accountMap[nameOfAccount].addItem(where,login, password);
    }
}

std::string AccountManager::getAllAccountNames()
{
    std::stringstream ss;
    for (std::pair<std::string,Account> it : accountMap)
    {
        ss << "\n[ " << it.first << " ]";
    }
    ss << "\n";
    return ss.str();
}