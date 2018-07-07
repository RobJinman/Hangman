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

#ifndef __QT_LETTERS_HPP__
#define __QT_LETTERS_HPP__


#include <QWidget>
#include <QPushButton>
#include <vector>
#include "Strings.hpp"


class QGridLayout;

class QtLetters : public QWidget {
  Q_OBJECT

  public:
    QtLetters(const ucs4string_t& alphabet, QWidget* parent = 0);

    void remake(const ucs4string_t& alphabet);

    void enable();
    void disable();

    virtual ~QtLetters();

  private slots:
    void onLetterClick(int id);

  signals:
    void letterClicked(int id);

  private:
    void destroy();

    QGridLayout* m_grid;
    std::vector<QPushButton*> m_letters;
    QButtonGroup* m_grpLetters;
};


#endif
