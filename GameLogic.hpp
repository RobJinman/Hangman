#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__


#include <vector>
#include <memory>
#include <map>
#include "GameState.hpp"


typedef std::vector<utf8string_t> wordList_t;
typedef std::unique_ptr<wordList_t> pWordList_t;


class GameSettings {
  public:
    utf8string_t language;
};


class GameLogic {
  public:
    GameLogic(const GameSettings& opts);

    void start(const ucs4string_t& alphabet, pWordList_t words);
    bool processInput(const utf8string_t& chars);
    void reset();
    inline const GameState& getState() const;

  private:
    void success();
    void endGame();
    void loadStrings();

    GameSettings m_opts;
    pWordList_t m_words;
    GameState m_state;
};

inline const GameState& GameLogic::getState() const {
  return m_state;
}


#endif
