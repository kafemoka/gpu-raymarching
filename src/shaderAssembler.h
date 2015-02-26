#pragma once

#include <iostream>
#include <sstream>
#include "objects/raymarchObject.h"
#include "lexer.h"
#include "utils.h"

class ShaderAssembler {

public:

    static std::string assemble(std::string _path);

};
