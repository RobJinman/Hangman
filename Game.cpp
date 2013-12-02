#include <cstring>
#include <stdexcept>
#include "Game.hpp"
#include "TextUi.hpp"
#include "QtUi.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


enum UiType_t { TEXT, QT };


//===========================================
// Game::Launch
//===========================================
int Game::launch(int argc, char** argv) {
  UiType_t uiType = TEXT;

  for (int i = 0; i < argc; ++i) {
    if (strncmp("-ui=", argv[i], 4) == 0) {
      if (strcmp(&argv[i][4], "qt") == 0) uiType = QT;
    }
  }

  switch (uiType) {
    case TEXT:  m_ui = pGameUi_t(new TextUi(argc, argv)); break;
    case QT:    m_ui = pGameUi_t(new QtUi(argc, argv));   break;
    default:    ERROR("Error constructing game UI; No such UI type");
  }

  return m_ui->start();
}
