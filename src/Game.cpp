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

#include <cstring>
#include "Game.hpp"
#include "TextUi.hpp"
#include "QtUi.hpp"
#include "Exception.hpp"


enum UiType_t { TEXT, QT };


//===========================================
// Game::Launch
//===========================================
int Game::launch(int argc, char** argv) {
  UiType_t uiType = QT;

  for (int i = 0; i < argc; ++i) {
    if (strncmp("-ui=", argv[i], 4) == 0) {
      if (strcmp(&argv[i][4], "text") == 0) {
        uiType = TEXT;
      }
    }
  }

  switch (uiType) {
    case TEXT:  m_ui = pGameUi_t(new TextUi(argc, argv)); break;
    case QT:    m_ui = pGameUi_t(new QtUi(argc, argv));   break;
    default:    EXCEPTION("Error constructing game UI; No such UI type");
  }

  return m_ui->start();
}
