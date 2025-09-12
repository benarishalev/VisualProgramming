#include "compile.hpp"

Compile::Compile(std::map<std::string, Variable>& variables) : variables(variables) {
    this->functions["print"] = [](const std::vector<std::string>& args) {
        int amount = std::stoi(args[1]);
        for (int i = 0; i < amount; i++) {
            std::cout << registers[i].value << " ";
        }
        std::cout << std::endl;
    };
    this->actions["mov"] = [this](const std::vector<std::string>& args) {
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        arg1->value = arg2.value;
    };
    this->actions["call"] = [this](const std::vector<std::string>& args) {
        this->functions[args[0]](args);
    };
    this->actions["add"] = [this](const std::vector<std::string>& args) {
        Variable* arg1 = this->getPointer(args[0]);
        Variable* arg2 = this->getPointer(args[1]);
        if (arg1->type != 'i' || arg2->type != 'i') {
            std::cout << "Error: Cannot perform addition on non-integer variables." << std::endl;
            return;
        }
        arg1->value = std::to_string(std::stoi(arg1->value) + std::stoi(arg2->value));
    };
    this->functions["makeVar"] = [this](const std::vector<std::string>& args) {
        std::string type = registers[0].value;
        std::string name = registers[1].value;
        std::string value = registers[2].value;
        this->variables.emplace(name, Variable(value, type[0]));
    };
}

Variable* Compile::getPointer(std::string arg) {
    if (arg[0] == 'r') {
        return &registers[std::stoi(arg.substr(1))];
    } else {
        return &this->variables[arg];
    }
}

Variable Compile::getCopy(std::string arg) {
    if (arg[0] == 'r') {
        return registers[std::stoi(arg.substr(1))];
    } else if (variables.find(arg) != variables.end()) {
        return this->variables[arg];
    } else {
        return Variable(arg, 'n');
    }
}

void Compile::Run(std::string line) {
    std::string actionName = this->getActionName(line);
    if (actionName == "") {return;}
    std::vector<std::string> args = this->getArgs(line);
    this->actions[actionName](args);
}

std::string Compile::getActionName(std::string line) {
    size_t pos = line.find(' ');
    std::string actionName = line.substr(0, pos);
    if (this->actions.find(actionName) == this->actions.end()) {
        std::cout << "Action not found: (" << actionName  << ")" << std::endl;
        return "";
    }
    return actionName;
}

std::string Compile::getFunctionName(std::string line) {
    size_t pos = line.find(' ');
    std::string functionName = line.substr(0, pos);
    if (this->functions.find(functionName) == functions.end()) {
        std::cout << "Function not found: (" << functionName  << ")" << std::endl;
        return "";
    }
    return functionName;
}

std::vector<std::string> Compile::getArgs(std::string line) {
    std::vector<std::string> args;
    // remove fisrt arg (function name)
    size_t firstSpacePos = line.find(' ');
    if (firstSpacePos == std::string::npos) {return args;}
    line = line.substr(firstSpacePos + 1);

    size_t CommaPos = line.find(',');
    while (CommaPos != std::string::npos) {
        args.push_back(line.substr(0, CommaPos));
        line.erase(0, CommaPos + 1);
        CommaPos = line.find(',');
    }
    args.push_back(line);

    for (int i = 0; i < args.size(); i++) {
        size_t spacePos = args[i].find(' ');
        while (spacePos != std::string::npos) {
            args[i].erase(spacePos, 1);
            spacePos = args[i].find(' ');
        }
    }
    return args;
}