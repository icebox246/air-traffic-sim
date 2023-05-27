#include "RealField.hpp"

#include "TextField.hpp"

void RealField::process() {
    char temp[m_buffer_size];
    memcpy(temp, m_buffer.get(), m_buffer_size);
    TextField::process();
    for (auto i = 0; i < m_buffer_size && m_buffer[i]; i++) {
        char c = m_buffer[i];
        if (c == '.' || (c >= '0' && c <= '9')) continue;
        memcpy(m_buffer.get(), temp, m_buffer_size);
        return;
    }
}
