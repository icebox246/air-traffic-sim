#pragma once

#include <functional>

template <typename... T>
class Signal {
   protected:
    std::function<void(T...)> m_callback;

   public:
    void connect(std::function<void(T...)> callback) { m_callback = callback; }

    void call(T... args) {
        if (m_callback) m_callback(args...);
    }
};
