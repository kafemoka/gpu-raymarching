#include <iostream>

#include "engine.h"
#include "utils.h"

static Engine* engine;

/*
 * Parent event signal handling
 */
void fileHasChanged(int sig) {
    if(sig == SIGALRM) {
        engine->fragmentHasChanged();
    }
}

/*
 * Event callback when file has changed
 */
void watcherCallback() {
    kill(engine->parentProcess, SIGALRM);
}

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

    int shmId = shmget(IPC_PRIVATE, sizeof(Engine), 0666);

    std::string fragShaderPath = std::string(argv[1]);

    pid_t parent = getpid();
    pid_t child = fork();

    // shared memory block
    engine = (Engine *) shmat(shmId, NULL, 0);

    // both will do
    engine->setFragShaderPath(fragShaderPath);
    engine->setChildProcess(child);
    engine->setParentProcess(parent);

    switch(child) {
        case -1: {
            shmctl(shmId, IPC_RMID, NULL);
            exit(-1);
        }

        case 0: {
            engine->watchingThread();
            break;
        }

        default: {
            if(engine->init()) {
                redefineSignal(SIGALRM, fileHasChanged);
                engine->renderingThread();
            }

            kill(child, SIGKILL);
        }
    }

    engine->destroy();

    // remove shared memory
    shmctl(shmId, IPC_RMID, NULL);

    return 0;
}
