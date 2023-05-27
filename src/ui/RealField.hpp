#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "TextField.hpp"

class RealField : protected TextField {
   public:
    RealField(int x, int y, int width, int height, size_t capacity)
        : TextField(x, y, width, height, capacity) {}
    double get_value() const { return std::atof(m_buffer.get()); }
    void set_value(double new_value) {
        std::string s = std::to_string(new_value);
        set_text(s);
    }
    virtual void process();
};
