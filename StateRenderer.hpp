#ifndef __STATE_RENDERER_HPP__
#define __STATE_RENDERER_HPP__


class GameState;

// Encapsulates all knowledge of how the game state is to be rendered,
// even what type of display (ascii, opengl, etc.).
class StateRenderer {
  public:
    virtual void draw(const GameState& state) const = 0;
    virtual ~StateRenderer() {}
};


#endif
