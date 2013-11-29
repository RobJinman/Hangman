#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__


#include <vector>
#include <memory>
#include <string>
#include <map>
#include "GameState.hpp"


typedef std::vector<std::string> wordList_t;
typedef std::unique_ptr<wordList_t> pWordList_t;


class GameLogic {
  public:
    GameLogic();

    void start(pWordList_t words);
    bool processInput(char c);
    inline const GameState& getState() const;

  private:
    void populateWordLists();
    void success();
    void endGame();

    pWordList_t m_words;

    GameState m_state;
};

inline const GameState& GameLogic::getState() const {
  return m_state;
}


#endif
