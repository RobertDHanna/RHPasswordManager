//
//  main.cpp
//  RHPasswordManager
//
//  Created by Robert Hanna on 4/9/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//
#include "AccountManager.h"
#include <iostream>
#include <iomanip>
#include "AccountManagerHelperFunctions.h"


int main(int argc, const char * argv[]) {
    
    
    AccountManager driver; //create accountmanager object
    std::string menu_choice = "";
    driver.readFromEncryptedFile(); //read in account info from encrypted file
    std::cout << std::setw(5) << "Welcome to Password Manager.\n\n";
    while (true)
    {
        try
        {
            //grabs good input for menu

            menu_choice = root_menu();
      
            //if-block to handle user input
            if (menu_choice == "view")
            {
                std::string accountName = "";
                std::cout << "Please enter the name of the account: ";
                getline(std::cin,accountName);
                if (!driver.accountExists(accountName))
                {
                    std::cout << "\n(" << accountName << ") ";
                    std::cout << "is not a valid account.\n\n";
                }
                else
                {
                    try
                    {
                        displayAccount(getAccount(accountName,driver));
                        std::cout << "Press enter to continue ... ";
                        std::cin.get();
                        clearTerminal();
                    }
                    catch (invalidPassword)
                    {
                        std::cout << "\nInvalid password.\n\n";
                    }
                }
                
        
            }
            else if (menu_choice == "create") //user wants to create an account
            {
                std::string newAccountName = getNewAccountName(driver);
                try
                {
                    //get password from the user
                    std::string newPassword = getPassword();
                    while (!validPassword(newPassword))
                    {
                        newPassword = getPassword();
                    }
                    
                    Account newAccount(newAccountName,newPassword);
                    
                    std::cout << "Would you like to add new passwords? (y/n) : ";
                    std::string response;
                    getline(std::cin,response);
                    yesNoResponse(response);
                    if (response == "y")
                    {
                        addNewItemsToAccount(newAccount);
                    }
                    driver.addAccount(newAccount);
                    std::cout << "\nAccount has been created!\n";
                }
                catch (duplicateAccount except)
                {
                    std::cout << "(" << except << ") ";
                    std::cout << "already exists.\n\n";
                }
            }
            else if (menu_choice == "list")
            {
                std::cout << driver.getAllAccountNames() << std::endl;
            }
            else if (menu_choice == "edit")
            {
                try
                {
                    Account* accountToEdit = &getAccountToEdit(driver);
                    std::cout << "(change), (remove) or (add) to account: ";
                    std::string choice = "";
                    std::getline(std::cin,choice);
                    if (choice == "change")
                    {
                        changeItemInAccount(accountToEdit);
                    }
                    else if (choice == "add")
                    {
                        addItemToAccount(accountToEdit);
                    }
                    else if (choice == "remove")
                    {
                        removeItemFromAccount(accountToEdit);
                    }
                    clearTerminal();
                }
                catch (invalidAccount)
                {
                    std::cout << "\nunable to access account.\n\n";
                }
            }
            else if (menu_choice == "delete")
            {
                deleteAnAccount(driver);
                clearTerminal();
            }
            else
            {
                std::cout << "\nlogging out.\n";
                //write data to encrypted file
                return 0;
            }
        }
        catch (fatalError except)
        {
            std::cout << "\nFatal error: " << except << "\n\n";
        }
    }
    return 0;
}





