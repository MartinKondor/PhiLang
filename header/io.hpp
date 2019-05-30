/*--------------------------------------------

IO class for handling file system tasks.

--------------------------------------------*/
#ifndef _IO_HPP_
#define _IO_HPP_

#include <fstream>


namespace IO {
    class IO {
        public:
        IO();

        /**
         * Reading the contents of a file and returning the lines
         * as a vector of strings.
         */
        const std::vector<std::string> read_file(std::string filepath);
    };
}

#endif
