//
//  AccountManager.h
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/17/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef AccountManager_h
#define AccountManager_h
#include <map>
#include "Account.h"

/**
*   AccountManager Class.
*   An AccountManager object manages the accounts that it contains. The
*   AccountController should always interact with an Account via the AccountManager.
*   The AccountManager is responsible for creating and destroying Account objects.
*/
class AccountManager
{
public:
    AccountManager() {};
    ~AccountManager();
    void add_account(Account new_account);
    void add_item_to_account(std::string account_name, std::string where,std::string login, std::string password);
    bool valid_account_return(std::string name, std::string password);
    void delete_account(std::string account_name);
    void write_data_to_file();
    void populate();
    bool account_exists(std::string account_name);
    Account* get_account(std::string account_name, std::string account_password);
    std::string get_all_account_names();
private:
    std::map<std::string,Account> account_map;
};

#endif /* AccountManager_h */
