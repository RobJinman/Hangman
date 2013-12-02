#ifndef __QT_UI_HPP__
#define __QT_UI_HPP__


#include <memory>
#include "GameUi.hpp"


class QtUi : public GameUi {
  public:
    QtUi(int argc, char** argv);

    virtual int start();

    virtual ~QtUi() {}

  private:
    int m_argc;
    char** m_argv;
};


#endif
