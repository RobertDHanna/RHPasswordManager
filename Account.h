//
//  Account.h
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef Account_h
#define Account_h
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "exceptionList.h"
class Account
{
public:
    Account();
    Account(std::string accountName,std::string accountPassword);
    ~Account();
    void addItem(std::string where,std::string login,std::string password);
    void removeItem(int indexIntoVector);
    std::pair<std::pair<std::string,std::string>,std::string>* returnItemToChange(int index);
    std::string password();
    std::string name();
    std::string displayAll();
    std::string returnEncryptedString();
private:
    std::string nameOfAccount;
    std::string accountPassword;
    std::vector<std::pair<std::pair<std::string,std::string>,std::string>> listOfData;
};




#endif /* Account_h */
