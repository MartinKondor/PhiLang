#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <string>
#include <sstream>
#include <sys/stat.h>


#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define built_in_getcwd _getcwd
#else
#define built_in_getcwd getcwd
#endif // _WIN32


/**
* @returns The current working directory
*/
std::string getcwd();

/**
* @returns True if the given file exists
*/
bool is_file_exists(const std::string file_name);

/**
* Reading in file an concatenate lines into one big string
* where each line is separated with '\n'
*/
std::string read_file(const std::string file_name);

/**
* Couts the help text
*/
void show_help();

/**
* Returns the given operator's priority
*/
int get_op_precedence(const std::string op_str);

template<typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

#endif // _MAIN_HPP_
