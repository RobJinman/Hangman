#include <stdexcept>
#include <iostream>
#include "AsciiDisplay.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// AsciiDisplay::AsciiDisplay
//===========================================
AsciiDisplay::AsciiDisplay(int w, int h) {
  m_w = w;
  m_h = h;

  m_pixels = new char*[w];

  for (int i = 0; i < w; ++i)
    m_pixels[i] = new char[h];
}

//===========================================
// AsciiDisplay::putChar
//===========================================
void AsciiDisplay::putChar(char c, int x, int y) {
  if (x >= m_w || y >= m_h)
    ERROR("Error putting char; Coords out of range");

  m_pixels[x][y] = c;
}

//===========================================
// AsciiDisplay::putChars
//===========================================
void AsciiDisplay::putChars(const std::string& str, int x, int y) {
  for (int i = 0; i < str.length(); ++i) {
    if (x + i >= m_w) break;

    putChar(str.data()[i], x + i, y);
  }
}

//===========================================
// AsciiDisplay::flush
//===========================================
void AsciiDisplay::flush() {
  for (int j = 0; j < m_h; ++j) {
    for (int i = 0; i < m_w; ++i) {
      cout << m_pixels[i][j];
    }
    cout << "\n";
  }
}

//===========================================
// AsciiDisplay::clear
//===========================================
void AsciiDisplay::clear(char c) {
  for (int j = 0; j < m_h; ++j) {
    for (int i = 0; i < m_w; ++i) {
      m_pixels[i][j] = c;
    }
  }
}
