#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__


#include <vector>
#include <memory>
#include <string>
#include "GameState.hpp"


class GameLogic {
  public:
    GameLogic();

    void start();
    bool processInput(char c);
    inline const GameState& getState() const;

  private:
    void populateWordList();
    void success();
    void endGame();

    std::vector<std::string> m_words;
    GameState m_state;
};

inline const GameState& GameLogic::getState() const {
  return m_state;
}


#endif
