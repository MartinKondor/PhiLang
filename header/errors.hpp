/*--------------------------------------------

Errors for the Phi language

--------------------------------------------*/
#ifndef _ERRORS_HPP_
#define _ERRORS_HPP_

class Phi_Error {
private:
    std::string m_msg;

public:
    Phi_Error(const std::string &msg);
    virtual const char* what() const throw() {return m_msg.c_str();}
};

#endif // _ERRORS_HPP_
