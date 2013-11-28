#include <stdexcept>
#include "AsciiHangman.hpp"
#include "AsciiDisplay.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


const int LAST_STATE = 11;


//===========================================
// AsciiHangman::AsciiHangman
//===========================================
AsciiHangman::AsciiHangman(const Hangman& hangman, int x, int y)
  : m_hangman(hangman), m_x(x), m_y(y) {}

//===========================================
// AsciiHangman::draw
//===========================================
void AsciiHangman::draw(AsciiDisplay& display) const {
  drawState(m_hangman.getState(), display);
}

//===========================================
// AsciiHangman::drawState
//===========================================
void AsciiHangman::drawState(int state, AsciiDisplay& display) const {
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
// AsciiHangman::drawState0...11

// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
void AsciiHangman::drawState0(AsciiDisplay& display) const {
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
void AsciiHangman::drawState1(AsciiDisplay& display) const {
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
void AsciiHangman::drawState2(AsciiDisplay& display) const {
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
void AsciiHangman::drawState3(AsciiDisplay& display) const {
  drawState2(display);

  display.putChars("________", m_x + 3, m_y + 0);
}

// |   ________     |
// |  |/            |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void AsciiHangman::drawState4(AsciiDisplay& display) const {
  drawState3(display);

  display.putChar('/', m_x + 3, m_y + 1);
}

// |   ________     |
// |  |/       |    |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void AsciiHangman::drawState5(AsciiDisplay& display) const {
  drawState4(display);

  display.putChar('|', m_x + 11, m_y + 1);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |             |
// |  |             |
// | _|_            |
void AsciiHangman::drawState6(AsciiDisplay& display) const {
  drawState5(display);

  display.putChar('O', m_x + 11, m_y + 2);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |        |    |
// |  |             |
// | _|_            |
void AsciiHangman::drawState7(AsciiDisplay& display) const {
  drawState6(display);

  display.putChar('|', m_x + 11, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|    |
// |  |             |
// | _|_            |
void AsciiHangman::drawState8(AsciiDisplay& display) const {
  drawState7(display);

  display.putChar('/', m_x + 10, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |             |
// | _|_            |
void AsciiHangman::drawState9(AsciiDisplay& display) const {
  drawState8(display);

  display.putChar('\\', m_x + 12, m_y + 3);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       /     |
// | _|_            |
void AsciiHangman::drawState10(AsciiDisplay& display) const {
  drawState9(display);

  display.putChar('/', m_x + 10, m_y + 4);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       / \   |
// | _|_            |
void AsciiHangman::drawState11(AsciiDisplay& display) const {
  drawState10(display);

  display.putChar('\\', m_x + 12, m_y + 4);
}
//===========================================
