#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__


#include <set>
#include <memory>
#include "Strings.hpp"
#include "Hangman.hpp"
#include "KvpParser.hpp"


// Should contain everything the renderer needs to know
// to render the scene.
class GameState {
  public:
    static const int WORD_SIZE_MAX = 64;

    KvpParser strings;

    std::set<uint32_t> availableLetters;

    Hangman hangman;
    ucs4string_t word;
    ucs4string_t guess;
    int wordLen;
    int phraseLen; // includes spaces
    int nCorrect;
    utf8string_t message;
};


#endif
