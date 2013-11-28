#ifndef __ASCII_RENDERER_HPP__
#define __ASCII_RENDERER_HPP__


#include "StateRenderer.hpp"
#include "AsciiDisplay.hpp"


class AsciiRenderer : public StateRenderer {
  public:
    AsciiRenderer();

    virtual void draw(const GameState& state) const;
    virtual ~AsciiRenderer() {}

  private:
    mutable AsciiDisplay m_display;
};


#endif
