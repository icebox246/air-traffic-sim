#pragma once

#include <string>
#include <vector>

#include "../RealPosition.hpp"
#include "RouteCheckpoint.hpp"

class Route {
   private:
    std::vector<RouteCheckpoint> m_checkpoints;

   public:
    class EmptyCheckpointsListException {
        // This exception should never be
        // thrown if the code running methods
        // of this class is written properly
        // as we assume the user of this class
        // checks whether they can by run.
        //
        // Thus they need not be caught.
        //
        // The are here mostly for exception driven
        // development (if an exception is thrown,
        // one should change the code so that it isn't)
        std::string m_method;

       public:
        EmptyCheckpointsListException(std::string method) : m_method(method) {}
    };
    Route(std::vector<RouteCheckpoint> checkpoints)
        : m_checkpoints(std::move(checkpoints)) {}
    std::vector<RouteCheckpoint> const& checkpoints() const {
        return m_checkpoints;
    }
    double altitude() const noexcept(false);
    double velocity() const noexcept(false);
    RealPosition target() const noexcept(false);
    bool advance_checkpoint();
};
