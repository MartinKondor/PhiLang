#ifndef _INPUT_STREAM_HPP_
#define _INPUT_STREAM_HPP_

#include <iostream>
#include <string>


class InputStream
{
private:
    unsigned int pos_index;
    unsigned int line_index;
    unsigned int column_index;
    std::string input_string;

public:
    InputStream();
    InputStream(const std::string &input_string);

    /**
    * @returns the next value but without removing it from the stream.
    */
    char peek();

    /**
    * @returns the next value and also discards it from the stream.
    */
    char next();

    /**
    * @returns true if and only if there are no more values in the stream.
    */
    bool eof();

    /**
    * Throws a Phi_Error
    */
    void croak(const std::string &msg);
};

#endif // _INPUT_STREAM_HPP_