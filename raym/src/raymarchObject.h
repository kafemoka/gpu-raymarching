#pragma once

#include <string>
#include <map>
#include <queue>

class RaymarchObject;

struct Operation {
    std::string m_kind;
    std::shared_ptr<RaymarchObject> m_first;
    std::shared_ptr<RaymarchObject> m_second;
};

class RaymarchObject {

public:
    RaymarchObject(std::string _symbol, std::string _position);

    virtual std::map<std::string, std::string> components() const;

    long getId() { return m_id; }
    std::string getSymbol() { return m_symbol; }

    RaymarchObject operator+(RaymarchObject _object);
    RaymarchObject operator-(RaymarchObject _object);
    RaymarchObject operator/(RaymarchObject _object);
    void assign(RaymarchObject _other);

    std::queue<Operation> getOperations() {
        return m_operations;
    }

protected:
    static long nextId() { return s_id++; }

    std::string m_symbol;
    std::string m_position;
    long m_id;

    static long s_id;

private:
    RaymarchObject operation(const std::string& op, RaymarchObject _object);
    std::queue<Operation> m_operations;
};

class RaymarchAggregate : public RaymarchObject {
public:
    RaymarchAggregate(std::string _symbol);

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

