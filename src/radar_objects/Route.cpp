#include "Route.hpp"

#include "../util.hpp"

double Route::altitude() const {
    ASSERT(!m_checkpoints.empty());
    return m_checkpoints.front().altitude();
}

double Route::velocity() const {
    ASSERT(!m_checkpoints.empty());
    return m_checkpoints.front().velocity();
}

RealPosition Route::target() const {
    ASSERT(!m_checkpoints.empty());
    return m_checkpoints.front().point();
};

bool Route::advance_checkpoint() {
    ASSERT(!m_checkpoints.empty());
    m_checkpoints.erase(m_checkpoints.cbegin());
    return !m_checkpoints.empty();
};
