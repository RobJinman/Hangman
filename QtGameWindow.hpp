#ifndef __QT_GAME_WINDOW_HPP__
#define __QT_GAME_WINDOW_HPP__


#include <memory>
#include <QWidget>
#include "GameLogic.hpp"


class QtGameWindow : public QWidget {
  Q_OBJECT

  public:
    QtGameWindow(const GameSettings& opts, QWidget *parent = 0);

    virtual ~QtGameWindow();

  private slots:

  private:
    std::unique_ptr<GameLogic> m_logic;
};


#endif
