#ifndef VARIABLE_APP
#define VARIABLE_APP

#include <string>

class Variable {
    public:
        std::string value;
        const char type;
    
    Variable(std::string value, char type);
    Variable();
};

#endif