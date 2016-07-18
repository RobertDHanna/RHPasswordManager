//
//  AccountManagerHelperFunctions.h
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef AccountManagerHelperFunctions_h
#define AccountManagerHelperFunctions_h
#include "AccountManager.h"
#include <termios.h>
#include <unistd.h>
std::string root_menu();

Account getAccount(std::string username,AccountManager driver);

bool validatePassword(std::string accountName,std::string passwordAttempt,AccountManager driver);

void displayAccount(Account toDisplay);

std::string getNewAccountName(AccountManager &driver);

void addNewItemsToAccount(Account &toAdd);

bool validPassword(std::string);

void yesNoResponse(std::string &response);

std::string getPassword();

Account& getAccountToEdit(AccountManager &driver);

void maskTerminal(termios &oldt);

void changeItemInAccount(Account*& accountToChange);

void addItemToAccount(Account*& accountToAdd);

void removeItemFromAccount(Account*& accountToRemove);

void deleteAnAccount(AccountManager &driver);

void clearTerminal();

#endif /* AccountManagerHelperFunctions_h */
