#pragma once

#include <creational/prototype.h>
#include <extensions/console.h>

using namespace cppe::pattern::creational;

class Monster : public prototype {};

class Bat : public Monster {
public:
    Monster* clone() override {
        return new Bat;
    }

    void method() override {
        cppe::io::console::output_line("I am Batman!");
    }
};

class Spider : public Monster {
public:
    Monster* clone() override {
        return new Spider;
    }

    void method() override {
        cppe::io::console::output_line("Your friendly neighborhood Spider-Man!");
    }
};
