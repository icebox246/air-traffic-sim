#pragma once

#include <functional>

template <typename rT, typename... aTs>
class Signal {
   protected:
    std::function<rT(aTs...)> m_callback;

   public:
    void connect(std::function<rT(aTs...)> callback) { m_callback = callback; }

    void call(aTs... args) {
        if (m_callback) m_callback(args...);
    }
};
