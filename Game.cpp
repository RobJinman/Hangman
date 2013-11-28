#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include "Game.hpp"
#include "AsciiRenderer.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// Game::Game
//===========================================
Game::Game() {
  m_state.nCorrect = 0;

  m_renderer = pRenderer_t(new AsciiRenderer);

  memset(m_state.word, 0, GameState::WORD_SIZE_MAX);
  memset(m_state.guess, 0, GameState::WORD_SIZE_MAX);

  populateWordList();

  for (char c = 'a'; c <= 'z'; ++c)
    m_state.availableLetters.insert(c);

  srand(time(NULL));
  int r = rand() % m_words.size();
  const string& w = m_words[r];
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

  if (l > GameState::WORD_SIZE_MAX)
    ERROR("Error initialising game; Word longer than WORD_SIZE_MAX");

  m_state.phraseLen = l;
  m_state.wordLen = l - nSpaces;

  memcpy(m_state.word, w.data(), l);
}

//===========================================
// Game::populateWordList
//===========================================
void Game::populateWordList() {
  m_words.push_back("pumpkin");
  m_words.push_back("susan boyle");
  m_words.push_back("lemon pie");
  m_words.push_back("dinosaur");
  m_words.push_back("frenchman");
}

//===========================================
// Game::processInput
//===========================================
void Game::processInput(char c) {
  if (m_state.availableLetters.find(c) == m_state.availableLetters.end()) {
    m_state.message = "Letter already used";
    return;
  }

  m_state.availableLetters.erase(c);

  bool b = false;

  for (int i = 0; i < m_state.phraseLen; ++i) {
    if (c == m_state.word[i]) {
      m_state.guess[i] = c;
      ++m_state.nCorrect;

      b = true;
    }
  }

  if (!b) m_state.hangman.advance();
}

//===========================================
// Game::launch
//===========================================
void Game::launch() {
  draw();
  gameLoop();
}

//===========================================
// Game::gameLoop
//===========================================
void Game::gameLoop() {
  while (1) {
    m_state.message = "";

    char c;
    cin >> c;

    processInput(c);

    if (m_state.nCorrect == m_state.wordLen) {
      success();
      draw();
      break;
    }

    if (m_state.hangman.isComplete()) {
      endGame();
      draw();
      break;
    }

    draw();
  }
}

//===========================================
// Game::draw
//===========================================
void Game::draw() {
  m_renderer->draw(m_state);
}

//===========================================
// Game::Success
//===========================================
void Game::success() {
  m_state.message = "Success!";
}

//===========================================
// Game::endGame
//===========================================
void Game::endGame() {
  memcpy(m_state.guess, m_state.word, m_state.phraseLen);
  m_state.message = "Failed";
}
