#pragma once

#include "glm/glm.hpp"

class Camera {

public:
    Camera(glm::vec3 _position, glm::vec3 _lookat);

private:
    glm::vec3 m_position;
    glm::vec3 m_lookat;

};
