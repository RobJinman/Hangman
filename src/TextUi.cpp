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

#include <iostream>
#include <sstream>
#include <cstring>
#include "TextUi.hpp"
#include "TextHangman.hpp"
#include "GameState.hpp"


using namespace std;


//===========================================
// TextUi::TextUi
//===========================================
TextUi::TextUi(int argc, char** argv)
  : m_display(40, 14) {

  GameSettings opts;

  opts.language = "English";
  for (int i = 0; i < argc; ++i) {
    if (strncmp("-lang=", argv[i], 6) == 0) {
      opts.language = utf8string_t(&argv[i][6]);
    }
  }

  m_logic = std::unique_ptr<GameLogic>(new GameLogic(opts));
}

//===========================================
// TextUi::start
//===========================================
int TextUi::start() {
  const GameState& state = m_logic->getState();

  bool done = false;
  while (!done) {
    m_logic->reset();

    m_display.clear(' ');

    m_display.putChars("|--------------------------------------|", 0, 0);
    m_display.putChars("|                                      |", 0, 1);
    m_display.putChars("|--------------------------------------|", 0, 2);
    m_display.putChars("|                                      |", 0, 3);
    m_display.putChars("|                                      |", 0, 4);
    m_display.putChars("|                                      |", 0, 5);
    m_display.putChars("|                                      |", 0, 6);
    m_display.putChars("|                                      |", 0, 7);
    m_display.putChars("|                                      |", 0, 8);
    m_display.putChars("|                                      |", 0, 9);
    m_display.putChars("|                                      |", 0, 10);
    m_display.putChars("|                                      |", 0, 11);
    m_display.putChars("|--------------------------------------|", 0, 12);

    utf8string_t title = state.strings.getValue("title");
    m_display.putChars(title, 2, 1);

    utf8string_t cat = state.strings.getValue("categorysub");
    m_display.putChars(cat, 2, 3);

    const vector<utf8string_t>& categories = state.categories;
    for (unsigned int i = 0; i < categories.size(); ++i) {
      stringstream ss;
      ss << i << ": " << categories[i];

      m_display.putChars(ss.str(), 2, 5 + i);
    }

    m_display.flush();

    stringstream ss;
    char buf[64];
    unsigned int c = 999;
    while (1) {
      memset(buf, 0, 64);

      cin.getline(buf, 64, '\n');
      ss.str("");
      ss.clear();

      ss << buf;
      ss >> c;

      if (!ss.fail() && c < categories.size()) {
        break;
      }

      utf8string_t badcat = state.strings.getValue("badcategory");
      m_display.putChars(badcat, 2, 11);

      m_display.flush();
    }

    m_logic->start(categories[c]);
    draw();

    done = ioLoop();
  }

  return EXIT_SUCCESS;
}

//===========================================
// TextUi::ioLoop
//===========================================
bool TextUi::ioLoop() {
  const GameState& state = m_logic->getState();

  bool done = false;

  while (!done) {
    char buf[64];
    memset(buf, 0, 64);

    cin.getline(buf, 64, '\n');

    utf8string_t str(buf);

    done = m_logic->processInput(str);

    draw();
  }

  utf8string_t strReplay = state.strings.getValue("replayprompt");
  m_display.putChars(strReplay, 0, 13);

  m_display.flush();

  utf8string_t y = state.strings.getValue("yeskey");

  char buf[8];
  memset(buf, 0, 8);

  cin.getline(buf, 8, '\n');

  utf8string_t ans(buf);

  return ans.compare(y) != 0;
}

//===========================================
// TextUi::draw
//===========================================
void TextUi::draw() const {
  const GameState& state = m_logic->getState();

  m_display.clear(' ');

  m_display.putChars("|--------------------------------------|", 0, 0);
  m_display.putChars("|                                      |", 0, 1);
  m_display.putChars("|--------------------------------------|", 0, 2);
  m_display.putChars("|                                      |", 0, 3);
  m_display.putChars("|                                      |", 0, 4);
  m_display.putChars("|                                      |", 0, 5);
  m_display.putChars("|                                      |", 0, 6);
  m_display.putChars("|                                      |", 0, 7);
  m_display.putChars("|                                      |", 0, 8);
  m_display.putChars("|                                      |", 0, 9);
  m_display.putChars("|                                      |", 0, 10);
  m_display.putChars("|                                      |", 0, 11);
  m_display.putChars("|--------------------------------------|", 0, 12);

  utf8string_t title = state.strings.getValue("title");
  m_display.putChars(title, 2, 1);

  m_display.putChars(state.message, 2, 11);

  for (int i = 0; i < state.phraseLen; ++i) {
    m_display.putChar(state.guess[i], 2 + i * 2, 10);
  }

  TextHangman hangman(state.hangman, 3, 3);
  hangman.draw(m_display);

  for (unsigned int c = 0; c < state.alphabet.length(); ++c) {
    int x = 23;
    int y = 4;

    int i = x + ((c * 2) % 10);
    int j = y + c / 5;

    uint32_t l = state.alphabet[c];

    if (state.availableLetters.find(l) != state.availableLetters.end()) {
      ucs4string_t ucs(&l, 1);
      utf8string_t utf = ucs4ToUtf8(ucs);

      m_display.putChars(utf, i, j);
    }
    else {
      m_display.putChar(' ', i, j);
    }
  }

  m_display.flush();
}
