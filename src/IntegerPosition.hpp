#pragma once

#include "Position.hpp"

class IntegerPosition : public Position<int> {
   public:
    IntegerPosition(int x, int y) : Position<int>(x, y) {}
};
