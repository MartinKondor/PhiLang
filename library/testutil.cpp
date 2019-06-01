
/**
 * Nice printing of the test case's result 
 */
const bool test(const char* what, const bool result) {
    std::cout << what;

    if (result) {
#       if defined(_WIN32) || defined(_WIN64)
            system("echo [42m");
            std::cout << "SUCCEEDED" << std::endl;
            system("echo [0m");
#       else
            system("\033[32m");
            cout << "SUCCEEDED" << endl;
            system("\033[0m");
#       endif
    }
    else
    {
#       if defined(_WIN32) || defined(_WIN64)
            system("echo [41m");
            std::cout << "FAILED" << std::endl;
            system("echo [0m");
#       else
            system("echo \033[31m");
            cout << "FAILED" << endl;
            system("echo \033[0m");
#       endif
    }

    return result;
}
