#ifndef __ASCII_UI_HPP__
#define __ASCII_UI_HPP__


#include "GameUi.hpp"
#include "AsciiDisplay.hpp"
#include "GameLogic.hpp"


class AsciiUi : public GameUi {
  public:
    AsciiUi();

    virtual void start();

    virtual ~AsciiUi() {}

  private:
    void ioLoop();
    void draw() const;

    mutable AsciiDisplay m_display;
    GameLogic m_logic;
};


#endif
