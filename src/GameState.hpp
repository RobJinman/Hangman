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

#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__


#include <set>
#include <memory>
#include "Strings.hpp"
#include "Hangman.hpp"


// Should contain everything the renderer needs to know
// to render the scene.
class GameState {
  public:
    static const int WORD_SIZE_MAX = 64;

    KvpParser strings;

    std::set<uint32_t> availableLetters;

    ucs4string_t alphabet;
    std::vector<utf8string_t> categories;

    Hangman hangman;
    ucs4string_t word;
    ucs4string_t guess;
    int wordLen;
    int phraseLen; // includes spaces
    int nCorrect;
    utf8string_t message;
};


#endif
