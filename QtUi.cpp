#include <cstring>
#include <QApplication>
#include <QTextCodec>
#include "QtUi.hpp"
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

  QApplication app(m_argc, m_argv);  
  QtGameWindow window(opts);
  window.show();

  return app.exec();
}
