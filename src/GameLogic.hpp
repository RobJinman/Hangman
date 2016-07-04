// This file is part of Hangman.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangman is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangman is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangman.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__


#include <vector>
#include <memory>
#include <map>
#include "KvpParser.hpp"
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

    void setSettings(const GameSettings& opts);
    void start(const utf8string_t& category);
    bool processInput(const utf8string_t& chars);
    void reset();
    inline const GameState& getState() const;

  private:
    void success();
    void endGame();
    void loadStrings();
    void fetchCategories();
    void fetchWords(const utf8string_t& cat);

    KvpParser m_categories;
    GameSettings m_opts;
    pWordList_t m_words;
    GameState m_state;
};

inline const GameState& GameLogic::getState() const {
  return m_state;
}


#endif
