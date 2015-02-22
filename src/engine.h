#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "graphics.h"
#include "filewatcher.h"
#include "default_vert.h"
#include "utils.h"
#include "shader.h"
#include "log.h"

using namespace std;

class Engine {

public:
    bool init();
    void watchingThread();
    void renderingThread();
    void setChildProcess(pid_t pid);
    void setParentProcess(pid_t pid);
    void setFragShaderPath(const string& fragShaderPath);

    friend void handleResize(GLFWwindow* window, int w, int h);
    friend void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void watcherCallback();

    void fragmentHasChanged();
    void destroy();

private:
    void render();
    bool initGL();
    bool initShader();

    bool fragHasChanged;

    GLFWwindow* window;
    GLuint vbo;
    GLint posAttrib;
    string fragShaderPath;

    pid_t childProcess;
    pid_t parentProcess;

    FileWatcher watcher;
    Shader shader;

    int width;
    int height;

};

extern void handleResize(GLFWwindow* window, int w, int h);
extern void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void watcherCallback();
