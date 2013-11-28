#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__


#include <set>
#include <memory>
#include <string>
#include "Hangman.hpp"


// Should contain everything the renderer needs to know
// to render the scene.
class GameState {
  public:
    static const int WORD_SIZE_MAX = 64;

    std::set<char> availableLetters;

    Hangman hangman;
    char word[WORD_SIZE_MAX];
    char guess[WORD_SIZE_MAX];
    int wordLen;
    int phraseLen; // includes spaces
    int nCorrect;
    std::string message;
};


#endif
