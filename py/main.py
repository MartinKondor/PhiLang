import argparse


class PhiVariable:
    name: str
    type: str
    value: str or int or float


class Error:
    ln_index: int
    ch_index: int
    msg: str


def Phi_create_variable(name: str, type: str or int or float or list, value: str or int or float or list):
    """
    Creates and returns a variable.
    """
    var = PhiVariable()
    var.name = name
    var.type = type
    var.value = value
    return var


def Phi_print_variable(var: PhiVariable):
    print(f'<name={var.name}, type={var.type}, value={var.value}>')


def Phi_create_error(msg: str, ln_index: int, ch_index: int):
    """
    Creates and returns an error.
    :returns Error:
    """
    err = Error()
    err.ln_index = ln_index
    err.ch_index = ch_index
    err.msg = msg
    return err

def Phi_print_error(error: Error):
    print(f'Error ({error.ln_index}:{error.ch_index}):\n{error.msg}')


def Phi_determine_type(value: str):
    """
    :returns: a type string
    """
    if value[0] == '"':
        return 'str'
    return 'obj'


def Phi_eval_command(command: str, ln_index: int):
    """
    :command str: like "s=12"
    :returns None or Error:
    """    
    token = ''
    other_token = ''
    in_assignment = False

    for ch_index, ch in enumerate(command):        
        if ch == '=':
            if in_assignment and not other_token:
                return Phi_create_error('Unexpected "=" operator.', ln_index, ch_index)

            in_assignment = True
            other_token = ''
            continue

        if in_assignment:
            other_token += ch
            continue

        token += ch

    if in_assignment:
        var = Phi_create_variable(token, Phi_determine_type(other_token), other_token)
        Phi_print_variable(var)

    return None


def Phi_eval(text: str):
    """
    Exaluate Phi code from text param.
    :text str:
    """

    # Go char by char
    ln_index = 0
    in_string = False
    in_one_line_comment = False
    command = ''

    for ch_index, ch in enumerate(text):
        if ch == '\n':
            ln_index += 1

            # Turn off one line comment
            if in_one_line_comment:
                in_one_line_comment = False

            continue

        # Ignore not important whitespace
        if in_one_line_comment or (ch == ' ' and not in_string):
            continue
        if ch == '#':
            in_one_line_comment = True
            continue

        # In string or not
        if ch == '"':
            in_string = not in_string

        if ch == '!':
            error = Phi_eval_command(command, ln_index)
            command = ''

            if error is not None:
                Phi_print_error(error)
                exit(1)

            continue

        command += ch


def main(input_file_name: str):
    # Read the contents of the input file
    input_file = open(args.input_file_name, 'r', encoding='utf-8')
    contents = input_file.read()
    input_file.close()

    Phi_eval(contents)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Phi.')
    parser.add_argument('input_file_name', type=str, help='the phi input file')
    args = parser.parse_args()

    main(args.input_file_name)
