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

#ifndef __TEXT_HANGMAN_HPP__
#define __TEXT_HANGMAN_HPP__


#include "Hangman.hpp"


class TextDisplay;

class TextHangman {
  public:
    TextHangman(const Hangman& hangman, int x, int y);

    void draw(TextDisplay& display) const;

  private:
    void drawState(int state, TextDisplay& display) const;
    void drawState0(TextDisplay& display) const;
    void drawState1(TextDisplay& display) const;
    void drawState2(TextDisplay& display) const;
    void drawState3(TextDisplay& display) const;
    void drawState4(TextDisplay& display) const;
    void drawState5(TextDisplay& display) const;
    void drawState6(TextDisplay& display) const;
    void drawState7(TextDisplay& display) const;
    void drawState8(TextDisplay& display) const;
    void drawState9(TextDisplay& display) const;
    void drawState10(TextDisplay& display) const;
    void drawState11(TextDisplay& display) const;

    Hangman m_hangman;
    int m_x;
    int m_y;
};


#endif
