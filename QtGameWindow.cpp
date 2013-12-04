#include <stdexcept>
#include <fstream>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
#include <QGridLayout>
#include <cassert>
#include "Strings.hpp"
#include "QtGameWindow.hpp"


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

  utf8string_t title = state.strings.getValue("title");
  setWindowTitle(title.data());

  m_actNew = pQAction_t(new QAction("&New", this));
  m_actQuit = pQAction_t(new QAction("&Quit", this));

  m_mnuGame = pQMenu_t(menuBar()->addMenu("&Game"));
  m_mnuGame->addAction(m_actNew);
  m_mnuGame->addAction(m_actQuit);

  m_actGrpCategories = pQActionGroup_t(new QActionGroup(this));
  m_mnuCategory = pQMenu_t(menuBar()->addMenu("&Category"));

  const vector<utf8string_t>& categories = state.categories;
  for (unsigned int i = 0; i < categories.size(); ++i) {

    pQAction_t cat(new QAction(categories[i].data(), this));
    cat->setActionGroup(m_actGrpCategories);
    cat->setCheckable(true);

    m_mnuCategory->addAction(cat);

    m_actCategories.push_back(std::move(cat));
  }

  m_actGrpLanguages = pQActionGroup_t(new QActionGroup(this));
  m_mnuLanguage = pQMenu_t(menuBar()->addMenu("&Language"));

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

  QVBoxLayout* vbox = new QVBoxLayout;

  QSizePolicy topleft(QSizePolicy::Preferred, QSizePolicy::Preferred);
  topleft.setVerticalStretch(2);
  topleft.setHorizontalStretch(2);

  QSizePolicy bottomleft(QSizePolicy::Preferred, QSizePolicy::Preferred);
  bottomleft.setVerticalStretch(1);
  bottomleft.setHorizontalStretch(2);

  QGridLayout* grid = new QGridLayout;
  grid->setSpacing(2);

  m_wgtCentral->setLayout(hbox);

  m_wgtLetters = pQWidget_t(new QWidget(m_wgtCentral));
  m_wgtLetters->setSizePolicy(right);
  m_wgtLetters->setLayout(grid);

  m_wgtHangman = new QtHangman(m_wgtCentral);
  m_wgtHangman->setSizePolicy(topleft);

  m_wgtGuess = new QtGuess(m_wgtCentral);
  m_wgtGuess->setSizePolicy(bottomleft);

  vbox->addWidget(m_wgtHangman);
  vbox->addWidget(m_wgtGuess);

  hbox->addLayout(vbox, 1);
  hbox->addWidget(m_wgtLetters);

  m_category = 0;

  m_logic->start(state.categories[m_category]);
  m_gameState = ST_STARTED;

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtGuess->update(state.guess);

  m_grpLetters = pQButtonGroup_t(new QButtonGroup);

  m_btnNew = pQPushButton_t(new QPushButton("&New Game", m_wgtCentral));
  grid->addWidget(m_btnNew, 0, 0, 1, -1);

  for (unsigned int i = 0; i < state.alphabet.length(); ++i) {
    int x = i / 5;
    int y = (i * 2) % 10;

    ucs4string_t ucsL(1, state.alphabet[i]);
    utf8string_t l = ucs4ToUtf8(ucsL);

    QPushButton* btn = new QPushButton(l.data(), m_wgtCentral);
    btn->setMaximumWidth(32);
    btn->setMaximumHeight(32);

    m_letters.push_back(pQPushButton_t(btn));

    m_grpLetters->addButton(btn, i);
    grid->addWidget(btn, x + 1, y);
  }

  connect(m_actNew, SIGNAL(triggered()), this, SLOT(restart()));
  connect(m_btnNew, SIGNAL(released()), this, SLOT(restart()));
  connect(m_actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(m_actGrpCategories, SIGNAL(triggered(QAction*)), this, SLOT(categoryChanged(QAction*)));
  connect(m_actGrpLanguages, SIGNAL(triggered(QAction*)), this, SLOT(languageChanged(QAction*)));
  connect(m_grpLetters, SIGNAL(buttonClicked(int)), this, SLOT(letterClicked(int)));

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

  for (unsigned int i = 0; i < m_letters.size(); ++i)
    m_letters[i]->setEnabled(true);

  const GameState& state = m_logic->getState();

  m_logic->start(state.categories[m_category]);

  m_wgtHangman->update(state.hangman, state.message);
  m_wgtGuess->update(state.guess);

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

  m_letters[id]->setEnabled(false);

  if (done) {
    for (unsigned int i = 0; i < m_letters.size(); ++i)
      m_letters[i]->setEnabled(false);
  }
}

//===========================================
// QtGameWindow::paintEvent
//===========================================
void QtGameWindow::paintEvent(QPaintEvent* event) {
  if (m_gameState != ST_STARTED) return;

  QPainter painter(this);
}

//===========================================
// QtGameWindow::~QtGameWindow
//===========================================
QtGameWindow::~QtGameWindow() {

}
