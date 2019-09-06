/*--------------------------------------------

IO class for handling file system tasks.

--------------------------------------------*/
#ifndef _IO_HPP_
#define _IO_HPP_
namespace IO {

/**
* Reading in file an concatenate lines into one big string
* where each line is separated with '\n'
*/
const std::string read_file(const std::string &filepath);

inline bool is_file_exists(const std::string& name);

}  // namespace IO
#endif  // _IO_HPP_
