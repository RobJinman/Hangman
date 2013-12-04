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

#include <QPainter>
#include "QtGuess.hpp"
#include "Exception.hpp"


using namespace std;


//===========================================
// QtGuess::QtGuess
//===========================================
QtGuess::QtGuess(QWidget* parent)
  : QWidget(parent) {

  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

  m_font = unique_ptr<QFont>(new QFont("Courier", 15, QFont::DemiBold));
  m_font->setLetterSpacing(QFont::AbsoluteSpacing, 2);
}

//===========================================
// QtGuess::update
//===========================================
void QtGuess::update(const ucs4string_t& guess) {
  m_guess = guess;
}

//===========================================
// QtGuess::paintEvent
//===========================================
void QtGuess::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setFont(*m_font);

  utf8string_t utf = ucs4ToUtf8(m_guess);

  painter.drawText(20, 40, utf.data());
}
