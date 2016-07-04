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

#include "Exception.hpp"
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
