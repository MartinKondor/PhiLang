
class TokenStream {
private:
    int i = 0;

public:

    const bool is_digit(const char &ch) {
        return std::regex_match(Utils::to_string(ch), DIGIT_REGEX);
    }

    const bool is_keyword(const std::string &str) {
        return KEYWORDS.find(" " + str + " ") != std::string::npos;
    }

    const bool is_id_start(const char &ch) {
        return std::regex_match(Utils::to_string(ch), ID_START_REGEX);
    }

    const bool is_id(const char &ch) {
        return this->is_id_start(ch) || NOT_ID_STRING.find(ch) != std::string::npos;
    }

    const bool is_op_char(const char &ch) {
        return std::regex_match(Utils::to_string(ch), OPERATOR_REGEX);
    }

    const bool is_punc(const char &ch) {
        //return std::regex_match(Utils::to_string(ch), PUNC_REGEX);
    }

    /*
    const bool is_whitespace(const char &ch) {
        return " \t\n".indexOf(ch) >= 0;
    }

    function read_while(predicate) {
        var str = "";
        while (!input.eof() && predicate(input.peek()))
            str += input.next();
        return str;
    }

    function read_number() {
        var has_dot = false;
        var number = read_while(function(ch){
            if (ch == ".") {
                if (has_dot) return false;
                has_dot = true;
                return true;
            }
            return is_digit(ch);
        });
        return { type: "num", value: parseFloat(number) };
    }

    function read_ident() {
        var id = read_while(is_id);
        return {
            type  : is_keyword(id) ? "kw" : "var",
            value : id
        };
    }

    function read_escaped(end) {
        var escaped = false, str = "";
        input.next();
        while (!input.eof()) {
            var ch = input.next();
            if (escaped) {
                str += ch;
                escaped = false;
            } else if (ch == "\\") {
                escaped = true;
            } else if (ch == end) {
                break;
            } else {
                str += ch;
            }
        }
        return str;
    }

    function read_string() {
        return { type: "str", value: read_escaped('"') };
    }

    function skip_comment() {
        read_while(function(ch){ return ch != "\n" });
        input.next();
    }

    function read_next() {
        read_while(is_whitespace);
        if (input.eof()) return null;
        var ch = input.peek();
        if (ch == "#") {
            skip_comment();
            return read_next();
        }
        if (ch == '"') return read_string();
        if (is_digit(ch)) return read_number();
        if (is_id_start(ch)) return read_ident();
        if (is_punc(ch)) return {
            type  : "punc",
            value : input.next()
        };
        if (is_op_char(ch)) return {
            type  : "op",
            value : read_while(is_op_char)
        };
        input.croak("Can't handle character: " + ch);
    }

    function peek() {
        return current || (current = read_next());
    }

    function next() {
        var tok = current;
        current = null;
        return tok || read_next();
    }

    function eof() {
        return peek() == null;
    }
    */

};
