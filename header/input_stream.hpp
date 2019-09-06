#ifndef _INPUT_STREAM_HPP_
#define _INPUT_STREAM_HPP_

class InputStream {
private:
    unsigned int pos_index;
    unsigned int line_index;
    unsigned int column_index;
    std::string input_string;

public:
    InputStream(const std::string &input_string);
    ~InputStream();

    /**
    * @returns the next value but without removing it from the stream.
    */
    const char peek();

    /**
    * @returns the next value and also discards it from the stream.
    */
    const char next();

    /**
    * @returns true if and only if there are no more values in the stream.
    */
    const bool eof();

    /**
    * @returns does throw new Error(msg).
    */
    Phi_Error* croak(const std::string &msg);
};

#endif // _INPUT_STREAM_HPP_
