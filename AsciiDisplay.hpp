#ifndef __ASCII_DISPLAY_HPP__
#define __ASCII_DISPLAY_HPP__


#include <string>


class AsciiDisplay {
  public:
    AsciiDisplay(int w, int h);

    void putChar(char c, int x, int y);
    void putChars(const std::string& str, int x, int y);
    void clear(char c);
    void flush();

  private:
    char** m_pixels;
    int m_w;
    int m_h;
};


#endif
