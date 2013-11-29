#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <ctime>
#include "GameLogic.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// GameLogic::GameLogic
//===========================================
GameLogic::GameLogic() {}

//===========================================
// GameLogic::processInput
//===========================================
bool GameLogic::processInput(char c) {
  m_state.message = "";

  if (m_state.availableLetters.find(c) == m_state.availableLetters.end()) {
    m_state.message = "Letter already used";
    return false;
  }

  m_state.availableLetters.erase(c);

  bool b = false;

  for (int i = 0; i < m_state.phraseLen; ++i) {
    if (tolower(c) == tolower(m_state.word[i])) {
      m_state.guess[i] = m_state.word[i];
      ++m_state.nCorrect;

      b = true;
    }
  }

  if (!b) m_state.hangman.advance();

  if (m_state.nCorrect == m_state.wordLen) {
    success();
    return true;
  }

  if (m_state.hangman.isComplete()) {
    endGame();
    return true;
  }

  return false;
}

//===========================================
// GameLogic::start
//===========================================
void GameLogic::start(pWordList_t words) {
  m_words = move(words);
  m_state.nCorrect = 0;

  memset(m_state.word, 0, GameState::WORD_SIZE_MAX);
  memset(m_state.guess, 0, GameState::WORD_SIZE_MAX);

  for (char c = 'a'; c <= 'z'; ++c)
    m_state.availableLetters.insert(c);

  srand(time(NULL));
  int r = rand() % m_words->size();
  const string& w = (*m_words)[r];
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
// GameLogic::Success
//===========================================
void GameLogic::success() {
  m_state.message = "Success!";
}

//===========================================
// GameLogic::endGame
//===========================================
void GameLogic::endGame() {
  memcpy(m_state.guess, m_state.word, m_state.phraseLen);
  m_state.message = "Failed";
}
