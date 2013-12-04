#include <stdexcept>
#include <fstream>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <cassert>
#include "Strings.hpp"
#include "QtGameWindow.hpp"
#include "QtLetters.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// QtGameWindow::QtGameWindow
//===========================================
QtGameWindow::QtGameWindow(const GameSettings& opts, QWidget* parent)
  : QMainWindow(parent), m_gameState(ST_IDLE) {

  getLanguages();

  resize(400, 300);

  m_logic = std::unique_ptr<GameLogic>(new GameLogic(opts));
  const GameState& state = m_logic->getState();

  m_category = 0;
  m_logic->start(state.categories[m_category]);
  m_gameState = ST_STARTED;

  utf8string_t strTitle = state.strings.getValue("title");
  utf8string_t strGame = state.strings.getValue("game");
  utf8string_t strNew = state.strings.getValue("new");
  utf8string_t strQuit = state.strings.getValue("quit");
  utf8string_t strCategory = state.strings.getValue("category");
  utf8string_t strLanguage = state.strings.getValue("language");
  utf8string_t strNewGame = state.strings.getValue("newgame");

  setWindowTitle(strTitle.data());

  m_actNew = pQAction_t(new QAction(strNew.data(), this));
  m_actQuit = pQAction_t(new QAction(strQuit.data(), this));

  m_mnuGame = pQMenu_t(menuBar()->addMenu(strGame.data()));
  m_mnuGame->addAction(m_actNew);
  m_mnuGame->addAction(m_actQuit);

  m_actGrpCategories = pQActionGroup_t(new QActionGroup(this));
  m_mnuCategory = pQMenu_t(menuBar()->addMenu(strCategory.data()));

  const vector<utf8string_t>& categories = state.categories;
  for (unsigned int i = 0; i < categories.size(); ++i) {

    pQAction_t cat(new QAction(categories[i].data(), this));
    cat->setActionGroup(m_actGrpCategories);
    cat->setCheckable(true);

    m_mnuCategory->addAction(cat);

    m_actCategories.push_back(std::move(cat));
  }

  m_actGrpLanguages = pQActionGroup_t(new QActionGroup(this));
  m_mnuLanguage = pQMenu_t(menuBar()->addMenu(strLanguage.data()));

  for (unsigned int i = 0; i < m_languages.size(); ++i) {
    pQAction_t lang(new QAction(m_languages[i].data(), this));
    lang->setActionGroup(m_actGrpLanguages);
    lang->setCheckable(true);

    m_mnuLanguage->addAction(lang);

    m_actLanguages.push_back(std::move(lang));
  }

  m_wgtCentral = pQWidget_t(new QWidget(this));
  setCentralWidget(m_wgtCentral);

  QHBoxLayout* hbox = new QHBoxLayout;

  QSizePolicy left(QSizePolicy::Preferred, QSizePolicy::Preferred);
  left.setHorizontalStretch(2);

  QSizePolicy right(QSizePolicy::Preferred, QSizePolicy::Preferred);
  right.setHorizontalStretch(1);

  QVBoxLayout* vboxl = new QVBoxLayout;
  QVBoxLayout* vboxr = new QVBoxLayout;

  QSizePolicy topleft(QSizePolicy::Preferred, QSizePolicy::Preferred);
  topleft.setVerticalStretch(2);
  topleft.setHorizontalStretch(2);

  QSizePolicy bottomleft(QSizePolicy::Preferred, QSizePolicy::Preferred);
  bottomleft.setVerticalStretch(1);
  bottomleft.setHorizontalStretch(2);

  m_wgtCentral->setLayout(hbox);

  m_wgtHangman = new QtHangman(m_wgtCentral);
  m_wgtHangman->setSizePolicy(topleft);

  m_wgtGuess = new QtGuess(m_wgtCentral);
  m_wgtGuess->setSizePolicy(bottomleft);

  m_wgtLetters = new QtLetters(m_logic->getState().alphabet, m_wgtCentral);
  m_wgtLetters->setSizePolicy(right);

  m_btnNew = pQPushButton_t(new QPushButton(strNewGame.data(), m_wgtCentral));
  vboxr->addWidget(m_btnNew);
  vboxr->addWidget(m_wgtLetters);

  vboxl->addWidget(m_wgtHangman);
  vboxl->addWidget(m_wgtGuess);

  hbox->addLayout(vboxl, 1);
  hbox->addLayout(vboxr, 1);

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtGuess->update(state.guess);

  connect(m_actNew, SIGNAL(triggered()), this, SLOT(restart()));
  connect(m_btnNew, SIGNAL(released()), this, SLOT(restart()));
  connect(m_actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(m_actGrpCategories, SIGNAL(triggered(QAction*)), this, SLOT(categoryChanged(QAction*)));
  connect(m_actGrpLanguages, SIGNAL(triggered(QAction*)), this, SLOT(languageChanged(QAction*)));
  connect(m_wgtLetters, SIGNAL(letterClicked(int)), this, SLOT(letterClicked(int)));

  m_actCategories.front()->setChecked(true);
}

//===========================================
// QtGameWindow::getLanguages
//===========================================
void QtGameWindow::getLanguages() {
  ifstream fin("data/text/languages.txt");

  if (!fin.good())
    ERROR("Error checking available languages; bad file");

  while (!fin.eof()) {
    char buf[64];
    memset(buf, 0, 64);

    fin.getline(buf, 64);
    if (fin.eof()) break;

    utf8string_t lang(buf);
    m_languages.push_back(lang);
  }

  fin.close();
}

//===========================================
// QtGameWindow::restart
//===========================================
void QtGameWindow::restart() {
  m_logic->reset();

  const GameState& state = m_logic->getState();

  m_logic->start(state.categories[m_category]);

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtGuess->update(state.guess);
  m_wgtLetters->enable();

  m_wgtHangman->repaint();
  m_wgtGuess->repaint();
}

//===========================================
// QtGameWindow::languageChanged
//===========================================
void QtGameWindow::languageChanged(QAction* act) {
  int i = -1;

  for (i = 0; i < static_cast<int>(m_actLanguages.size()); ++i) {
    if (m_actLanguages[i] == act) break;
  }

  assert(i != -1);

  GameSettings opts;
  opts.language = m_languages[i];

  m_logic->setSettings(opts);

  restart();

  const GameState& state = m_logic->getState();

  m_wgtLetters->remake(state.alphabet);

  utf8string_t strTitle = state.strings.getValue("title");
  utf8string_t strGame = state.strings.getValue("game");
  utf8string_t strNew = state.strings.getValue("new");
  utf8string_t strQuit = state.strings.getValue("quit");
  utf8string_t strCategory = state.strings.getValue("category");
  utf8string_t strLanguage = state.strings.getValue("language");
  utf8string_t strNewGame = state.strings.getValue("newgame");

  setWindowTitle(strTitle.data());
  m_mnuGame->setTitle(strGame.data());
  m_actNew->setText(strNew.data());
  m_actQuit->setText(strQuit.data());
  m_mnuCategory->setTitle(strCategory.data());
  m_mnuLanguage->setTitle(strLanguage.data());
  m_btnNew->setText(strNewGame.data());
}

//===========================================
// QtGameWindow::categoryChanged
//===========================================
void QtGameWindow::categoryChanged(QAction* act) {
  int i = -1;

  for (i = 0; i < static_cast<int>(m_actCategories.size()); ++i) {
    if (m_actCategories[i] == act) break;
  }

  assert(i != -1);

  m_category = i;
  restart();
}

//===========================================
// QtGameWindow::letterClicked
//===========================================
void QtGameWindow::letterClicked(int id) {
  const GameState& state = m_logic->getState();

  ucs4string_t ucs(1, state.alphabet[id]);
  utf8string_t utf = ucs4ToUtf8(ucs);

  bool done = m_logic->processInput(utf);

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtHangman->repaint();

  m_wgtGuess->update(state.guess);
  m_wgtGuess->repaint();

  if (done) m_wgtLetters->disable();
}

//===========================================
// QtGameWindow::~QtGameWindow
//===========================================
QtGameWindow::~QtGameWindow() {

}
