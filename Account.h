//
//  Account.h
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/17/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef Account_h
#define Account_h
#include <iostream>
#include <vector>
#include "PassManLibrary.h"

/**
*   Represents a password / username combo.
*   where - domain. ex. GMAIL
*   login - username. ex. Robert900
*   password - ex. h3lloTH3R3!
*/
struct AccountItem
{
    std::string where;
    std::string login;
    std::string password;
};

/**
*   Account Class. Contains the Account name and password as well as a list of
*   AccountItems stored in a <vector> container.
*/
class Account
{
public:
    Account();
    Account(std::string account_name,std::string account_password);
    ~Account();
    void add_item(std::string where,std::string login,std::string password);
    AccountItem* get_item_to_edit(int index);
    void remove_item(int index);
    // Getters
    std::string password() {return account_password;}
    std::string name() {return account_name;}
    std::string display_all();
    std::string get_encrypted_contents();
    bool has_items();
private:
    std::string account_name;
    std::string account_password;
    std::vector<AccountItem> account_items;
};

#endif /* Account_h */
