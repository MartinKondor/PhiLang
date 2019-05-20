
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

        const int addNode(const int &parentID, const std::string &value) {
            const int newNodeID = this->getNewNodeID();
            this->container.push_back(ASTNode(parentID, newNodeID, value));
            return newNodeID;
        }

        const ASTNode getNode(const int &ID) {
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].ID == ID) {
                    return this->container[i];
                }
            }
            return ASTNode(-1, -1, "null");
        }

        const void printChildren(int &parentNodeID) {
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].parentID == parentNodeID) {
                    std::cout << "ID: " << this->container[i].ID << " Value: " << this->container[i].value << std::endl;
                }
            }
        }

        const std::vector<ASTNode> getChildren(const int &parentNodeID) {
            std::vector<ASTNode> ret = {};
            for (int i = 0; i < this->container.size(); i++) {
                if (this->container[i].parentID == parentNodeID) {
                    ret.push_back(this->container[i]);
                }
            }
            return ret;
        }
    };
}
