"""
Phi classes are named "Phi<Classname>"
Phi functions are named "<function name>_f"
"""
import enum
from lib2to3.pgen2.token import EQEQUAL
import time
import argparse
from enum import Enum

from yaml import parse


class Phi_NodeState(Enum):
    DEAD = 0  # Not used node
    LIVING = 1


class Phi_NodeType(Enum):
    UNKNOWN = 0
    EQUATION = 1


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


def execEquation(to_var, type, from_var) -> list:
    pass


def execTree(tree: Phi_Tree):
    var_tree = Phi_Tree()

    for node in tree.nodes:
        if node.type == Phi_NodeType.UNKNOWN:
            print("Error:", node)
            exit(1)
        if node.type == Phi_NodeType.EQUATION:
            if len(node.data) < 3:
                print("Error:", node)
                exit(1)

            var_tree.extend(execEquation(node.data[0], node.data[1], *node.data[2:]))


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
