#ifndef __QT_GAME_WINDOW_HPP__
#define __QT_GAME_WINDOW_HPP__


#include <memory>
#include <vector>
#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include "GameLogic.hpp"
#include "QtHangman.hpp"
#include "QtGuess.hpp"


class QMenu;
class QAction;
class QActionGroup;
class QtLetters;

typedef QMenu* pQMenu_t;
typedef QAction* pQAction_t;
typedef QActionGroup* pQActionGroup_t;
typedef QPushButton* pQPushButton_t;
typedef QWidget* pQWidget_t;
typedef QButtonGroup* pQButtonGroup_t;

class QtGameWindow : public QMainWindow {
  Q_OBJECT

  public:
    QtGameWindow(const GameSettings& opts, QWidget* parent = 0);

    virtual ~QtGameWindow();

  private slots:
    void languageChanged(QAction* act);
    void categoryChanged(QAction* act);
    void letterClicked(int id);
    void restart();

  private:
    enum gameState_t { ST_IDLE, ST_STARTED };

    void getLanguages();

    gameState_t m_gameState;
    std::unique_ptr<GameLogic> m_logic;
    std::vector<utf8string_t> m_languages;

    int m_category;

    pQMenu_t m_mnuGame;
    pQMenu_t m_mnuCategory;
    pQMenu_t m_mnuLanguage;
    pQAction_t m_actNew;
    pQAction_t m_actQuit;
    std::vector<pQAction_t> m_actCategories;
    pQActionGroup_t m_actGrpCategories;
    std::vector<pQAction_t> m_actLanguages;
    pQActionGroup_t m_actGrpLanguages;
    pQPushButton_t m_btnNew;
    pQWidget_t m_wgtCentral;
    QtLetters* m_wgtLetters;
    QtHangman* m_wgtHangman;
    QtGuess* m_wgtGuess;
};


#endif
