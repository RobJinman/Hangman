#ifndef __GAME_HPP__
#define __GAME_HPP__


#include <memory>
#include "GameUi.hpp"


typedef std::unique_ptr<GameUi> pGameUi_t;

class Game {
  public:
    void launch(int argc, char** argv);

  private:
    pGameUi_t m_ui;
};


#endif
