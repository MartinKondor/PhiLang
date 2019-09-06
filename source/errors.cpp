#include "../header/errors.hpp"


Phi_Error::Phi_Error(const std::string &msg) {
    this->m_msg = msg;
    cout << this->m_msg << endl;
}
