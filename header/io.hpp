/*--------------------------------------------

IO class for handling file system tasks.

--------------------------------------------*/
#ifndef _IO_HPP_
#define _IO_HPP_

namespace IO {

    class IO {
        public:
        IO();
        ~IO();

        /**
         * Reading the contents of a file and returning the lines
         * as a vector of strings.
         */
        const std::vector<std::string> read_file(const std::string &filepath);

        /**
        * Reading in file an concatenate lines into one big string
        * where each line is separated by '\n'
        */
        const std::string read_file_as_str(const std::string &filepath);
    };

    inline bool is_file_exists(const std::string& name) {
        struct stat buffer;
        return (stat(name.c_str(), &buffer) == 0);
    }

}

#endif  // _IO_HPP_
