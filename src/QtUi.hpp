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

#ifndef __QT_UI_HPP__
#define __QT_UI_HPP__


#include <memory>
#include "GameUi.hpp"


class QtUi : public GameUi {
  public:
    QtUi(int argc, char** argv);

    virtual int start();

    virtual ~QtUi() {}

  private:
    int m_argc;
    char** m_argv;
};


#endif
