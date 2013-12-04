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

#include <cstring>
#include <QTextCodec>
#include "QtUi.hpp"
#include "QtApplication.hpp"
#include "QtGameWindow.hpp"


using namespace std;


//===========================================
// QtUi::QtUi
//===========================================
QtUi::QtUi(int argc, char** argv) {
  m_argc = argc;
  m_argv = argv;

  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
}

//===========================================
// QtUi::start
//===========================================
int QtUi::start() {
  GameSettings opts;

  opts.language = "English";
  for (int i = 0; i < m_argc; ++i) {
    if (strncmp("-lang=", m_argv[i], 6) == 0) {
      opts.language = utf8string_t(&m_argv[i][6]);
    }
  }

  QtApplication app(m_argc, m_argv);  
  QtGameWindow window(opts);
  window.show();

  return app.exec();
}
