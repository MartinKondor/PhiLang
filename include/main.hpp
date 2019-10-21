#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <string>
#include <sstream>
#include <sys/stat.h>
#include <vector>


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
unsigned int get_op_precedence(const std::string op_str);

template<typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

template <typename T>
void merge_sort(std::vector<T> &arr, unsigned int beg_index, unsigned int end_index)
{
    if (beg_index == end_index)
    {
        return;
    }
    int mid = (beg_index + end_index) / 2;
    merge_sort(arr, beg_index, mid);
    merge_sort(arr, mid + 1, end_index);
    int i = beg_index, j = mid + 1;
    int l = end_index - beg_index + 1;
    T* temp = new T[l];

    for (size_t k = 0; k < l; k++)
    {
        if (j > end_index || (i <= mid && arr[i] < arr[j]))
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
    }

    for (size_t k = 0, i = beg_index; k < l; k++, i++)
    {
        arr[i] = temp[k];
    }
    delete temp;
}

/**
* Sorts the given array in place
* @returns The original indices
*/
template <typename T>
std::vector<size_t> sort(std::vector<T> &arr)
{
    std::vector<size_t> indices;
    merge_sort(arr, 0, arr.size());
    return indices;
}

#endif // _MAIN_HPP_
