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
        if (args.size() != 2) {return "Error: Not Enough Args in Action";}
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        arg1->value = arg2.value;
        return "";
    };
    this->actions["call"] = [this](const std::vector<std::string>& args) {
        if (args.size() != 2) {return "Error: Not Enough Args in Action";}
        if (this->functions.find(args[0]) == this->functions.end()) {
            std::string error = "Error: Function not found: " + args[0];
            return error.c_str();
        }
        this->functions[args[0]](args);
        return "";
    };
    this->actions["add"] = [this](const std::vector<std::string>& args) {
        if (args.size() != 2) {return "Error: Not Enough Args in Action";}
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        if (arg1->type != 'i' || (arg2.type != 'i' && arg2.type != 'n')) {
            return "Error: Cannot perform addition on non-integer variables.";
        }
        arg1->value = std::to_string(std::stoi(arg1->value) + std::stoi(arg2.value));
        return "";
    };
    this->functions["makeVar"] = [this](const std::vector<std::string>& args) {
        std::string type = registers[0].value;
        std::string name = registers[1].value;
        std::string value = registers[2].value;
        this->variables.emplace(name, Variable(value, type[0]));
    };
    this->conditions["eq"] = [this](const std::vector<std::string>& args) {
        if (args.size() != 2) {
            std::cout << "\033[31m" << "Not Enough Args in Condition: (eq)" << "\033[0m" << std::endl;
            return false;
        }
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        if (arg1->value.compare(arg2.value) == 0) {
            return true;
        }
        return false;
    };
    this->conditions["lo"] = [this](const std::vector<std::string>& args) {
        if (args.size() != 2) {
            std::cout << "\033[31m" << "Not Enough Args in Condition: (lo)" << "\033[0m" << std::endl;
            return false;
        }
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        if (arg1->type != 'i' || (arg2.type != 'i' && arg2.type != 'n')) {
            std::cout << "\033[31m" << "Error: Cannot perform comparison on non-integer variables." << "\033[0m" << std::endl;
            return false;
        }
        if (std::stoi(arg1->value) < std::stoi(arg2.value)) {
            return true;
        }
        return false;
    };
    this->conditions["gr"] = [this](const std::vector<std::string>& args) {
        if (args.size() != 2) {
            std::cout << "\033[31m" << "Not Enough Args in Condition: (gr)" << "\033[0m" << std::endl;
            return false;
        }
        Variable* arg1 = this->getPointer(args[0]);
        Variable arg2 = this->getCopy(args[1]);
        if (arg1->type != 'i' || (arg2.type != 'i' && arg2.type != 'n')) {
            std::cout << "\033[31m" << "Error: Cannot perform comparison on non-integer variables." << "\033[0m" << std::endl;
            return false;
        }
        if (std::stoi(arg1->value) > std::stoi(arg2.value)) {
            return true;
        }
        return false;
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

std::string Compile::Run(std::string line) {
    std::string actionName = this->getActionName(line);
    if (actionName == "") {return "Error: Invalid Action";}
    std::vector<std::string> args = this->getArgs(line);
    std::string codeError = this->actions[actionName](args);
    return codeError == "" ? "" : (codeError + "\n Line: " + line);
}

bool Compile::Check(std::string line) {
    if (line == "") {return true;}
    std::string conditionName = this->getConditionName(line);
    if (conditionName == "") {return false;}
    std::vector<std::string> args = this->getArgs(line);
    return this->conditions[conditionName](args);
}

std::string Compile::getActionName(std::string line) {
    size_t pos = line.find(' ');
    std::string actionName = line.substr(0, pos);
    if (this->actions.find(actionName) == this->actions.end()) {return "";}
    return actionName;
}

std::string Compile::getFunctionName(std::string line) {
    size_t pos = line.find(' ');
    std::string functionName = line.substr(0, pos);
    if (this->functions.find(functionName) == this->functions.end()) {
        std::cout << "Function not found: (" << functionName  << ")" << std::endl;
        return "";
    }
    return functionName;
}

std::string Compile::getConditionName(std::string line) {
    size_t pos = line.find(' ');
    std::string conditionName = line.substr(0, pos);
    if (this->conditions.find(conditionName) == this->conditions.end()) {
        std::cout << "\033[31m" << "Condition not found: (" << conditionName  << ")" << "\033[0m" << std::endl;
        return "";
    }
    return conditionName;
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