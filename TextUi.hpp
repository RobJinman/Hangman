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

#ifndef __TEXT_UI_HPP__
#define __TEXT_UI_HPP__


#include <memory>
#include "GameUi.hpp"
#include "TextDisplay.hpp"
#include "KvpParser.hpp"
#include "GameLogic.hpp"


class TextUi : public GameUi {
  public:
    TextUi(int argc, char** argv);

    virtual int start();

    virtual ~TextUi() {}

  private:
    bool ioLoop();
    void draw() const;

    mutable TextDisplay m_display;
    std::unique_ptr<GameLogic> m_logic;
};


#endif
