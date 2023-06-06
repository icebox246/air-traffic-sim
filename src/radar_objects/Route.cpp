#include "Route.hpp"

#include "../util.hpp"

double Route::altitude() const {
    if (m_checkpoints.empty()) throw EmptyCheckpointsListException("altitude");
    return m_checkpoints.front().altitude();
}

double Route::velocity() const {
    if (m_checkpoints.empty()) throw EmptyCheckpointsListException("velocity");
    return m_checkpoints.front().velocity();
}

RealPosition Route::target() const {
    if (m_checkpoints.empty()) throw EmptyCheckpointsListException("target");
    return m_checkpoints.front().point();
};

bool Route::advance_checkpoint() {
    if (m_checkpoints.empty())
        throw EmptyCheckpointsListException("advance_checkpoint");
    m_checkpoints.erase(m_checkpoints.cbegin());
    return !m_checkpoints.empty();
};
