#ifndef _INPUT_STREAM_HPP_
#define _INPUT_STREAM_HPP_

class InputStream {
private:
    unsigned int pos = 0;
    unsigned int line = 1;
    unsigned int col = 0;
    std::string input;

public:
    InputStream(const std::string &input);
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
