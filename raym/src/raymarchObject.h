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

class RaymarchAggregate : public RaymarchObject {
public:
    RaymarchAggregate(std::string _symbol);

    RaymarchObject& operator+(const RaymarchObject& _object);
    RaymarchObject& operator-(const RaymarchObject& _object);
    RaymarchObject& operator/(const RaymarchObject& _object);

    std::string resolve() const;

};

class RaymarchSphere : public RaymarchObject {

public:
    RaymarchSphere(std::string _symbol, std::string _pos, std::string _radius);
    std::map<std::string, std::string> components() const override;

protected:
    std::string m_radius;

    static std::string s_distanceFunction;
};

class RaymarchCube : public RaymarchObject {

public:
    RaymarchCube(std::string _symbol, std::string _pos, std::string _dim);
    std::map<std::string, std::string> components() const override;

protected:
    std::string m_dimension;

    static std::string s_distanceFunction;
};

