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

#include <QGridLayout>
#include <QButtonGroup>
#include "QtLetters.hpp"


//===========================================
// QtLetters::QtLetters
//===========================================
QtLetters::QtLetters(const ucs4string_t& alphabet, QWidget* parent)
  : QWidget(parent), m_grpLetters(NULL) {

  m_grid = new QGridLayout;
  m_grid->setSpacing(2);

  setLayout(m_grid);

  remake(alphabet);
}

//===========================================
// QtLetters::remake
//===========================================
void QtLetters::remake(const ucs4string_t& alphabet) {
  destroy();

  m_grpLetters = new QButtonGroup;

  for (unsigned int i = 0; i < alphabet.length(); ++i) {
    int x = i / 5;
    int y = (i * 2) % 10;

    ucs4string_t ucsL(1, alphabet[i]);
    utf8string_t l = ucs4ToUtf8(ucsL);

    QPushButton* btn = new QPushButton(l.data(), this);
    btn->setMaximumWidth(32);
    btn->setMaximumHeight(32);

    m_letters.push_back(btn);

    m_grpLetters->addButton(btn, i);
    m_grid->addWidget(btn, x, y);
  }

  connect(m_grpLetters, SIGNAL(buttonClicked(int)), this, SLOT(onLetterClick(int)));
}

//===========================================
// QtLetters::destroy
//===========================================
void QtLetters::destroy() {
  m_grid->removeWidget(this);

  delete m_grpLetters;

  for (unsigned int i = 0; i < m_letters.size(); ++i) {
    m_grid->removeWidget(m_letters[i]);
    delete m_letters[i];
  }

  m_letters.clear();
}

//===========================================
// QtLetters::onLetterClick
//===========================================
void QtLetters::onLetterClick(int id) {
  m_letters[id]->setEnabled(false);

  emit letterClicked(id);
}

//===========================================
// QtLetters::enable
//===========================================
void QtLetters::enable() {
  for (unsigned int i = 0; i < m_letters.size(); ++i)
    m_letters[i]->setEnabled(true);
}

//===========================================
// QtLetters::disable
//===========================================
void QtLetters::disable() {
  for (unsigned int i = 0; i < m_letters.size(); ++i)
    m_letters[i]->setEnabled(false);
}

//===========================================
// QtLetters::~QtLetters
//===========================================
QtLetters::~QtLetters() {}
