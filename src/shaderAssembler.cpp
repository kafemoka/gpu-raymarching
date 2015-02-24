#include "shaderAssembler.h"

std::string ShaderAssembler::assemble(std::string _path) {
    std::string shader;

    if(!loadFromPath(_path, &shader)) {
        std::cerr << "error loading shader from " + _path << std::endl;
        return "";
    }

    std::string startTag = "#pragma begin scene_def";
    std::string endTag = "#pragma end scene_def";

    size_t start = shader.find(startTag);
    size_t end = shader.find(endTag);

    if(start == std::string::npos && end == std::string::npos) {
        std::cerr << "missing scene definition" << std::endl;
        return "";
    }

    start += startTag.length();

    std::istringstream iss(shader.substr(start, end - start));

    for(std::string line; std::getline(iss, line); ) {
        std::cout << ">> " << line << std::endl;
    }

    return "";
}
