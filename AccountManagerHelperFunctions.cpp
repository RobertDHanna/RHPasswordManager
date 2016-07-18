//
//  AccountManagerHelperFunctions.cpp
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "AccountManagerHelperFunctions.h"
//tcsetattr(STDIN_FILENO, TCSANOW, &oldt); unmask terminal
void yesNoResponse(std::string &response)
{
    while (response != "n" && response != "y")
    {
        std::cout << "please enter a valid command (y/n) : ";
        getline(std::cin,response);
    }
}

void addNewItemsToAccount(Account &toAdd)
{
    while (true)
    {
        std::string name = "";
        std::cout << "Name of the domain/local: ";
        getline(std::cin,name);
        
        std::cout << "Login/ID: ";
        std::string login = "";
        getline(std::cin,login);
        
        std::string u_password = getPassword();
        
        toAdd.addItem(name, login, u_password);
        
        std::cout << "ITEM ADDED.\n\n continue? (y/n) : ";
        std::string response;
        getline(std::cin,response);
        yesNoResponse(response);
        if (response == "n")
        {
            break;
        }
    }
}


bool validPassword(std::string potentialPassword)
{
    size_t digitCount = 0;
    if (potentialPassword.length() < 6)
    {
        std::cout << "Password must be greater than 6 characters long.\n";
        return false;
    }
    for (size_t i = 0; i < potentialPassword.length(); i++)
    {
        if (isdigit(potentialPassword[i]))
        {
            digitCount++;
        }
    }
    if (digitCount < 1 || digitCount == potentialPassword.length())
    {
        std::cout << "Password must include at least one digit and letter.\n";
        return false;
    }
    return true;
}

void displayAccount(Account toDisplay)
{
    std::cout << std::endl << toDisplay.displayAll() << std::endl;
}

Account getAccount(std::string username,AccountManager driver)
{
    std::string password = getPassword();
    if(validatePassword(username,password,driver))
    {
        return driver.getAccount(username);
    }
    invalidPassword except;
    throw except;
}

bool validatePassword(std::string accountName,std::string passwordAttempt,AccountManager driver)
{
    return driver.validAccountReturn(accountName, passwordAttempt);
}

std::string root_menu()
{
    std::string menu_choice = "";
    
        std::cout << "Please select an option: \n";
        std::cout << "(create) an account.\n";
        std::cout << "(list) all accounts.\n";
        std::cout << "(view) an account.\n";
        std::cout << "(edit) an account.\n";
        std::cout << "(delete) an account.\n";
        std::cout << "(exit) the program.\n";
        getline(std::cin,menu_choice);
    while (menu_choice != "create" && menu_choice != "view" && menu_choice != "delete"
          && menu_choice != "edit" && menu_choice != "exit" && menu_choice != "list")
    {
        std::cout << "(" << menu_choice << ") ";
        std::cout << "is not a valid command.\n\n";
        std::cout << "Please select an option: \n";
        std::cout << "(create) an account.\n";
        std::cout << "(list) all accounts.\n";
        std::cout << "(view) an account.\n";
        std::cout << "(edit) an account.\n";
        std::cout << "(delete) an account.\n";
        std::cout << "(exit) the program.\n";
        getline(std::cin,menu_choice);
        
    }
    return menu_choice;
    
}

std::string getNewAccountName(AccountManager& driver)
{
    std::string nameForAccount;
    std::cout << "New account name: ";
    getline(std::cin,nameForAccount);
    if (!driver.accountExists(nameForAccount))
    {
        return nameForAccount;
    }
    else
    {
        duplicateAccount except = nameForAccount;
        throw except;
    }
}

Account& getAccountToEdit(AccountManager &driver)
{
    std::cout << "Name of account to edit: ";
    std::string nameOfAccountToEdit = "";
    getline(std::cin,nameOfAccountToEdit);
    std::string password = getPassword();
    if (!driver.accountExists(nameOfAccountToEdit) || !validatePassword(nameOfAccountToEdit, password, driver))
    {
        invalidAccount except = password;
        throw except;
    }
    return driver.getAccount(nameOfAccountToEdit);
}

std::string getPassword()
{
    termios oldt;
    maskTerminal(oldt);
    std::string newPassword = "";
    std::string confirm = "";
    while (true)
    {
        std::cout << "password: ";
        newPassword = "";
        confirm = "";
        getline(std::cin,newPassword);
        
        std::cout << "confirm password: ";
        getline(std::cin,confirm);
        
        if (newPassword != confirm)
        {
            std::cout << "\n\nPasswords do not match.\n\n";
        }
        else
        {
            break;
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //unmask terminal
    return newPassword;
}

void maskTerminal(termios &oldt)
{
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void changeItemInAccount(Account*& accountToChange)
{
    try
    {
        int indexOfItemToChange = 0;
        std::cout << accountToChange->displayAll() << std::endl;
        std::cout << "item to change (index) : ";
        std::cin >> indexOfItemToChange;
        std::cin.ignore(1000,'\n');
        //toEdit is a reference to the pair contained in account.
        std::pair<std::pair<std::string,std::string>,std::string>* toEdit = accountToChange->returnItemToChange(indexOfItemToChange);
        
        std::cout << "0 => " << toEdit->first.first << "\n";
        std::cout << "1 => " << toEdit->first.second << "\n";
        std::cout << "2 => " << toEdit->second << "\n";
        std::cout << "to edit (where/login/password) : ";
        size_t numberToEdit = 0;
        std::cin >> numberToEdit;
        if (numberToEdit > 2)
        {
            std::cout << "\ninvalid.\n\n";
            return;
        }
        
        std::cout << "changed value: ";
        std::string change = "";
        std::cin >> change;
        if (numberToEdit == 0)
        {
            toEdit->first.first = change;
        }
        else if (numberToEdit == 1)
        {
            toEdit->first.second = change;
        }
        else if (numberToEdit == 2)
        {
            toEdit->second = change;
        }
    }
    catch(invalidAccount except)
    {
        std::cout << "\ninvalid index\n\n";
    }
}

void addItemToAccount(Account*& accountToAdd)
{
    std::string where, login, password;
    std::cout << "where: ";
    getline(std::cin,where);
    std::cout << "login: ";
    getline(std::cin,login);
    password = getPassword();
    accountToAdd->addItem(where, login, password);
    std::cout << "\nitem added.\n\n";
}

void removeItemFromAccount(Account*& accountToRemove)
{
    try
    {
        std::cout << accountToRemove->displayAll() << std::endl;
        std::cout << "item to remove (index) : ";
        int indexOfItemToRemove = 0;
        std::cin >> indexOfItemToRemove;
        std::cin.ignore(1000,'\n');
        accountToRemove->removeItem(indexOfItemToRemove);
        std::cout << "\nitem removed.\n\n";
    }
    catch(invalidIndex e)
    {
        std::cout << "\ninvalid index\n\n";
    }
}

void deleteAnAccount(AccountManager &driver)
{
    std::string accountToDelete = "";
    std::cout << "Please enter the name of the account: ";
    getline(std::cin,accountToDelete);
    if (!driver.accountExists(accountToDelete))
    {
        std::cout << "there is no account by this name.\n";
        return;
    }
    else
    {
        std::string password = getPassword();
        if (!validatePassword(accountToDelete, password, driver))
        {
            std::cout << "invalid password.\n";
        }
        else
        {
            driver.deleteAccount(accountToDelete);
            std::cout << "\naccount deleted.\n\n";
        }
    }
}

void clearTerminal() //this code will clear the terminal and put the cursor back to line one
{
    std::cout << "\033[2J\033[1;1H";
}