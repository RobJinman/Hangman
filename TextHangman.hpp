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
