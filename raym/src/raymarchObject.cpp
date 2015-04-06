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

RaymarchAggregate::RaymarchAggregate(std::string _symbol) : RaymarchObject(_symbol, "") {}

RaymarchObject RaymarchObject::operation(const std::string& op, RaymarchObject _object) {
    RaymarchObject tmp = RaymarchAggregate("tmp_" + op);
    tmp.m_symbol += std::to_string(tmp.m_id);
    tmp.m_operations.push({ op,
        std::make_shared<RaymarchObject>(*this),
        std::make_shared<RaymarchObject>(_object)
    });
    return tmp;
}

void RaymarchObject::assign(RaymarchObject _other) {
    m_operations.push({ "assign",
        std::make_shared<RaymarchObject>(*this),
        std::make_shared<RaymarchObject>(_other)
    });
}

RaymarchObject RaymarchObject::operator+(RaymarchObject _object) {
    return operation("union", _object);
}

RaymarchObject RaymarchObject::operator-(RaymarchObject _object) {
    return operation("minus", _object);
}

RaymarchObject RaymarchObject::operator/(RaymarchObject _object) {
    return operation("intersect", _object);
}

std::string RaymarchAggregate::resolve() const {
    
}
