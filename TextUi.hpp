#ifndef __TEXT_UI_HPP__
#define __TEXT_UI_HPP__


#include <memory>
#include "GameUi.hpp"
#include "TextDisplay.hpp"
#include "KvpParser.hpp"
#include "GameLogic.hpp"


class TextUi : public GameUi {
  public:
    TextUi(int argc, char** argv);

    virtual int start();

    virtual ~TextUi() {}

  private:
    bool ioLoop();
    void draw() const;

    mutable TextDisplay m_display;
    std::unique_ptr<GameLogic> m_logic;
};


#endif
