//
//  Account.cpp
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/17/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "Account.h"

/*
 ************************************************************************
                AccountController Helper Functions
 ************************************************************************
 */

/**
*   Base Constructor.
*/
Account::Account() : account_name(""), account_password("") {}

/**
*   Overloaded Constructor.
*/
Account::Account(std::string account_name,std::string account_password)
        : account_name(account_name), account_password(account_password)
{}

/**
*   Destructor.
*/
Account::~Account() {}

/**
*   Creates an AccountItem object and stores it in the AccountItems container.
*/
void Account::add_item(std::string where,std::string login,std::string password)
{
    AccountItem item;
    item.where = where;
    item.login = login;
    item.password = password;
    account_items.push_back(item);
}

/**
*   Returns a pointer to an item within the AccountItems container. An exception is
*   thrown if an invalid index is given.
*/
AccountItem* Account::get_item_to_edit(int index)
{
    if (index > account_items.size() - 1 || index < 0 || account_items.size() == 0)
    {
        throw std::runtime_error("invalid index.");
    }
    else
    {
        return &account_items[index];
    }
}

/**
*   Returns a string with all items within the AccountItems container.
*/
std::string Account::display_all()
{
    std::stringstream ss;
    ss << account_name << "\n";
    for (size_t i = 0; i < account_items.size(); i++)
    {
        ss << "[item number: " << i << "]\n";
        ss << "where: ";
        ss << account_items[i].where << "\n";
        ss << "login: ";
        ss << account_items[i].login << "\n";
        ss << "password: ";
        ss << account_items[i].password << "\n";
    }
    return ss.str();
}

/**
*   Returns an XOR encrypted string with all of the Account info.
*/
std::string Account::get_encrypted_contents()
{
    std::stringstream ss;
    ss << RHPasswordManager::encrypt(account_name) << "\n";
    ss << RHPasswordManager::encrypt(account_password) << "\n";
    for (size_t i = 0; i < account_items.size(); i++)
    {
        ss << RHPasswordManager::encrypt(account_items[i].where) << "\n";
        ss << RHPasswordManager::encrypt(account_items[i].login) << "\n";
        ss << RHPasswordManager::encrypt(account_items[i].password) << "\n";
    }
    ss << RHPasswordManager::encrypt("EOF") << std::endl;
    return ss.str();
}

/**
*   Removes an item from the AccountItems container. Throws an exception if an
*   invalid index is given.
*/
void Account::remove_item(int index)
{
    if (index > account_items.size()-1 || index < 0)
    {
        throw std::out_of_range("Invalid index.");
    }
    else
    {
        account_items.erase(account_items.begin() + index);
    }
}

/**
*   Returns a boolean value representing whether an Account has any AccountItems
*   or not.
*/
bool Account::has_items()
{
    return account_items.size();
}
