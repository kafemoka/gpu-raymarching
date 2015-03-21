#pragma once

#include <string>
#include <map>

class RaymarchObject {

public:
    RaymarchObject(std::string _symbol, std::string _position);

    virtual std::map<std::string, std::string> components() const;

    long getId() { return m_id; }

protected:
    static long nextId() { return s_id++; }

    std::string m_symbol;
    std::string m_position;
    long m_id;

    static long s_id;
};

class RaymarchSphere : public RaymarchObject {

public:
    RaymarchSphere(std::string _symbol, std::string _pos, std::string _radius);
    std::map<std::string, std::string> components() const override;

protected:
    std::string m_radius;

    static std::string s_distanceFunction;
};
