#pragma once

class Widget {
   private:
    bool m_visible = true;

   public:
    void set_visible(bool new_visible) { m_visible = new_visible; }
    bool visible() const { return m_visible; }
    virtual void process() = 0;
};
