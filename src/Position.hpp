#pragma once

template <typename T>
class Position {
   protected:
    T m_x, m_y;
    Position(T x, T y) {
        m_x = x;
        m_y = y;
    }

   public:
    T x() const { return m_x; }
    T y() const { return m_y; }
    Position<T> moved(T dx, T dy) { return {m_x + dx, m_y + dy}; }
};
