//
//  AccountManager.h
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef AccountManager_h
#define AccountManager_h
#include <string>
#include <map>
#include "Account.h"

class AccountManager
{
public:
    AccountManager();
    ~AccountManager();
    void addAccount(Account newAccount);
    void addItemToAccount(std::string nameOfAccount, std::string where,std::string login, std::string password);
    bool validAccountReturn(std::string name, std::string password);
    void deleteAccount(std::string accountName);
    void writeToEncryptedFile();
    void readFromEncryptedFile();
    bool accountExists(std::string accountName);
    Account& getAccount(std::string accountName);
    std::string getAllAccountNames();
    
private:
    std::map<std::string,Account> accountMap;
};

#endif /* AccountManager_h */
