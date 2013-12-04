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

#ifndef __QT_HANGMAN_HPP__
#define __QT_HANGMAN_HPP__


#include <QWidget>
#include <QPainter>
#include <memory>
#include "Hangman.hpp"
#include "Strings.hpp"


class QtHangman : public QWidget {
  Q_OBJECT

  public:
    QtHangman(QWidget* parent = 0);

    void update(const Hangman& hangman, const utf8string_t& message);

    virtual ~QtHangman() {}

  private:
    void paintEvent(QPaintEvent* event);
    void drawState0(QPainter& painter);
    void drawState1(QPainter& painter);
    void drawState2(QPainter& painter);
    void drawState3(QPainter& painter);
    void drawState4(QPainter& painter);
    void drawState5(QPainter& painter);
    void drawState6(QPainter& painter);
    void drawState7(QPainter& painter);
    void drawState8(QPainter& painter);
    void drawState9(QPainter& painter);
    void drawState10(QPainter& painter);
    void drawState11(QPainter& painter);
    void drawMessage(QPainter& painter);

    Hangman m_hangman;
    utf8string_t m_message;

    std::unique_ptr<QFont> m_font;

    float m_x;
    float m_y;
    float m_w;
    float m_h;
};


#endif
