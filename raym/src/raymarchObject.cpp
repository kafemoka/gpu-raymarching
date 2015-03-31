#include "raymarchObject.h"

long RaymarchObject::s_id = 0;

RaymarchObject::RaymarchObject(std::string _symbol, std::string _position) :
    m_symbol("$_" + _symbol),
    m_position(_position)
{
    m_id = nextId();
}

std::map<std::string, std::string> RaymarchObject::components() const {
    std::map<std::string, std::string> components;
    components[m_symbol + "_pos"] = m_position;
    return components;
}

RaymarchSphere::RaymarchSphere(std::string _symbol, std::string _position, std::string _radius) :
    RaymarchObject(_symbol, _position),
    m_radius(_radius)
{}

std::map<std::string, std::string> RaymarchSphere::components() const {
    auto components = RaymarchObject::components();
    components[m_symbol + "_rad"] = m_radius;
    return components;
}

std::string RaymarchSphere::s_distanceFunction = R"END(
    float sdSphere(vec3 p, float s) {
        return length(p) - s;
    }
)END";

RaymarchCube::RaymarchCube(std::string _symbol, std::string _position, std::string _dimension) :
    RaymarchObject(_symbol, _position),
    m_dimension(_dimension)
{}

std::map<std::string, std::string> RaymarchCube::components() const {
    auto components = RaymarchObject::components();
    components[m_symbol + "_dim"] = m_dimension;
    return components;
}

std::string RaymarchCube::s_distanceFunction = R"END(
    float sdBox(vec3 p, vec3 b) {
        return length(max(abs(p) - b, 0.0));
    }
)END";

