#pragma once

#include <iostream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

class Interpreter {

public:

    static std::string assemble(std::string _shader);

};
