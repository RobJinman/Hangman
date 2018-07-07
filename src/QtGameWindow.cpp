// This file is part of Hangman.
//
// Copyright Rob Jinman 2013 <jinmanr@gmail.com>
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

#include <fstream>
#include <cassert>
#include <sstream>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "Strings.hpp"
#include "QtGameWindow.hpp"
#include "QtLetters.hpp"
#include "FileException.hpp"
#include "Utils.hpp"


using namespace std;


//===========================================
// QtGameWindow::QtGameWindow
//===========================================
QtGameWindow::QtGameWindow(const GameSettings& opts, QWidget* parent)
  : QMainWindow(parent),
    m_gameState(ST_IDLE),
    m_mnuGame(NULL),
    m_mnuCategory(NULL),
    m_mnuLanguage(NULL),
    m_mnuHelp(NULL),
    m_actNew(NULL),
    m_actQuit(NULL),
    m_actAbout(NULL),
    m_actGrpCategories(NULL),
    m_actGrpLanguages(NULL),
    m_btnNew(NULL),
    m_wgtCentral(NULL),
    m_wgtLetters(NULL),
    m_wgtHangman(NULL),
    m_wgtGuess(NULL) {

  getLanguages();

  resize(600, 300);

  m_logic = std::unique_ptr<GameLogic>(new GameLogic(opts));
  const GameState& state = m_logic->getState();

  m_category = 0;
  m_logic->start(state.categories[m_category]);
  m_gameState = ST_STARTED;

  m_actNew = new QAction("", this);
  m_actQuit = new QAction("", this);

  m_mnuGame = menuBar()->addMenu("");
  m_mnuGame->addAction(m_actNew);
  m_mnuGame->addAction(m_actQuit);

  m_actGrpCategories = new QActionGroup(this);
  m_mnuCategory = menuBar()->addMenu("");

  m_actGrpLanguages = new QActionGroup(this);
  m_mnuLanguage = menuBar()->addMenu("");

  for (unsigned int i = 0; i < m_languages.size(); ++i) {
    QAction* lang = new QAction(m_languages[i].data(), this);
    lang->setActionGroup(m_actGrpLanguages);
    lang->setCheckable(true);

    if (m_languages[i].compare(opts.language) == 0) {
      lang->setChecked(true);
    }

    m_mnuLanguage->addAction(lang);

    m_actLanguages.push_back(std::move(lang));
  }

  m_actAbout = new QAction("", this);
  m_mnuHelp = menuBar()->addMenu("");
  m_mnuHelp->addAction(m_actAbout);

  m_wgtCentral = new QWidget(this);
  setCentralWidget(m_wgtCentral);

  QHBoxLayout* hbox = new QHBoxLayout;

  QVBoxLayout* vboxl = new QVBoxLayout;
  QVBoxLayout* vboxr = new QVBoxLayout;

  m_wgtCentral->setLayout(hbox);

  m_wgtHangman = new QtHangman(m_wgtCentral);

  m_wgtGuess = new QtGuess(m_wgtCentral);

  m_wgtLetters = new QtLetters(m_logic->getState().alphabet, m_wgtCentral);

  m_btnNew = new QPushButton("", m_wgtCentral);
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
  connect(m_actAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

  remakeUi();

  getVersion();
}

//===========================================
// QtGameWindow::getVersion
//===========================================
void QtGameWindow::getVersion() {
  stringstream ss;
  ss << utils::dataPath() << "/VERSION";

  utf8string_t path = utils::platformPath(ss.str());

  ifstream fin(path);

  if (!fin.good()) {
    m_version = "1.?.?";
  }
  else {
    char buf[32];
    memset(buf, 0, 32);

    fin.getline(buf, 32);

    m_version = utf8string_t(buf);
  }

  fin.close();
}

//===========================================
// QtGameWindow::showAbout
//===========================================
void QtGameWindow::showAbout() {
  const GameState& state = m_logic->getState();

  utf8string_t strTitle = state.strings.getValue("abouttitle");
  utf8string_t strBody = state.strings.getValue("aboutbody");

  for (int i = static_cast<int>(strBody.length()) - 2; i >= 0; --i) {
    if (strncmp(&strBody.data()[i], "\\n", 2) == 0) {
      strBody.replace(i, 2, "\n");
    }

    if (strncmp(&strBody.data()[i], "%v", 2) == 0) {
      strBody.replace(i, 2, m_version);
    }
  }

  QMessageBox::about(this, strTitle.data(), strBody.data());
}

//===========================================
// QtGameWindow::getLanguages
//===========================================
void QtGameWindow::getLanguages() {
  stringstream ss;
  ss << utils::dataPath() << "/text/languages.txt";

  utf8string_t path = utils::platformPath(ss.str());
  ifstream fin(path);

  if (!fin.good()) {
    fin.close();
    FILE_EXCEPTION("Error checking available languages; bad file", path);
  }

  while (!fin.eof()) {
    char buf[64];
    memset(buf, 0, 64);

    fin.getline(buf, 64);

    if (strlen(buf) > 0) {
      utf8string_t lang(buf);
      m_languages.push_back(lang);
    }
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
    if (m_actLanguages[i] == act) {
      break;
    }
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

  for (unsigned int i = 0; i < m_actCategories.size(); ++i) {
    m_actGrpCategories->removeAction(m_actCategories[i]);
  }

  m_actCategories.clear();
  m_mnuCategory->clear();

  const vector<utf8string_t>& categories = state.categories;
  for (unsigned int i = 0; i < categories.size(); ++i) {
    QAction* cat = new QAction(categories[i].data(), this);
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
  utf8string_t strHelp = state.strings.getValue("help");
  utf8string_t strAbout = state.strings.getValue("about");

  setWindowTitle(strTitle.data());
  m_mnuGame->setTitle(strGame.data());
  m_actNew->setText(strNew.data());
  m_actQuit->setText(strQuit.data());
  m_mnuCategory->setTitle(strCategory.data());
  m_mnuLanguage->setTitle(strLanguage.data());
  m_btnNew->setText(strNewGame.data());
  m_mnuHelp->setTitle(strHelp.data());
  m_actAbout->setText(strAbout.data());
}

//===========================================
// QtGameWindow::categoryChanged
//===========================================
void QtGameWindow::categoryChanged(QAction* act) {
  int i = -1;

  for (i = 0; i < static_cast<int>(m_actCategories.size()); ++i) {
    if (m_actCategories[i] == act) {
      break;
    }
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

  if (done) {
    m_wgtLetters->disable();
  }
}

//===========================================
// QtGameWindow::~QtGameWindow
//===========================================
QtGameWindow::~QtGameWindow() {
  delete m_wgtCentral;

  delete m_mnuGame;
  delete m_mnuCategory;
  delete m_mnuLanguage;
  delete m_mnuHelp;
  delete m_actNew;
  delete m_actQuit;
  delete m_actAbout;

  for (auto i = m_actCategories.begin(); i != m_actCategories.end(); ++i) {
    delete *i;
  }

  delete m_actGrpCategories;

  for (auto i = m_actLanguages.begin(); i != m_actLanguages.end(); ++i) {
    delete *i;
  }

  delete m_actGrpLanguages;
}
