#include <stdexcept>
#include <iostream>
#include "TextDisplay.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// TextDisplay::TextDisplay
//===========================================
TextDisplay::TextDisplay(int w, int h) {
  m_w = w;
  m_h = h;

  m_pixels = new uint32_t*[w];

  for (int i = 0; i < w; ++i)
    m_pixels[i] = new uint32_t[h];
}

//===========================================
// TextDisplay::putChar
//===========================================
void TextDisplay::putChar(uint32_t c, int x, int y) {
  if (x >= m_w || y >= m_h)
    ERROR("Error putting char; Coords out of range");

  m_pixels[x][y] = c;
}

//===========================================
// TextDisplay::putChars
//===========================================
void TextDisplay::putChars(const utf8string_t& str, int x, int y) {
  ucs4string_t ucs = utf8ToUcs4(str);

  for (int i = 0; i < static_cast<int>(ucs.length()); ++i) {
    if (x + i >= m_w) break;

    putChar(ucs.data()[i], x + i, y);
  }
}

//===========================================
// TextDisplay::flush
//===========================================
void TextDisplay::flush() {
  for (int j = 0; j < m_h; ++j) {
    for (int i = 0; i < m_w; ++i) {
      ucs4string_t ucs(&m_pixels[i][j], 1);
      utf8string_t utf = ucs4ToUtf8(ucs);

      cout << utf;
    }
    cout << "\n";
  }
}

//===========================================
// TextDisplay::clear
//===========================================
void TextDisplay::clear(uint32_t c) {
  for (int j = 0; j < m_h; ++j) {
    for (int i = 0; i < m_w; ++i) {
      m_pixels[i][j] = c;
    }
  }
}
