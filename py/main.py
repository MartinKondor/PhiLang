import argparse
import enum


class PhiType(enum.Enum):
    NULL = 0
    OBJ = 1  # Inherited by everything
    STR = 2
    NUM = 3 


class PhiVariable:
    name: str = ''
    type: PhiType = PhiType.NULL
    value: str or int or float = ''


class Error:
    ln_index: int = 0
    ch_index: int = 0
    msg: str = ''


class PhiFunction:
    name: str = ''
    body: str = ''  # Stores the code of the function
    parameters: list = []  # list[str] Parameter names
    is_built_in: bool = False


class PhiStack:
    """
    Stores variables and function for a given scope.
    """
    id: int = 0 # Stack ID
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


def Phi_get_variable(name: str, stack: PhiStack):
    """
    Returns variable form stack if found, else
    returns None 
    """
    for var in stack.variables:
        if var.name == name:
            return var
    return None


def Phi_maybe_get_variable(name: str, stack: PhiStack):
    """
    :name str:
    :returns PhiVarible or name: name if PhiVarible
            cannot be found with the given name.
    """
    var: PhiVariable = Phi_get_variable(name, stack)
    if var != None:
        return var 
    return name


def Phi_function_call(func_name: str, parameters: list, ln_index: int, ch_index: int, stack: PhiStack):
    """
    Attempt to call the given function with the given parameters.
    :param func_name: str
    :param parameters: list
    """
    func: PhiFunction = None

    # Check function in stack in case of undefined function
    for p_func in stack.functions:
        if p_func.name == func_name:
            func = p_func
            break

    if func == None:
        Phi_print_error(Phi_create_error(f'Undefined reference to function {func_name}.', ln_index, ch_index))
        exit(1)

    parameter_values = []

    # Find variables in the current stack
    for parameter in parameters:
        parameter_values.append(Phi_maybe_get_variable(parameter, stack))

    if func.is_built_in:
        func.body += '('
        params_str = ''

        for param in parameter_values:
            params_str += param.value + ','

        # Add kwargs
        for param in func.parameters:
            param += param + ',' 

        func.body += params_str + ')'
        eval(func.body)
    else:
        func.body += '('
        params_str = ''

        for param in parameter_values:
            params_str += param.value + ','

        # Add kwargs
        for param in func.parameters:
            param += param + ',' 

        func.body += params_str + ')'


def Phi_create_function(text: str):
    """
    :param text: str
    :returns PhiFunction: the scope with the contents of the function
    """
    func = PhiFunction()
    func.name = ''
    func.body = ''
    func.parameters = []

    last_ch_index = 0
    token = ''
    in_parameters = False

    for ch_index, ch in enumerate(text):
        if ch == '(':
            func.name = token
            in_parameters = True
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


def Phi_eval_command(command: str, ln_index: int, stack: PhiStack):
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
        stack.variables.append(var)
    if in_function_call_parameter_field:
        if other_token:
            parameters.append(other_token[:-1])

        Phi_function_call(token, parameters, ln_index, ch_index, stack)

    return None


def Phi_setup_stack(stack: PhiStack):
    """
    Adding the built-in functions and variables to the stack.
    """
    print_f = PhiFunction()
    print_f.name = 'print'
    print_f.body = 'print'
    print_f.parameters = ['end=""']
    print_f.is_built_in = True
    stack.functions.append(print_f)

    println_f = PhiFunction()
    println_f.name = 'println'
    println_f.body = 'print'
    println_f.parameters = []
    println_f.is_built_in = True
    stack.functions.append(println_f)


def Phi_eval(text: str, stack_id: int=0):
    """
    Exaluate Phi code from text param.
    :param text: str Phi code string
    :param stack_id: where to collect variables and functions.
    """

    # Go char by char
    ln_index = 1
    in_string = False
    in_one_line_comment = False
    in_function_def = False
    command = ''
    main_stack = PhiStack()
    main_stack.id = stack_id
    Phi_setup_stack(main_stack)

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

        if in_string:
            command += ch
            continue

        if ch == '{':
            in_function_def = True
        
        if ch == '}':
            if not in_function_def:
                Phi_print_error(Phi_create_error('Unopened function definition.', ln_index, ch_index))
                exit(1)

            in_function_def = False
            main_stack.functions.append(Phi_create_function(command + '}'))
            command = ''
            continue

        if in_function_def:
            command += ch
            continue

        if ch == '!':
            if in_string:
                Phi_print_error(Phi_create_error('Unclosed string.', ln_index, ch_index))
                exit(1)

            error = Phi_eval_command(command, ln_index, main_stack)
            command = ''

            if error is not None:
                Phi_print_error(error)
                exit(1)

            continue

        command += ch

    return main_stack


def main(input_file_name: str):

    # Read the contents of the input file
    input_file = open(args.input_file_name, 'r', encoding='utf-8')
    contents = input_file.read()
    input_file.close()

    main_scope = Phi_eval(contents)

    # Print main scope
    if 0:
        for var in main_scope.variables:
            Phi_print_variable(var)
        for func in main_scope.functions:
            Phi_print_function(func)


if __name__ == '__main__':

    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Phi.')
    parser.add_argument('input_file_name', type=str, help='the input file what contains Phi code')
    args = parser.parse_args()

    import time
    st = time.time()
    main(args.input_file_name)
    print('\nRun time:', time.time() - st)
