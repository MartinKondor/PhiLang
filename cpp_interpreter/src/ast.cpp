#include <iostream>
#include <string>
#include <vector>

namespace AST {
    class ASTNode {
        public:
        int parentID;
        int ID;
        std::string value;

        ASTNode(int _parentID, int _ID, std::string _value) {
            parentID = _parentID;
            ID = _ID;
            value = _value;
        }
    };

    class AST {
        private:
        int currentID;
        std::vector<ASTNode> container;
        
        public:
        AST() {
            currentID = 0;
            container = {};
        }

        const int getNewNodeID() {
            return ++currentID;
        }

        const int addNode(int parentID, std::string value) {
            const int newNodeID = getNewNodeID();
            container.push_back(ASTNode(parentID, newNodeID, value));
            return newNodeID;
        }

        const ASTNode getNode(int ID) {
            for (int i = 0; i < container.size(); i++) {
                if (container[i].ID == ID) {
                    return container[i];
                }
            }
            return ASTNode(-1, -1, "null");
        }

        const void printChildren(int parentNodeID) {
            for (int i = 0; i < container.size(); i++) {
                if (container[i].parentID == parentNodeID) {
                    std::cout << "ID: " << container[i].ID << " Value: " << container[i].value << std::endl;
                }
            }
        }

        const std::vector<ASTNode> getChildren(int parentNodeID) {
            std::vector<ASTNode> ret = {};
            for (int i = 0; i < container.size(); i++) {
                if (container[i].parentID == parentNodeID) {
                    ret.push_back(container[i]);
                }
            }
            return ret;
        }
    };
}
