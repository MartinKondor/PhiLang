#include "../source/parser.cpp"


bool input_stream_should_behave_as_expected() {
    Parser::InputStream is = Parser::InputStream("a=0");
    
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
