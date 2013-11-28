#include <cstring>
#include <stdexcept>
#include "Game.hpp"
#include "AsciiUi.hpp"
//#include "QtUi.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


enum UiType_t { ASCII, QT };


void Game::launch(int argc, char** argv) {
  UiType_t uiType = ASCII;

  if (argc > 1) {
    for (int i = 0; i < argc; ++i) {
      if (strcmp(argv[i], "qt") == 0) uiType = QT;
    }
  }

  switch (uiType) {
    case ASCII: m_ui = pGameUi_t(new AsciiUi); break;
//    case QT:    m_ui = pGameUi_t(new QtUi);    break;
    default:    ERROR("Error constructing game UI; No such UI type");
  }

  m_ui->start();
}
