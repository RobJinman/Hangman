#ifndef __ASCII_HANGMAN_HPP__
#define __ASCII_HANGMAN_HPP__


#include "Hangman.hpp"


class AsciiDisplay;

class AsciiHangman {
  public:
    AsciiHangman(const Hangman& hangman, int x, int y);

    void draw(AsciiDisplay& display) const;

  private:
    void drawState(int state, AsciiDisplay& display) const;
    void drawState0(AsciiDisplay& display) const;
    void drawState1(AsciiDisplay& display) const;
    void drawState2(AsciiDisplay& display) const;
    void drawState3(AsciiDisplay& display) const;
    void drawState4(AsciiDisplay& display) const;
    void drawState5(AsciiDisplay& display) const;
    void drawState6(AsciiDisplay& display) const;
    void drawState7(AsciiDisplay& display) const;
    void drawState8(AsciiDisplay& display) const;
    void drawState9(AsciiDisplay& display) const;
    void drawState10(AsciiDisplay& display) const;
    void drawState11(AsciiDisplay& display) const;

    Hangman m_hangman;
    int m_x;
    int m_y;
};


#endif
