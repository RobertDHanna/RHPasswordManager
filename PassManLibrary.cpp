//
//  PassManLibrary.cpp
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/19/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#include <stdio.h>
#include "PassManLibrary.h"

/**
* A namespace for project-wide functions.
*/
namespace RHPasswordManager
{
    /**
    * Creates a static map to convert string menu options to numbers.
    */
    std::map<std::string,size_t> Map_Gen::menu_options =  Map_Gen::create_map();

    /**
    *   Gets a valid menu choice from the user.
    */
    size_t root_menu()
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
        //std::cout <<  Map_Gen::menu_options["list"] << std::endl;
        return Map_Gen::menu_options[menu_choice];
    }

    /**
    *   Clears the terminal and put the cursor back to line one.
    *   This is useful for removing sensitive information from the terminal.
    */
    void clear_terminal()
    {
        std::cout << "\033[2J\033[1;1H";
    }

    /**
    *   Hides user input. This is useful for when the user is entering sensitive
    *   information.
    */
    void mask_terminal(termios &oldt)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    
    /**
    *   XOR encrypts a string and returns the encrypted value.
    */
    std::string encrypt(std::string to_encrypt)
    {
        char key = 's';
        std::string encrypted_data = "";
        for (size_t i = 0; i < to_encrypt.length(); i++)
        {
            encrypted_data += (to_encrypt[i] ^ (int(key) + i) % 255);
        }
        return encrypted_data;
    }

    /**
    *   Allows for quicker format changes when printing something to the terminal.
    */
    void newline_format(std::string message, size_t newline_before, size_t newline_after)
    {
        for (size_t i = 0; i < newline_before; i++)
        {
            std::cout << "\n";
        }
        std::cout << message;
        for (size_t i = 0; i < newline_after; i++)
        {
            std::cout << "\n";
        }
    }

    /**
    *   Most user input is retrieved via getline(), but occasionally we want to get
    *   a single value from the user. (Usually for numbers)
    *   This checks to see if the input was bad and clears the buffer if needed.
    *   Throws a runtime exception.
    */
    void check_cin_fail(bool cin_ignore)
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            if (cin_ignore)
            {
                std::cin.ignore(1000,'\n');
            }
            throw std::runtime_error("Invalid input.");
        }
    }
}
