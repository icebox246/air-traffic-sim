#pragma once

#include <functional>

template <typename rT, typename... aTs>
class Signal {
   protected:
    std::function<rT(aTs...)> m_callback;

   public:
    void connect(std::function<rT(aTs...)> callback) { m_callback = callback; }

    rT call(aTs... args) {
        if (m_callback)
            return m_callback(args...);
        else
            return {};
    }
};

template <typename... aTs>
class Signal<void, aTs...> {
   protected:
    std::function<void(aTs...)> m_callback;

   public:
    void connect(std::function<void(aTs...)> callback) {
        m_callback = callback;
    }

    void call(aTs... args) {
        if (m_callback) return m_callback(args...);
    }
};
