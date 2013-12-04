// This file is part of Hangmuž.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangmuž is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangmuž is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangmuž.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __HANG_MAN_HPP__
#define __HANG_MAN_HPP__


class Hangman {
  public:
    Hangman();

    void advance();
    void reset();
    bool isComplete() const;

    inline int getState() const;
    inline int lastState() const;

  private:
    int m_state;
    int m_lastState;
};

inline int Hangman::getState() const {
  return m_state;
}

inline int Hangman::lastState() const {
  return m_lastState;
}


#endif
