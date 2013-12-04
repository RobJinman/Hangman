// This file is part of Hangmuž.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangmuž is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangmuž is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangmuž.  If not, see <http://www.gnu.org/licenses/>.

#include <cassert>
#include "TextHangman.hpp"
#include "TextDisplay.hpp"


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
    default: assert(false);
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
