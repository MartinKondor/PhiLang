/*--------------------------------------------

Errors for the Phi language

--------------------------------------------*/
#ifndef _ERRORS_HPP_
#define _ERRORS_HPP_

class Phi_Error {
    private:
    std::string msg;

    public:
    Phi_Error(std::string msg) {
        this->msg = msg;
    }

    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

#endif
