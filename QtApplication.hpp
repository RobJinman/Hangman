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

#ifndef __QT_APPLICATION_HPP__
#define __QT_APPLICATION_HPP__


#include <QApplication>


class QtApplication : public QApplication {
  public:
    QtApplication(int argc, char** argv)
      : QApplication(argc, argv) {}

    virtual bool notify(QObject* receiver, QEvent* event);
};


#endif
