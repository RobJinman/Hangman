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

  resize(600, 300);

  m_logic = std::unique_ptr<GameLogic>(new GameLogic(opts));
  const GameState& state = m_logic->getState();

  m_category = 0;
  m_logic->start(state.categories[m_category]);
  m_gameState = ST_STARTED;

  m_actNew = pQAction_t(new QAction("", this));
  m_actQuit = pQAction_t(new QAction("", this));

  m_mnuGame = pQMenu_t(menuBar()->addMenu(""));
  m_mnuGame->addAction(m_actNew);
  m_mnuGame->addAction(m_actQuit);

  m_actGrpCategories = pQActionGroup_t(new QActionGroup(this));
  m_mnuCategory = pQMenu_t(menuBar()->addMenu(""));

  m_actGrpLanguages = pQActionGroup_t(new QActionGroup(this));
  m_mnuLanguage = pQMenu_t(menuBar()->addMenu(""));

  for (unsigned int i = 0; i < m_languages.size(); ++i) {
    pQAction_t lang(new QAction(m_languages[i].data(), this));
    lang->setActionGroup(m_actGrpLanguages);
    lang->setCheckable(true);

    if (m_languages[i].compare(opts.language) == 0)
      lang->setChecked(true);

    m_mnuLanguage->addAction(lang);

    m_actLanguages.push_back(std::move(lang));
  }

  m_wgtCentral = pQWidget_t(new QWidget(this));
  setCentralWidget(m_wgtCentral);

  QHBoxLayout* hbox = new QHBoxLayout;

  QVBoxLayout* vboxl = new QVBoxLayout;
  QVBoxLayout* vboxr = new QVBoxLayout;

  m_wgtCentral->setLayout(hbox);

  m_wgtHangman = new QtHangman(m_wgtCentral);

  m_wgtGuess = new QtGuess(m_wgtCentral);

  m_wgtLetters = new QtLetters(m_logic->getState().alphabet, m_wgtCentral);

  m_btnNew = pQPushButton_t(new QPushButton("", m_wgtCentral));
  vboxr->addWidget(m_btnNew);
  vboxr->addWidget(m_wgtLetters);

  vboxl->addWidget(m_wgtHangman, 2);
  vboxl->addWidget(m_wgtGuess, 1);

  hbox->addLayout(vboxl, 2);
  hbox->addLayout(vboxr, 1);

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtGuess->update(state.guess);

  connect(m_actNew, SIGNAL(triggered()), this, SLOT(restart()));
  connect(m_btnNew, SIGNAL(released()), this, SLOT(restart()));
  connect(m_actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(m_actGrpCategories, SIGNAL(triggered(QAction*)), this, SLOT(categoryChanged(QAction*)));
  connect(m_actGrpLanguages, SIGNAL(triggered(QAction*)), this, SLOT(languageChanged(QAction*)));
  connect(m_wgtLetters, SIGNAL(letterClicked(int)), this, SLOT(letterClicked(int)));

  remakeUi();
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

  m_category = 0;
  restart();

  remakeUi();
}

//===========================================
// QtGameWindow::remakeUi
//
// Remake UI using current language and categories
//===========================================
void QtGameWindow::remakeUi() {
  const GameState& state = m_logic->getState();

  for (unsigned int i = 0; i < m_actCategories.size(); ++i)
    m_actGrpCategories->removeAction(m_actCategories[i]);

  m_actCategories.clear();
  m_mnuCategory->clear();

  const vector<utf8string_t>& categories = state.categories;
  for (unsigned int i = 0; i < categories.size(); ++i) {

    pQAction_t cat(new QAction(categories[i].data(), this));
    cat->setActionGroup(m_actGrpCategories);
    cat->setCheckable(true);

    m_mnuCategory->addAction(cat);

    m_actCategories.push_back(std::move(cat));
  }

  m_actCategories.front()->setChecked(true);

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

  const GameState& state = m_logic->getState();
  m_wgtLetters->remake(state.alphabet);
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
