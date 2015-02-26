#include <iostream>

#include "engine.h"
#include "utils.h"
#include "shaderAssembler.h"

static Engine* engine;

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
        case 256: // ESC
            glfwSetWindowShouldClose(engine->window, GL_TRUE);
    }
}

void handleResize(GLFWwindow* window, int w, int h) {
    engine->width = w;
    engine->height = h;

    glViewport(0, 0, w, h);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cerr << "Provide fragment shader argument" << std::endl;
        exit(-1);
    }

    std::string fragShaderPath = std::string(argv[1]);

    ShaderAssembler::assemble(fragShaderPath);

    return 0;
}
