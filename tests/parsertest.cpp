#include "../source/parser.cpp"


bool input_stream_woks_on_one_line() {
    PARSER::InputStream is = PARSER::InputStream("a=0");
    if (is.is_eof()) {
        return false;
    }
    if (is.peek() != 'a') {
        return false;
    }
    if (is.next() != 'a') {
        return false;
    }
    if (is.next() != '=') {
        return false;
    }
    if (is.next() != '0') {
        return false;
    }
    if (!is.is_eof()) {
        return false;
    }
    try {
        is.croak("Test error");
        return false;
    } 
    catch (Phi_Error* err) {}
    return true;
}

bool input_stream_woks_on_multipe_lines() {
    PARSER::InputStream is = PARSER::InputStream("a=0\nb=1");
    if (is.is_eof()) {
        return false;
    }
    is.next();
    is.next();
    is.next();
    if (is.is_eof()) {
        return false;
    }
    if (is.next() != '\n') {
        return false;
    }
    return is.next() == 'b';
}

bool parser_wproperly() {
    return false;
}
