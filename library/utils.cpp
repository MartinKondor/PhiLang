#ifndef _UTILS_CPP_
#define _UTILS_CPP_

#include <algorithm>
#include <sstream>


namespace Utils {

    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    std::string to_string(int d) {
        std::ostringstream ss;
        ss << d;
        return ss.str();
    }

}

#endif
