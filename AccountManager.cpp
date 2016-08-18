//
//  AccountManager.cpp
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/17/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "AccountManager.h"

/**
*   Destructor. Saves Account info to a file before it's destroyed.
*/
AccountManager::~AccountManager() { write_data_to_file(); };

/**
*   Adds a new account to the <map> container.
*/
void AccountManager::add_account(Account new_account)
{
    //TODO: need to validate that account doesn't already exist
    account_map[new_account.name()] = new_account;
}

/**
*   Adds an item to a specific account.
*/
void AccountManager::add_item_to_account(std::string account_name, std::string where,std::string login, std::string password)
{
    if (account_map.find(account_name) != account_map.end())
    {
        account_map[account_name].add_item(where,login, password);
    }
}

/**
*   Password Verification.
*/
bool AccountManager::valid_account_return(std::string name, std::string user_password)
{
    return account_map[name].password() == user_password;
}

/**
*   Deletes an account from the <map> container.
*/
void AccountManager::delete_account(std::string account_name)
{
    account_map.erase(account_name);
}

const std::string FILENAME = "PATH_TO_FILE/data.dat";

/**
*   Saves an Account's encrypted contents in a file.
*/
void AccountManager::write_data_to_file()
{
    std::ofstream write_file(FILENAME.c_str());
    for (std::pair<std::string,Account> account : account_map)
    {
        write_file << account.second.get_encrypted_contents();
    }
    write_file.close();
}

/**
*   Creates Account objects that were saved in the encrypted file.
*/
void AccountManager::populate()
{
    //extract existing account from data file upon execution
    std::ifstream read_file(FILENAME.c_str());

    if (!read_file.is_open()) return;
    //if the file is open, read in account name and password.
    std::string username = "";
    std::string password = "";
    while(getline(read_file,username))
    {
        if (RHPasswordManager::encrypt(username) == "EOF") break;
        getline(read_file,password);
        Account old_account(RHPasswordManager::encrypt(username),RHPasswordManager::encrypt(password));

        std::string where = "";
        std::string login = "";
        std::string password = "";
        //add existing passwords to account
        while (getline(read_file,where))
        {
            if (RHPasswordManager::encrypt(where) == "EOF")
            {
                break;
            }

            getline(read_file,login);
            getline(read_file,password);

            old_account.add_item(RHPasswordManager::encrypt(where),
                               RHPasswordManager::encrypt(login),
                               RHPasswordManager::encrypt(password));
        }
        add_account(old_account);
    }
}

/**
*   Verifies that an Account exists in the <map> storage container.
*/
bool AccountManager::account_exists(std::string account_name)
{
    return account_map.count(account_name);
}

/**
*   Returns a pointer to an Account. Throws an exception if the provided password
*   does not match the Account password.
*/
Account* AccountManager::get_account(std::string account_name, std::string account_password)
{
    if (account_exists(account_name))
    {
        if (valid_account_return(account_name, account_password))
        {
            return &account_map[account_name];
        }
    }
    std::stringstream message;
    message << "Access denied to account: " << account_name << "\n";
    throw Access_Denied(message.str());
}

/**
*   Returns a list of all of the Account names the AccountManager object contains.
*/
std::string AccountManager::get_all_account_names()
{
    std::stringstream account_names;
    for (std::pair<std::string,Account> accounts : account_map)
    {
        account_names << "\n[ " << accounts.first << " ]";
    }
    account_names << "\n";
    return account_names.str();
}
