// This file is part of Hangman.
//
// Copyright Rob Jinman 2013 <jinmanr@gmail.com>
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

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cstring>
#include "GameLogic.hpp"
#include "FileException.hpp"
#include "Utils.hpp"


using namespace std;


//===========================================
// GameLogic::GameLogic
//===========================================
GameLogic::GameLogic(const GameSettings& opts) {
  setSettings(opts);
}

//===========================================
// GameLogic::setSettings
//===========================================
void GameLogic::setSettings(const GameSettings& opts) {
  m_state = GameState();

  m_opts = opts;

  loadStrings();
  fetchCategories();
}

//===========================================
// GameLogic::loadStrings
//===========================================
void GameLogic::loadStrings() {
  stringstream ss;
  ss << utils::dataPath() << "/text/" << m_opts.language << "/strings.txt";

  utf8string_t path = utils::platformPath(ss.str());
  m_state.strings.parseFile(path);
}

//===========================================
// GameLogic::processInput
//===========================================
bool GameLogic::processInput(const utf8string_t& chars) {
  ucs4string_t ucs = utf8ToUcs4(chars);

  bool done = false;
  for (unsigned int j = 0; j < ucs.length(); ++j) {
    uint32_t c = ucs[j];

    m_state.message = "";

    if (m_state.availableLetters.find(c) == m_state.availableLetters.end()) {
      m_state.message = m_state.strings.getValue("letterrepeat");

      continue;
    }

    m_state.availableLetters.erase(c);

    bool b = false;

    for (int i = 0; i < m_state.phraseLen; ++i) {
      if (c == m_state.word[i]) {
        m_state.guess[i] = m_state.word[i];
        ++m_state.nCorrect;

        b = true;
      }
    }

    if (!b) {
      m_state.hangman.advance();
    }

    if (m_state.nCorrect == m_state.wordLen) {
      success();
      done = true;
      break;
    }

    if (m_state.hangman.isComplete()) {
      endGame();
      done = true;
      break;
    }
  }

  return done;
}

//===========================================
// GameLogic::start
//===========================================
void GameLogic::start(const utf8string_t& category) {
  fetchWords(category);

  m_state.nCorrect = 0;

  for (unsigned int i = 0; i < m_state.alphabet.length(); ++i) {
    m_state.availableLetters.insert(m_state.alphabet[i]);
  }

  srand(time(NULL));
  int r = rand() % m_words->size();

  const utf8string_t& utf_w = (*m_words)[r];
  ucs4string_t w = utf8ToUcs4(utf_w);

  m_state.guess.resize(GameState::WORD_SIZE_MAX, '\0');

  int l = w.length();

  int nSpaces = 0;
  for (int i = 0; i < l; ++i) {
    if (w.data()[i] == ' ') {
      ++nSpaces;
      m_state.guess[i] = ' ';
    }
    else {
      m_state.guess[i] = '_';
    }
  }

  if (l > GameState::WORD_SIZE_MAX) {
    EXCEPTION("Error initialising game; Word longer than WORD_SIZE_MAX");
  }

  m_state.phraseLen = l;
  m_state.wordLen = l - nSpaces;

  m_state.word = w;
}

//===========================================
// GameLogic::fetchWords
//===========================================
void GameLogic::fetchWords(const utf8string_t& cat) {
  utf8string_t file = m_categories.getValue(cat);

  stringstream ss;
  ss << utils::dataPath() << "/text/" << m_opts.language << "/wordlists/" << file;

  utf8string_t path = utils::platformPath(ss.str());

  ifstream fin(path);
  if (!fin.good()) {
    fin.close();
    FILE_EXCEPTION("Error loading word list; File not found", path);
  }

  char buf[512];
  memset(buf, 0, 512);

  fin.getline(buf, 512);
  utf8string_t utfAlpha(buf);
  m_state.alphabet = utf8ToUcs4(utfAlpha);

  m_words = pWordList_t(new wordList_t);

  while (!fin.eof()) {
    fin.getline(buf, 512);

    if (!fin.eof()) {
      m_words->push_back(utf8string_t(buf));
    }
  }

  fin.close();
}

//===========================================
// GameLogic::fetchCategories
//===========================================
void GameLogic::fetchCategories() {
  stringstream ss;
  ss << utils::dataPath() << "/text/" << m_opts.language << "/wordlists/index.txt";

  utf8string_t path = utils::platformPath(ss.str());

  m_categories.clear();
  m_categories.parseFile(path);

  for (auto c = m_categories.begin(); c != m_categories.end(); ++c) {
    m_state.categories.push_back(c->first);
  }
}

//===========================================
// GameLogic::Success
//===========================================
void GameLogic::success() {
  m_state.message = m_state.strings.getValue("success");
}

//===========================================
// GameLogic::endGame
//===========================================
void GameLogic::endGame() {
  m_state.guess = m_state.word;
  m_state.message = m_state.strings.getValue("failure");
}

//===========================================
// GameLogic::reset
//===========================================
void GameLogic::reset() {
  m_state.availableLetters.clear();
  m_state.hangman = Hangman();
  m_state.word.clear();
  m_state.guess.clear();
  m_state.wordLen = 0;
  m_state.phraseLen = 0;
  m_state.nCorrect = 0;
  m_state.message = "";
}
