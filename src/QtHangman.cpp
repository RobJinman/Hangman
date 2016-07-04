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

#include <cassert>
#include "QtHangman.hpp"


using namespace std;


//===========================================
// QtHangman::QtHangman
//===========================================
QtHangman::QtHangman(QWidget* parent)
  : QWidget(parent) {

  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

  m_font = unique_ptr<QFont>(new QFont("Courier", 15, QFont::DemiBold));

  m_x = 20;
  m_y = 20;
  m_w = 100;
  m_h = 100;
}

//===========================================
// QtHangman::update
//===========================================
void QtHangman::update(const Hangman& hangman, const utf8string_t& message) {
  m_hangman = hangman;
  m_message = message;
}

//===========================================
// QtHangman::paintEvent
//===========================================
void QtHangman::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setFont(*m_font);

  Qt::PenStyle style = Qt::PenStyle(Qt::SolidLine);
  Qt::PenCapStyle cap = Qt::PenCapStyle(Qt::SquareCap);
  Qt::PenJoinStyle join = Qt::PenJoinStyle(Qt::RoundJoin);

  QPen pen(Qt::black, 2, style, cap, join);
  QBrush brush(Qt::transparent);

  painter.setPen(pen);
  painter.setBrush(brush);

  switch (m_hangman.getState()) {
    case 0: drawState0(painter); break;
    case 1: drawState1(painter); break;
    case 2: drawState2(painter); break;
    case 3: drawState3(painter); break;
    case 4: drawState4(painter); break;
    case 5: drawState5(painter); break;
    case 6: drawState6(painter); break;
    case 7: drawState7(painter); break;
    case 8: drawState8(painter); break;
    case 9: drawState9(painter); break;
    case 10: drawState10(painter); break;
    case 11: drawState11(painter); break;
    default: assert(false);
  }

  drawMessage(painter);
}

//===========================================
// QtHangman::drawMessage
//===========================================
void QtHangman::drawMessage(QPainter& painter) {
  painter.drawText(m_x, m_y + m_h + 32, m_message.data());
}

//===========================================
// QtHangman::drawState0...11

// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
void QtHangman::drawState0(QPainter& painter) {
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
void QtHangman::drawState1(QPainter& painter) {
  drawState0(painter);
  painter.setRenderHint(QPainter::Antialiasing, true);

  painter.drawLine(QPoint(m_x, m_y), QPoint(m_x, m_y + m_h));
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState2(QPainter& painter) {
  drawState1(painter);

  int w = m_w * 0.1;
  painter.drawLine(QPoint(m_x - w, m_y + m_h), QPoint(m_x + w, m_y + m_h));
}

// |   ________     |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState3(QPainter& painter) {
  drawState2(painter);

  int w = m_w * 0.8;
  painter.drawLine(QPoint(m_x, m_y), QPoint(m_x + w, m_y));
}

// |   ________     |
// |  |/            |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState4(QPainter& painter) {
  drawState3(painter);

  int w = m_w * 0.2;
  int h = m_h * 0.2;
  painter.drawLine(QPoint(m_x, m_y + h), QPoint(m_x + w, m_y));
}

// |   ________     |
// |  |/       |    |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState5(QPainter& painter) {
  drawState4(painter);

  int w = m_w * 0.8;
  int h = m_h * 0.2;
  painter.drawLine(QPoint(m_x + w, m_y), QPoint(m_x + w, m_y + h));
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState6(QPainter& painter) {
  drawState5(painter);

  int w = m_w * 0.15;
  int h = m_h * 0.15;
  int x = m_x + m_w * 0.8 - w / 2;
  int y = m_y + m_h * 0.2;

  QRect rect(x, y, w, h);

  painter.drawEllipse(rect);
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |        |    |
// |  |             |
// | _|_            |
void QtHangman::drawState7(QPainter& painter) {
  drawState6(painter);

  int x = m_x + m_w * 0.8;
  int y = m_y + m_h * 0.35;
  int h = m_h * 0.2;
  painter.drawLine(QPoint(x, y), QPoint(x, y + h));
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|    |
// |  |             |
// | _|_            |
void QtHangman::drawState8(QPainter& painter) {
  drawState7(painter);

  int x1 = m_x + m_w * 0.8;
  int y1 = m_y + m_h * 0.37;
  int x2 = x1 - m_w * 0.1;
  int y2 = y1 + m_h * 0.16;
  painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |             |
// | _|_            |
void QtHangman::drawState9(QPainter& painter) {
  drawState8(painter);

  int x1 = m_x + m_w * 0.8;
  int y1 = m_y + m_h * 0.37;
  int x2 = x1 + m_w * 0.1;
  int y2 = y1 + m_h * 0.16;
  painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       /     |
// | _|_            |
void QtHangman::drawState10(QPainter& painter) {
  drawState9(painter);

  int x1 = m_x + m_w * 0.8;
  int y1 = m_y + m_h * 0.55;
  int x2 = x1 - m_w * 0.1;
  int y2 = y1 + m_h * 0.2;
  painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       / \   |
// | _|_            |
void QtHangman::drawState11(QPainter& painter) {
  drawState10(painter);

  int x1 = m_x + m_w * 0.8;
  int y1 = m_y + m_h * 0.55;
  int x2 = x1 + m_w * 0.1;
  int y2 = y1 + m_h * 0.2;
  painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
}
//===========================================
