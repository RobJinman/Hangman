#include <stdexcept>
#include "Hangman.hpp"


const int LAST_STATE = 11;


//===========================================
// Hangman::Hangman
//===========================================
Hangman::Hangman()
  : m_state(0), m_lastState(LAST_STATE) {}

//===========================================
// Hangman::advance
//===========================================
void Hangman::advance() {
  ++m_state;
}

//===========================================
// Hangman::reset
//===========================================
void Hangman::reset() {
  m_state = 0;
}

//===========================================
// Hangman::isComplete
//===========================================
bool Hangman::isComplete() const {
  return m_state == m_lastState;
}
