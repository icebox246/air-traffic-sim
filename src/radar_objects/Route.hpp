#pragma once

#include <vector>

#include "../RealPosition.hpp"
#include "RouteCheckpoint.hpp"

class Route {
   private:
    std::vector<RouteCheckpoint> m_checkpoints;

   public:
    Route(std::vector<RouteCheckpoint> checkpoints)
        : m_checkpoints(std::move(checkpoints)) {}
    std::vector<RouteCheckpoint> const& checkpoints() const {
        return m_checkpoints;
    }
    double altitude() const;
    double velocity() const;
    RealPosition target() const;
    bool advance_checkpoint();
};
