#ifndef AST_CPP_
#define AST_CPP_
#endif


namespace AST {
    
    class ASTNode {
        public:
        int parentID;
        int ID;
        std::string value;

        ASTNode(const int &parentID, const int &ID, const std::string &value) {
            this->parentID = parentID;
            this->ID = ID;
            this->value = value;
        }
    };

    class AST {
        private:
        int currentID;
        std::vector<ASTNode> container;
        
        public:
        AST() {
            this->currentID = 0;
            this->container = {};
        }

        const int getNewNodeID() {
            return ++this->currentID;
        }

        /**
        * Add a new uniuqe IDd node for the given
        * parentID with the given value
        */
        const int addNode(const int &parentID, const std::string &value) {
            const int newNodeID = this->getNewNodeID();
            this->container.push_back(ASTNode(parentID, newNodeID, value));
            return newNodeID;
        }

        /**
        * Rerturns the value of the searched node,
        * if the node does not found, it returns a
        * ASTNode(-1, -1, "null")
        */
        const ASTNode getNode(const int &ID) {
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].ID == ID) {
                    return this->container[i];
                }
            }
            return ASTNode(-1, -1, "null");
        }

        /**
        *  Returns the vector of the children nodes
        *  of the given IDd node
        */ 
        const std::vector<ASTNode> getChildren(const int &parentNodeID) {
            std::vector<ASTNode> children = {};
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].parentID == parentNodeID) {
                    children.push_back(this->container[i]);
                }
            }
            return children;
        }
        
        const void printChildren(int &parentNodeID) {
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].parentID == parentNodeID) {
                    std::cout << "ID: " << this->container[i].ID << " Value: " << this->container[i].value << std::endl;
                }
            }
        }
        
    };
    
}
