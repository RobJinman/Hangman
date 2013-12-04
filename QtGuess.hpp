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

#ifndef __QT_GUESS_HPP__
#define __QT_GUESS_HPP__


#include <QWidget>
#include <memory>
#include "Strings.hpp"


class QtGuess : public QWidget {
  Q_OBJECT

  public:
    QtGuess(QWidget* parent = 0);

    void update(const ucs4string_t& guess);

    virtual ~QtGuess() {}

  private:
    void paintEvent(QPaintEvent* event);

    ucs4string_t m_guess;

    std::unique_ptr<QFont> m_font;
};


#endif
