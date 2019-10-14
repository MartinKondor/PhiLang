#include "input_stream.hpp"


InputStream::InputStream() {}

InputStream::InputStream(const std::string &input_string)
{
    this->input_string = input_string;
    this->pos_index = 0;
    this->line_index = 1;
    this->column_index = 0;
}

char InputStream::peek()
{
    return this->pos_index < this->input_string.length() ? this->input_string[this->pos_index] : '\0';
}

char InputStream::next()
{
    if (this->pos_index >= this->input_string.length())
    {
        return '\0';
    }
    const char ch = this->input_string[this->pos_index];

    if (ch == '\n')
    {
        this->line_index++;
        this->column_index = 0;
    }
    else
    {
        this->column_index++;
    }

    this->pos_index++;
    return ch;
}

bool InputStream::eof()
{
    return this->peek() == '\0';
}

void InputStream::croak(const std::string &msg)
{
    std::cout << std::endl;
    std::cout << "Error: " << "(" << this->line_index << " : " << this->column_index << ")" << std::endl;
    std::cout << msg << std::endl;
    std::cout << std::endl;
    // throw new Phi_Error(msg);
    exit(EXIT_FAILURE);
}
