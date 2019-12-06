import argparse

from variable import PhiType, PhiVariable


STACK = []  # Stores PhiVariables
NAMESPACE = []  # Stores functions


class PhiFunction:

    def __init__(self, id: str, parameters: list, body: str, return_type: PhiType=PhiType.NULL):
        self.id = id
        self.parameters = parameters
        self.return_type = return_type
        self.body = body

    def call(self, parameters: list):
        # if len(parameters) != self.parameters:
        #     raise Exception(f'Error, not enough parameter for function ({self.id}).')
        
        for i, v in enumerate(parameters):
            
            # Find var in stack
            for s in STACK:
                if s.id == v:
                    parameters[i] = s.value

        eval(self.body.format(','.join(parameters)))

    def __str__(self):
        return '{' + f'Function, id={self.id}' + '}'


def determine_phi_type(value: str):
    return PhiType.NULL


def Phi_exec_token(token: str, line_index: int):
    in_string = False

    # Go char by char
    for ch_index, ch in enumerate(token):
        if ch == '"':
            in_string = True
            continue

        if in_string:
            if ch == '"':
                in_string = False
            continue
        
        if ch == '=':  # Assignment
            parts = [p.strip() for p in token.split('=')]
            STACK.append(PhiVariable(parts[0], parts[1], determine_phi_type(parts[1])))
        elif ch == '(':  # Function call
            parts = [p.strip() for p in token.split('(')]

            if parts[-1][-1] != ')':
                raise Exception(f'Expected (")") at {line_index}:{ch_index}.')
            
            # Find function in namespace
            for func in NAMESPACE:
                if func.id == parts[0]:
                    func.call([p for p in parts[-1][:-1].split(',') if p])
                    break


def Phi_eval(contents: str):
    in_one_line_comment = False
    line_index = 1
    token = ''

    # Go char by char
    for ch_index, ch in enumerate(contents):
        if ch == '#':
            in_one_line_comment = True
            continue

        if ch == '\n' or ch == '\r':
            line_index += 1
            in_one_line_comment = False
            continue
        elif in_one_line_comment:
            continue

        if ch == '!':
            Phi_exec_token(token, line_index)
            token = ''
            continue

        token += ch


def main(input_file_name: str):
    # Read the contents of the input file
    input_file = open(args.input_file_name, 'r')
    contents = input_file.read()
    input_file.close()
    Phi_eval(contents)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Phi.')
    parser.add_argument('input_file_name', type=str, help='the phi input file')
    args = parser.parse_args()

    # Register the basic Phi functions
    NAMESPACE.append(PhiFunction('print', [PhiType.ANY], 'print({})', PhiType.NULL))

    main(args.input_file_name)
    
    print('\nSTACK:')
    for v in STACK:
        print(v)
