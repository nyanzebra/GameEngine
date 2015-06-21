#pragma once

#include <string>
#include <creational/factory.h>

using namespace cppe::pattern::creational;

class Base {
public:
    Base(const std::string& s) : argc(s) {}
    virtual std::string print() const {
        return "Base: " + argc;
    }
protected:
    std::string argc;
};
class Derived_0 : public Base {
public:
    Derived_0(const std::string& s) : Base(s) {}
    virtual std::string print() const {
        return "Derived_0: " + argc;
    }
};
class Derived_1 : public Base {
public:
    Derived_1(const std::string& s) : Base(s) {}
    virtual std::string print() const {
        return "Derived_1: " + argc;
    }
};
