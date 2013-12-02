#include "Strings.hpp"
#include "QtGameWindow.hpp"


using namespace std;


//===========================================
// QtGameWindow::QtGameWindow
//===========================================
QtGameWindow::QtGameWindow(const GameSettings& opts, QWidget* parent) {
  m_logic = std::unique_ptr<GameLogic>(new GameLogic(opts));

  resize(400, 300);

  const GameState& state = m_logic->getState();

  utf8string_t title = state.strings.getValue("title");
  setWindowTitle(title.data());
}

//===========================================
// QtGameWindow::~QtGameWindow
//===========================================
QtGameWindow::~QtGameWindow() {

}
