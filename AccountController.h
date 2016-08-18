//
//  AccountController.h
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/18/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef AccountController_h
#define AccountController_h
#include "AccountManager.h"

/**
*   AccountController Class.
*   The AccountController object contains an AccountManager object. The
*   AccountController interacts with the user and sends data through the AccountManager
*   object to create / delete / edit Accounts.
*/
class AccountController
{
public:
    AccountController();
    ~AccountController();
    void startup();
    void create();
    void list();
    void view();
    void edit();
    void delete_account_routine();
    void exit();
private:
    AccountManager account_manager;
};

#endif /* AccountController_h */
