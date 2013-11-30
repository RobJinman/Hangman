#ifndef __TEXT_DISPLAY_HPP__
#define __TEXT_DISPLAY_HPP__


#include "Strings.hpp"


class TextDisplay {
  public:
    TextDisplay(int w, int h);

    void putChar(uint32_t ucsChar, int x, int y);
    void putChars(const utf8string_t& str, int x, int y);
    void clear(uint32_t c);
    void flush();

  private:
    uint32_t** m_pixels;
    int m_w;
    int m_h;
};


#endif
