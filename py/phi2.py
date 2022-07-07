"""
Phi classes are named "Phi<Classname>"
Phi functions are named "<function name>_f"
"""
import enum
from lib2to3.pgen2.token import EQEQUAL
import time
import argparse
from enum import Enum
from numpy import var

from yaml import parse


class Phi_NodeState(Enum):
    DEAD = 0  # Not used node
    LIVING = 1


class Phi_NodeType(Enum):
    UNKNOWN = 0
    EQUATION = 1
    VARIABLE = 2
    FUNCTION_CALL = 3


class Phi_Node:
    
    def __init__(self, type=Phi_NodeType.UNKNOWN):
        self.data = []
        self.type = type
        self.is_processed = False
        self.state = Phi_NodeState.LIVING

    def add_data(self, new_data):
        self.data.append(new_data)

    def isempty(self):
        if len(self.data) == 0:
            return True
        if len(self.data[0].strip()) == 0 and \
                len(self.data) == 1:
            return True
        return False

    def __str__(self):
        return self.data.__str__()

    @staticmethod
    def get_type(node):
        # Search for special characters
        for data in node.data:
            if data == "=":
                return Phi_NodeType.EQUATION    
            if data == "(":
                return Phi_NodeType.FUNCTION_CALL    
        return Phi_NodeType.UNKNOWN


class Phi_Tree:
    """
    Contains Phi_Nodes to be executed
    """
    def __init__(self):
        self.nodes = []

    def add_node(self, node: Phi_Node):
        self.nodes.append(node)

    def __str__(self):
        s = ""
        print("Tree:")
        for node in self.nodes:
            s += "\t" + node.__str__()
            s += "\t" + "\n"
        return s

    def remove_node(self, index):
        self.nodes[index].state = Phi_NodeState.DEAD

    def extend(self, new_nodes):
        for new_node in new_nodes:
            self.nodes.append(new_node)

    def get_var_value(self, var_name):
        for node in self.nodes:
            if node.data and node.type == Phi_NodeType.VARIABLE and node.data[0] == var_name:
                return node.data[1]
        return var_name

    def set_var_value(self, var_name, value):
        for node in self.nodes:
            if node.data and node.type == Phi_NodeType.VARIABLE and node.data[0] == var_name:
                node.data[1] = value
        return None


def execEquation(var_tree: Phi_Tree, to_var: str, type: Phi_NodeType, from_var: str) -> list:
    node = Phi_Node(type=Phi_NodeType.VARIABLE)

    if type == "=":
        val = var_tree.get_var_value(from_var)
        var_tree.set_var_value(to_var, val)
        node.add_data(to_var)
        node.add_data(val)

    return [node]


def execFunctionCall(var_tree: Phi_Tree, node: Phi_Node):
    func_name = node.data[0]
    params = [var_tree.get_var_value(d) for d in node.data[1:] if d not in ["(", ")"]]

    if func_name == "print":
        print(*params)


def execTree(tree: Phi_Tree):
    var_tree = Phi_Tree()

    for node in tree.nodes:
        node.type = Phi_Node.get_type(node)

        if node.type == Phi_NodeType.UNKNOWN:
            print("Error:", node)
            exit(1)
        if node.type == Phi_NodeType.EQUATION:
            if len(node.data) < 3:
                print("Error:", node)
                exit(1)

            new_tree = execEquation(var_tree, node.data[0], node.data[1], *node.data[2:])
            var_tree.extend(new_tree)

        if node.type == Phi_NodeType.FUNCTION_CALL:
            execFunctionCall(var_tree, node)

    return var_tree


def parseLine(line) -> Phi_Node:
    current_node = Phi_Node()
    parsed_line = ""

    for ch in line:
        #tree.add_node()
        
        # Check for special characters
        if ch == "#":
            break

        if ch == "=":
            current_node.add_data(parsed_line)
            current_node.add_data("=")
            parsed_line = ""
            continue

        if ch == "(":
            current_node.add_data(parsed_line)
            current_node.add_data("(")
            parsed_line = ""
            continue

        if ch == ")":
            current_node.add_data(parsed_line)
            parsed_line = ")"
            continue

        parsed_line += ch
    
    current_node.add_data(parsed_line)
    return current_node


"""
Remove excess whitespace and determine type
"""
def cleanNodes(tree):
    for node in tree.nodes:
        for i, data in enumerate(node.data):
            node.data[i] = data.strip()
            
            if data == "=":
                node.type = Phi_NodeType.EQUATION            

    return tree


def parseLines(lines):
    tree = Phi_Tree()
    
    for line in lines:
        node = parseLine(line)
    
        if not node.isempty():
            tree.add_node(node)

    return cleanNodes(tree)


def main(input_file_name):
    file = open(input_file_name, 'r')
    lines = file.readlines()
    file.close()

    tree = parseLines(lines)
    execTree(tree)


if __name__ == "__main__":

    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Phi language.')
    parser.add_argument('input_file_name', type=str, help='the input file what contains Phi code')
    args = parser.parse_args()

    start_time = time.time()
    main(args.input_file_name)
    print("Runtime:", time.time() - start_time)
