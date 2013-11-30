#include <stdexcept>
#include "TextHangman.hpp"
#include "TextDisplay.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


const int LAST_STATE = 11;


//===========================================
// TextHangman::TextHangman
//===========================================
TextHangman::TextHangman(const Hangman& hangman, int x, int y)
  : m_hangman(hangman), m_x(x), m_y(y) {}

//===========================================
// TextHangman::draw
//===========================================
void TextHangman::draw(TextDisplay& display) const {
  drawState(m_hangman.getState(), display);
}

//===========================================
// TextHangman::drawState
//===========================================
void TextHangman::drawState(int state, TextDisplay& display) const {
  switch (state) {
    case 0: drawState0(display); break;
    case 1: drawState1(display); break;
    case 2: drawState2(display); break;
    case 3: drawState3(display); break;
    case 4: drawState4(display); break;
    case 5: drawState5(display); break;
    case 6: drawState6(display); break;
    case 7: drawState7(display); break;
    case 8: drawState8(display); break;
    case 9: drawState9(display); break;
    case 10: drawState10(display); break;
    case 11: drawState11(display); break;
    default: ERROR("Error drawing graphic; Unrecognised state");
  }
}

//===========================================
// TextHangman::drawState0...11

// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
void TextHangman::drawState0(TextDisplay& display) const {
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
void TextHangman::drawState1(TextDisplay& display) const {
  drawState0(display);

  display.putChar('|', m_x + 2, m_y + 1);
  display.putChar('|', m_x + 2, m_y + 2);
  display.putChar('|', m_x + 2, m_y + 3);
  display.putChar('|', m_x + 2, m_y + 4);
  display.putChar('|', m_x + 2, m_y + 5);
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void TextHangman::drawState2(TextDisplay& display) const {
  drawState1(display);

  display.putChar('_', m_x + 1, m_y + 5);
  display.putChar('_', m_x + 3, m_y + 5);
}

// |   ________     |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void TextHangman::drawState3(TextDisplay& display) const {
  drawState2(display);

  display.putChars("________", m_x + 3, m_y + 0);
}

// |   ________     |
// |  |/            |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void TextHangman::drawState4(TextDisplay& display) const {
  drawState3(display);

  display.putChar('/', m_x + 3, m_y + 1);
}

// |   ________     |
// |  |/       |    |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void TextHangman::drawState5(TextDisplay& display) const {
  drawState4(display);

  display.putChar('|', m_x + 11, m_y + 1);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |             |
// |  |             |
// | _|_            |
void TextHangman::drawState6(TextDisplay& display) const {
  drawState5(display);

  display.putChar('O', m_x + 11, m_y + 2);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |        |    |
// |  |             |
// | _|_            |
void TextHangman::drawState7(TextDisplay& display) const {
  drawState6(display);

  display.putChar('|', m_x + 11, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|    |
// |  |             |
// | _|_            |
void TextHangman::drawState8(TextDisplay& display) const {
  drawState7(display);

  display.putChar('/', m_x + 10, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |             |
// | _|_            |
void TextHangman::drawState9(TextDisplay& display) const {
  drawState8(display);

  display.putChar('\\', m_x + 12, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       /     |
// | _|_            |
void TextHangman::drawState10(TextDisplay& display) const {
  drawState9(display);

  display.putChar('/', m_x + 10, m_y + 4);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       / \   |
// | _|_            |
void TextHangman::drawState11(TextDisplay& display) const {
  drawState10(display);

  display.putChar('\\', m_x + 12, m_y + 4);
}
//===========================================
