#ifndef _UTILS_CPP_
#define _UTILS_CPP_


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

    /// Trim the given string from both ends (in place)
    inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    template<typename T> std::string to_string(const T &n) {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }

    /// @returns The current working directory
    const std::string getcwd() {
        char buff[FILENAME_MAX];
        __getcwd(buff, FILENAME_MAX);
        std::string current_working_dir(buff);
        return current_working_dir;
    }

}

namespace CommandUtils {

    /// Prints out help text
    const void showHelp() {
        cout << "PhiLang " << PHI_VERSION << " (" << OS_NAME << ")" << endl;
    }

}

#endif // _UTILS_CPP_
