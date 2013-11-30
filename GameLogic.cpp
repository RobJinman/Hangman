#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <sstream>
#include "GameLogic.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// GameLogic::GameLogic
//===========================================
GameLogic::GameLogic(const GameSettings& opts) {
  m_opts = opts;

  loadStrings();
}

//===========================================
// GameLogic::loadStrings
//===========================================
void GameLogic::loadStrings() {
  stringstream ss;
  ss << "./data/text/" + m_opts.language + "/strings.txt";

  utf8string_t path(ss.str());

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

      break;
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

    if (!b) m_state.hangman.advance();

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
void GameLogic::start(const ucs4string_t& alphabet, pWordList_t words) {
  m_words = move(words);
  m_state.nCorrect = 0;

  for (unsigned int i = 0; i < alphabet.length(); ++i)
    m_state.availableLetters.insert(alphabet[i]);

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

  if (l > GameState::WORD_SIZE_MAX)
    ERROR("Error initialising game; Word longer than WORD_SIZE_MAX");

  m_state.phraseLen = l;
  m_state.wordLen = l - nSpaces;

  m_state.word = w;
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
