#ifndef __GAME_HPP__
#define __GAME_HPP__


#include <vector>
#include <memory>
#include <string>
#include "StateRenderer.hpp"
#include "GameState.hpp"


typedef std::unique_ptr<StateRenderer> pRenderer_t;


class Game {
  public:
    Game();
    void launch();

  private:
    void populateWordList();
    void gameLoop();
    void processInput(char c);
    void draw();
    void success();
    void endGame();

    std::vector<std::string> m_words;
    GameState m_state;
    pRenderer_t m_renderer;
};


#endif
