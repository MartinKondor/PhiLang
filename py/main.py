import argparse
import enum


class PhiType(enum.Enum):
    NULL = 0
    OBJ = 1  # Inherited by everything
    STR = 2


class PhiVariable:
    name: str
    type: PhiType
    value: str or int or float


class Error:
    ln_index: int
    ch_index: int
    msg: str


class PhiFunction:
    name: str
    body: str = ''  # Stores the code of the function
    parameters: list = []  # list[str] Parameter names


class PhiScope:
    """
    Stores variables and function for a given scope.
    """
    id: int  # Stack ID
    variables: list = []  # list[PhiVariable]
    functions: list = []  # list[PhiFunction]


def Phi_create_variable(name: str, type: PhiType, value: str or int or float or list):
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


def Phi_print_function(func: PhiFunction):
    print(f'<name={func.name}, params={func.parameters}, body={func.body}>')


def Phi_determine_type(value: str):
    """
    :returns: PhiType
    """
    if value[0] == '"':
        return PhiType.STR
    return PhiType.OBJ


def Phi_maybe_get_variable(name: str):
    """
    :name str:
    :returns PhiVarible or name: name if PhiVarible
            cannot be found with the given name.
    """
    return name


def Phi_function_call(func_name: str, parameters: list):
    """
    Attempt to call the given function with the given parameters.
    :param func_name: str
    :param parameters: list
    """
    parameter_values = []

    # Find variables in the current stack
    for parameter in parameters:
        parameter_values.append(Phi_maybe_get_variable(parameter))

    print(f'Calling "{func_name}" with parameters {parameter_values}')


def Phi_define_function(text: str):
    """
    :param text: str
    :returns PhiFunction: the scope with the contents of the function
    """
    last_ch_index = 0
    func = PhiFunction()
    token = ''
    in_parameters = False

    for ch_index, ch in enumerate(text):
        if ch == '(':
            in_parameters = True
            func.name = token
            token = ''
            continue
        
        if ch == ')':
            if not in_parameters:
                pass  # TODO: Throw error

            func.parameters.append(token)
            in_parameters = False
            token = ''
            continue

        if in_parameters and ch == ',':
            func.parameters.append(token)
            token = ''
            continue

        if ch == '{':
            last_ch_index = ch_index
            break

        token += ch

    # Extract the body of the function
    for i, _ in enumerate(text):
        if text[last_ch_index + i + 1] == '}':
            if i != len(text) - 1:
                pass  # TODO: Throw error

            break

        func.body += text[last_ch_index + i + 1]

    return func


def Phi_eval_command(command: str, ln_index: int, scope: PhiScope):
    """
    :command str: like "s=12"
    :returns None or Error:
    """    
    parameters = []
    in_function_call_parameter_field = False

    token = ''
    other_token = ''
    in_assignment = False

    for ch_index, ch in enumerate(command):  

        # Process parameters of function call
        if in_function_call_parameter_field:
            if ch == ',':
                var = Phi_create_variable(token, Phi_determine_type(other_token), other_token)
                parameters.append(var)
                other_token = ''
                continue

            other_token += ch
            continue
        
        if ch == '=':
            if in_assignment and not other_token:
                return Phi_create_error('Unexpected "=" operator.', ln_index, ch_index)

            in_assignment = True
            other_token = ''
            continue
        
        if ch == '(':
            in_function_call_parameter_field = True
            continue

        if in_assignment:
            other_token += ch
            continue

        token += ch

    if in_assignment:
        var = Phi_create_variable(token, Phi_determine_type(other_token), other_token)
        scope.variables.append(var)
        
        print('Allocating: ', end='')
        Phi_print_variable(var)
    if in_function_call_parameter_field:
        if other_token:
            parameters.append(other_token[:-1])
        Phi_function_call(token, parameters)

    return None


def Phi_eval(text: str, scope_id: int=0):
    """
    Exaluate Phi code from text param.
    :param text: str Phi code string
    :param scope_id: where to collect variables and functions.
    """

    # Go char by char
    ln_index = 1
    in_string = False
    in_one_line_comment = False
    in_function_def = False
    command = ''
    main_scope = PhiScope()
    main_scope.id = scope_id

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

        if ch == '{':
            in_function_def = True
        
        if ch == '}':
            if not in_function_def:
                Phi_print_error(Phi_create_error('Unopened function definition.', ln_index, ch_index))
                exit(1)

            in_function_def = False
            main_scope.functions.append(Phi_define_function(command + '}'))
            command = ''
            continue

        if in_function_def:
            command += ch
            continue

        if ch == '!':
            if in_string:
                Phi_print_error(Phi_create_error('Unclosed string.', ln_index, ch_index))
                exit(1)

            error = Phi_eval_command(command, ln_index, main_scope)
            command = ''

            if error is not None:
                Phi_print_error(error)
                exit(1)

            continue

        command += ch

    return main_scope


def main(input_file_name: str):
    # Read the contents of the input file
    input_file = open(args.input_file_name, 'r', encoding='utf-8')
    contents = input_file.read()
    input_file.close()

    main_scope = Phi_eval(contents)

    # Print main scope
    for var in main_scope.variables:
        Phi_print_variable(var)
    for func in main_scope.functions:
        Phi_print_function(func)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Phi.')
    parser.add_argument('input_file_name', type=str, help='the phi input file')
    args = parser.parse_args()

    main(args.input_file_name)
