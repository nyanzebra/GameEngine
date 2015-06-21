#pragma once

#include <array>
#include <cstdarg>
#include <stdarg.h>

#include <creational/builder.h>
#include <extensions/console.h>

using namespace cppe::pattern::creational;
using namespace cppe::io;

struct Struct : Build_Object {
    int i = 0;
};

class builderExample : public builder {
public:
    builderExample() {
        test = true;
    }
    ~builderExample() = default;

    void build_strings(const char* args...) {
        va_list valist;
        va_start(valist, args);

        arg_0 = args;
        arg_1 = va_arg(valist, char*);
        arg_2 = va_arg(valist, char*);

        va_end(valist);
    }

    void build_string(const char* arg) override {
        arg_0 = arg;
    }

    void build_struct(const Build_Object* test_struct) override {
        my_struct.i = ((Struct*)test_struct)->i;
    }

    bool test = false;

    std::string arg_0 = "";
    std::string arg_1 = "";
    std::string arg_2 = "";

    Struct my_struct;
};
