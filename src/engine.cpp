#include "engine.h"

bool Engine::init() {
    bool init = initGL();
    shader.log = &(ScreenLog::Instance());
    fragHasChanged = false;
    return init && initShader();
}

void Engine::destroy() {
    glDeleteBuffers(1, &vbo);
}

bool Engine::initShader() {
    string fragSource;

    if(!loadFromPath(fragShaderPath, &fragSource)) {
        std::cerr << "Unable to load " << fragShaderPath << std::endl;
        return false;
    }

    if(!shader.build(fragSource, vertexShader)) {
        return false;
    }

    float vertices[12];

    quad(vertices);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    posAttrib = glGetAttribLocation(shader.getProgram(), "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    return true;
}

void Engine::setChildProcess(pid_t pid) {
    childProcess = pid;
}

void Engine::setParentProcess(pid_t pid) {
    parentProcess = pid;
}

void Engine::setFragShaderPath(const string& shaderPath) {
    fragShaderPath = shaderPath;
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    shader.sendUniform("resolution", width, height);
    shader.sendUniform("time", glfwGetTime());

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Engine::fragmentHasChanged() {
    fragHasChanged = true;
}

bool Engine::initGL() {
    width = 800;
    height = 600;

    if(!glfwInit()) {
        cerr << "GLFW init failed" << endl;
        return false;
    }

    window = glfwCreateWindow(width, height, "fragtool", NULL, NULL);

    if(!window) {
        glfwTerminate();
        cerr << "GLFW create window failed" << endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if(err != GLEW_OK) {
        cerr << glewGetErrorString(err) << endl;
        return false;
    }

    glfwSetWindowSizeCallback(window, handleResize);
    glfwSetKeyCallback(window, handleKeypress);

    return true;
}

void Engine::renderingThread() {
    glClearColor(56.0/255, 101.0/255, 190.0/255, 1);

    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(fragHasChanged) {
            string fragSource;

            if(loadFromPath(fragShaderPath, &fragSource)) {
                shader.detach(GL_FRAGMENT_SHADER | GL_VERTEX_SHADER);
                shader.build(fragSource, vertexShader);
                fragHasChanged = false;
            }
        }

        render();
        ScreenLog::Instance().render(true);

        glfwPollEvents();
    }

    glfwTerminate();
}

void Engine::watchingThread() {
    char s[1024];
    realpath(fragShaderPath.c_str(), s);

    string absolutePath(s);

    std::cout << "Watching fragment file source: " << s << std::endl;
    watcher = FileWatcher(absolutePath, &watcherCallback);
    watcher.startWatching();
}
