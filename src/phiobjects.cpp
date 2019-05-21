#ifndef PHIOBJECTS_CPP_
#define PHIOBJECTS_CPP_
#endif


namespace PhiObjects {
    
    class PhiObject {
        public:
        std::string ID;
        std::string value;
        std::string type;

        PhiObject() {
            this->ID = "null";
            this->value = "null";
            this->type = "null";
        }

        PhiObject(const std::string &ID, const std::string &value, const std::string &type) {
            this->ID = ID;
            this->value = value;
            this->type = type;
        }

        /**
         * Basic methods.
         * These must be defined for every object
         */
        bool __isEqual__(const PhiObject &other) {
            return this->ID == other.ID && this->type == other.type && this->value == other.value;
        }

        /**
        * Method for the + operator
        */
        PhiObject __plus__(const PhiObject &other) {
            if (this->type == "number" && other.type == "number") {
                return PhiObject("null", std::to_string(std::stoi(this->value) + std::stoi(other.value)), "number");
            }
            else if (this->type == "string" && other.type == "string") {
                return PhiObject("null", this->value + other.value, "string");
            }
            // TODO: implement element wise array addition
            utils::closeWithError("Types cannot be added together: \"" + this->type + "\" + \"" + other.type + "\"");
            return PhiObject();
        }
        
        /**
        * Method for the - operator
        */
        PhiObject __minus__(const PhiObject &other) {
            if (this->type == "number" && other.type == "number") {
                return PhiObject("null", std::to_string(std::stoi(this->value) - std::stoi(other.value)), "number");
            }
            // TODO: implement element wise array substraction
            utils::closeWithError("Types cannot be subtracted: \"" + this->type + "\" + \"" + other.type + "\"");
            return PhiObject();
        }

        /**
        * Method for the * operator
        */
        PhiObject __star__(const PhiObject &other) {
            if (this->type == "number" && other.type == "number") {
                return PhiObject("null", std::to_string(std::stoi(this->value) * std::stoi(other.value)), "number");
            }
            // TODO: implement element wise array substraction
            utils::closeWithError("Types cannot be multiplied: \"" + this->type + "\" + \"" + other.type + "\"");
            return PhiObject();
        }

        /**
        * Method for the / operator
        */
        PhiObject __slash__(const PhiObject &other) {
            if (this->type == "number" && other.type == "number") {
                return PhiObject("null", std::to_string(std::stof(this->value) / std::stof(other.value)), "number");
            }
            // TODO: implement element wise array substraction
            utils::closeWithError("Types cannot be subtracted: \"" + this->type + "\" + \"" + other.type + "\"");
            return PhiObject();
        }

        /**
        * Method for the % operator
        */
        PhiObject __modulo__(const PhiObject &other) {
            if (this->type == "number" && other.type == "number") {
                return PhiObject("null", std::to_string(std::stoi(this->value) % std::stoi(other.value)), "number");
            }
            // TODO: implement element wise array substraction
            utils::closeWithError("Types cannot be used with modulo: \"" + this->type + "\" + \"" + other.type + "\"");
            return PhiObject();
        }

    };

}
