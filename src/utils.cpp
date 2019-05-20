#include <algorithm>

#define N_OF_OPERATORS 14
const std::string OPERATORS[N_OF_OPERATORS] = {
    "==", "!=", "+=", "-=", ">=", "<=",
    "=", ">", "<", "/", "*", "%", "+", "-",
};

#define N_OF_KEYWORDS 27
const std::string KEYWORDS[N_OF_KEYWORDS] = {
    "if", "else", "elseif", "while", "for", "in",
	"continue", "break", "true", "false", "null",
	"and", "or", "not", "def", "return", "const",
	"try", "catch", "throw", "as", "import", "delete",
    "finally", "is", "pass", "yield"
};

namespace utils {
    const void closeWithError(const std::string errorText, const int lineNumber=0) {
        std::cout << "Error:" << std::endl;
        std::cout << "\t" << errorText << std::endl;
        if (lineNumber != 0) {
            std::cout << "\t" << "At line: " << lineNumber << std::endl;
        }
        exit(1);
    }

    const std::string removeSpace(const std::string text) {
        std::string newString = "";
        for (unsigned int i = 0; i < text.length(); i++) {
            if (text[i] != ' ') {
                newString += text[i];
            }
        }
        return newString;
    }

    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
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

    const void reverseStr(std::string& str) { 
        int n = str.length();
        for (int i = 0; i < n / 2; i++) 
            std::swap(str[i], str[n - i - 1]);
    } 

    const bool hasTheGivenKeyword(const std::string givenKeyword, const std::string text) {
        std::string inputText = text;
        trim(inputText);
    	if (inputText.substr(0, inputText.find_first_of(' ')) == givenKeyword) {
    		return true;
    	}
    	return false;
    }

    // ?
    const void replaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
        size_t pos = data.find(toSearch);
        while( pos != std::string::npos) {
            data.replace(pos, toSearch.size(), replaceStr);
            pos =data.find(toSearch, pos + replaceStr.size());
        }
    }

}
