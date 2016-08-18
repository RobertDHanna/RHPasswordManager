//
//  AccountController.cpp
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/18/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "AccountController.h"

/************************************************************************
                AccountController Helper Functions
 ************************************************************************
 */

/**
*   Displays all Account info.
*/
void display_account(Account* to_display)
{
    std::cout << std::endl << to_display->display_all() << std::endl;
}

/**
*   A routine that is used to get a password from the active user. The function is
*   meant to keep prompting the user for a password until the user enters the same password
*   twice.
*/
std::string get_password()
{
    termios oldt;
    RHPasswordManager::mask_terminal(oldt);
    std::string new_password = "";
    std::string confirm = "";
    bool continue_prompt = true;
    while (continue_prompt)
    {
        std::cout << "\npassword: ";
        new_password = "";
        confirm = "";
        getline(std::cin,new_password);

        std::cout << "\nconfirm password: ";
        getline(std::cin,confirm);

        if (new_password != confirm)
        {
            std::cout << "\n\nPasswords do not match.\n\n";
        }
        else
        {
            continue_prompt = false;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //unmask terminal
    return new_password;
}

/**
*   Interacts with an AccountManager object to confirm the validity of a given password.
*/
bool validate_password(std::string accountName,std::string password_attempt,AccountManager account_manager)
{
    return account_manager.valid_account_return(accountName, password_attempt);
}

/**
*   A routine to prompt the user for a new Account name. If an Account name already
*   exists in the given AccountManager object, a Duplicate_Account exception is thrown.
*/
std::string get_new_account_name(AccountManager& account_manager_object)
{
    std::string new_account_name;
    std::cout << "New account name: ";
    getline(std::cin,new_account_name);
    if (!account_manager_object.account_exists(new_account_name))
    {
        return new_account_name;
    }
    else
    {
        std::stringstream message;
        message << "(" << new_account_name << ") already exists.";
        throw Duplicate_Account(message.str());
    }
}

/**
*   Validates that a given password meets several security constraints.
*/
bool validate_password_format(std::string password)
{
    size_t digit_count = 0;
    if (password.length() < 6)
    {
        std::cout << "Password must be at least 6 characters long.\n";
        return false;
    }

    for (size_t i = 0; i < password.length(); i++)
    {
        if (isdigit(password[i]))
        {
            digit_count++;
        }
    }

    if (digit_count < 1 || digit_count == password.length())
    {
        std::cout << "Password must include at least one digit and letter.\n";
        return false;
    }
    return true;
}

/**
*   A routine to get a "yes" or "no" response from the user.
*/
void yes_no_response(std::string &response)
{
    while (response != "n" && response != "y")
    {
        std::cout << "please enter a valid command (y/n) : ";
        getline(std::cin,response);
    }
}

/**
*   Gets the info needed for item creation and adds them to the given account.
*/
void add_items_to_account(Account &new_account)
{
    bool continue_adding = true;
    while (continue_adding)
    {
        std::string name = "";
        std::cout << "Name of the domain/local: ";
        getline(std::cin,name);

        std::cout << "Login/ID: ";
        std::string login = "";
        getline(std::cin,login);

        std::string new_password = get_password();

        new_account.add_item(name, login, new_password);

        std::cout << "ITEM ADDED.\n\n continue? (y/n) : ";
        std::string response;
        getline(std::cin,response);
        yes_no_response(response);
        if (response == "n")
        {
            continue_adding = false;
        }
    }
}

/**
*   Returns a pointer to the Account the user would like to edit. Password Verification
*   is done before an Account is returned.
*/
Account* get_account_to_edit(AccountManager &account_manager)
{
    std::cout << "Name of account to edit: ";
    std::string account_name = "";
    getline(std::cin,account_name);
    if (!account_manager.account_exists(account_name))
    {
        std::stringstream message;
        message << "Access denied to account: " << account_name;
        throw Access_Denied(message.str());
    }
    std::string password = get_password();
    if (!validate_password(account_name, password, account_manager))
    {
        std::stringstream message;
        message << "Access denied to account: " << account_name;
        throw Access_Denied(message.str());
    }
    return account_manager.get_account(account_name,password);
}

/**
*   Gets an AccountItem based on user preference and allows the user to edit
*   any value.
*   Returns a string upon success / failure.
*/
std::string edit_item(Account* account_to_edit)
{
    if (!account_to_edit->has_items())
    {
        return "Account has no items to edit.";
    }

    try
    {
        int item_index = 0;
        std::cout << account_to_edit->display_all() << std::endl;
        std::cout << "item number to edit: ";
        std::cin >> item_index;

        RHPasswordManager::check_cin_fail(true);
        std::cin.ignore(1000,'\n');

        AccountItem* item = account_to_edit->get_item_to_edit(item_index);

        std::cout << "0 => " << item->where << "\n";
        std::cout << "1 => " << item->login << "\n";
        std::cout << "2 => " << item->password << "\n";
        std::cout << "to edit (where/login/password) : ";
        size_t numberToEdit = 0;
        std::cin >> numberToEdit;

        RHPasswordManager::check_cin_fail(true);
        std::cin.ignore(1000,'\n');

        std::cout << "new value: ";
        std::string change = "";
        std::getline(std::cin,change);

        switch(numberToEdit)
        {
            case 0 :
                item->where = change;
                break;
            case 1 :
                item->login = change;
                break;
            case 2 :
                item->password = change;
                break;
            default:
                throw std::runtime_error("Invalid index.");
                break;
        }
        return "Item edited";
    }
    catch(std::runtime_error e)
    {

        return e.what();
    }
}

/**
*   Adds a new item to the given Account.
*/
std::string add_item(Account* account)
{
    std::string where = "", login = "", password = "";
    std::cout << "where: ";
    getline(std::cin,where);
    std::cout << "login: ";
    getline(std::cin,login);
    password = get_password();
    account->add_item(where, login, password);
    return "Item added.";
}

/**
*   Removes an item from the given Account.
*/
std::string remove_item_from_account(Account* account)
{
    try
    {
        std::cout << account->display_all() << std::endl;
        std::cout << "item to remove (index) : ";
        int index = 0;
        std::cin >> index;

        RHPasswordManager::check_cin_fail(true);

        std::cin.ignore(1000,'\n');
        account->remove_item(index);
        return "Item removed.";
    }
    catch(std::out_of_range e)
    {
        return e.what();
    }
}

/************************************************************************
                              Class Methods
 ************************************************************************
 */

/**
*   Constructor.
*/
AccountController::AccountController() {}

/**
*   Destructor. Calls the exit routine upon destruction.
*/
AccountController::~AccountController()
{
    exit();
}

/**
*   Runs the startup() routine. Calls the AccountManager populate() function
*   that builds Account objects from an encrypted file.
*/
void AccountController::startup()
{
    account_manager.populate();
}

/**
*   Create Account routine. Allows the user to add new passwords to the new Account.
*   Handles the Duplicate_Account case.
*/
void AccountController::create()
{
    try
    {
        std::string new_account_name = get_new_account_name(account_manager);
        std::string new_password = get_password(); //get password from the user

        while (!validate_password_format(new_password))
        {
            new_password = get_password();
        }

        Account new_account(new_account_name,new_password);

        std::cout << "\nWould you like to add new passwords? (y/n) : ";
        std::string response;
        getline(std::cin,response);
        yes_no_response(response);
        if (response == "y")
        {
            add_items_to_account(new_account);
        }
        account_manager.add_account(new_account);
        RHPasswordManager::clear_terminal();
        RHPasswordManager::newline_format("Account has been created!", 1, 2);
    }
    catch (Duplicate_Account e)
    {
        RHPasswordManager::newline_format(e.what(),1,2);
    }
}

/**
*   Lists all of the Account names in the AccountManager object.
*/
void AccountController::list()
{
    RHPasswordManager::newline_format("Accounts: ", 1, 0);
    std::cout << account_manager.get_all_account_names() << std::endl;
    std::cout << "Press enter to continue...\n";
    std::cin.get();
}

/**
*   View Account routine. After name / password validation, the entire contents of
*   an Account are displayed to the user. The terminal is cleared when the routine
*   is complete.
*/
void AccountController::view()
{
    std::string account_name = "";
    std::cout << "Please enter the name of the account: ";
    getline(std::cin,account_name);
    if (!account_manager.account_exists(account_name))
    {
        std::cout << "\n(" << account_name << ") ";
        std::cout << "is not a valid account.\n\n";
    }
    else
    {
        try
        {
            std::string password = get_password();
            display_account(account_manager.get_account(account_name, password));
            std::cout << "Press enter to continue ... ";
            std::cin.get();
            RHPasswordManager::clear_terminal();
        }
        catch (Access_Denied e)
        {
            RHPasswordManager::newline_format(e.what(), 1, 1);
        }
        RHPasswordManager::clear_terminal();
    }
}

/**
*   Edit Account routine. Gets a pointer to an Account object after password
*   validation. Allows the user to change a value or add/remove an item from an Account.
*/
void AccountController::edit()
{
    try
    {
        Account* account_to_edit = get_account_to_edit(account_manager);
        std::cout << "\n(change), (remove) or (add) to account: ";
        std::string choice = "";
        std::string result = "";
        std::getline(std::cin,choice);
        try
        {
            if (choice == "change")
            {
                result = edit_item(account_to_edit);
            }
            else if (choice == "add")
            {
                result = add_item(account_to_edit);
            }
            else if (choice == "remove")
            {
                result = remove_item_from_account(account_to_edit);
            }
        }
        catch (std::runtime_error e)
        {
            RHPasswordManager::newline_format(e.what(),1,1);
        }
        RHPasswordManager::clear_terminal();
        RHPasswordManager::newline_format(result,1,2);
    }
    catch (Access_Denied e)
    {
        RHPasswordManager::newline_format("Unable to access account.", 0, 2);
    }
}

/**
*   Delete Account routine. Deletes an account from the AccountManager object
*   after password validation.
*/
void AccountController::delete_account_routine()
{
    std::string account_name = "";
    std::cout << "Please enter the name of the account: ";
    getline(std::cin,account_name);
    if (!account_manager.account_exists(account_name))
    {
        RHPasswordManager::newline_format("There is no account by this name.", 1, 2);
        return;
    }
    else
    {
        std::string password = get_password();
        if (!validate_password(account_name, password, account_manager))
        {
            std::cout << "Invalid password.\n";
        }
        else
        {
            account_manager.delete_account(account_name);
            std::cout << "\nAccount deleted.\n\n";
        }
    }
}

/**
*   Exit routine. Writes all account info to a file.
*/
void AccountController::exit()
{
    account_manager.write_data_to_file();
}
