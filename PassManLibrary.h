//
//  PassManLibrary.h
//  RHPasswordManager0.1
//
//  Created by Robert Hanna on 7/18/16.
//  Copyright © 2016 Robert Hanna. All rights reserved.
//

#ifndef PassManLibrary_h
#define PassManLibrary_h
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <termios.h>
#include <unistd.h>

namespace RHPasswordManager
{
    extern size_t root_menu(); //Menu options.
    extern void clear_terminal(); //Clears the terminal.
    extern void mask_terminal(termios &oldt); //Hides user input from the terminal.
    extern std::string encrypt(std::string to_encrypt); //Returns an encrypted string.
    extern void newline_format(std::string message, size_t newline_before, size_t newline_after); //Prints newlines before and/or after a message.
    extern void check_cin_fail(bool cin_ignore); //Checks input for failure.
    struct Map_Gen //Creates a static map with menu option / number relations.
    {
        static std::map<std::string,size_t> create_map()
        {
            std::map<std::string,size_t> my_map;
            my_map["create"] = 0;
            my_map["list"] = 1;
            my_map["view"] = 2;
            my_map["edit"] = 3;
            my_map["delete"] = 4;
            my_map["exit"] = 5;
            return my_map;
        }
        static std::map<std::string,size_t> menu_options;
    };
}

/**
*   Custom exception. Thrown when access to an account is denied.
*/
class Access_Denied : public std::runtime_error
{
public:
    Access_Denied(std::string message) : std::runtime_error(message) {};
};

/**
*   Custom exception. Thrown when an account(s) already exists.
*/
class Duplicate_Account : public std::runtime_error
{
public:
    Duplicate_Account(std::string message) : std::runtime_error(message) {};
};
#endif /* PassManLibrary_h */
