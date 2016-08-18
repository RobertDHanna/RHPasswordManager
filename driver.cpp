//
//  driver.cpp
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/18/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include "AccountController.h"

int main()
{
    AccountController controller; //AccountController object
    controller.startup(); //Build account objects from file.
    std::cout << std::setw(5) << "Welcome to Password Manager.\n\n";
    size_t menu_choice = 0;
    bool active = true;
    try
    {
        while(active)
        {
            menu_choice = RHPasswordManager::root_menu();
            switch(menu_choice)
            {
                case 0 :
                    controller.create(); //Create a new account.
                    break;
                case 1 :
                    controller.list(); //List all accounts.
                    break;
                case 2 :
                    controller.view(); //View passwords for a specific account.
                    break;
                case 3 :
                    controller.edit(); //Edit existing info for a specific account.
                    break;
                case 4 :
                    controller.delete_account_routine(); //Delete an existing account and it's content.
                    break;
                case 5 :
                    controller.exit(); //Write current data to file.
                    active = false;
                    break;
                default:
                    std::stringstream message;
                    message << "menu_choice: " << menu_choice << " not supported.\n";
                    throw std::runtime_error(message.str());
                    break;
            }
        }
    }
    catch(...)
    {
        // write to error log.
        std::cout << "Oops! There was an error.\n";
    }
}
