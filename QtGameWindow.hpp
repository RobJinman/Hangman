// This file is part of Hangmuž.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangmuž is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangmuž is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangmuž.  If not, see <http://www.gnu.org/licenses/>.

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


class QAction;
class QActionGroup;
class QtLetters;

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
    void showAbout();

  private:
    enum gameState_t { ST_IDLE, ST_STARTED };

    void getLanguages();
    void remakeUi();

    gameState_t m_gameState;
    std::unique_ptr<GameLogic> m_logic;
    std::vector<utf8string_t> m_languages;

    int m_category;

    QMenu* m_mnuGame;
    QMenu* m_mnuCategory;
    QMenu* m_mnuLanguage;
    QMenu* m_mnuHelp;
    QAction* m_actNew;
    QAction* m_actQuit;
    QAction* m_actAbout;
    std::vector<QAction*> m_actCategories;
    QActionGroup* m_actGrpCategories;
    std::vector<QAction*> m_actLanguages;
    QActionGroup* m_actGrpLanguages;
    QPushButton* m_btnNew;
    QWidget* m_wgtCentral;
    QtLetters* m_wgtLetters;
    QtHangman* m_wgtHangman;
    QtGuess* m_wgtGuess;
};


#endif
