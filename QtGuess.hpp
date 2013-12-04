#ifndef __QT_GUESS_HPP__
#define __QT_GUESS_HPP__


#include <QWidget>
#include <memory>
#include "Strings.hpp"


class QtGuess : public QWidget {
  Q_OBJECT

  public:
    QtGuess(QWidget* parent = 0);

    void update(const ucs4string_t& guess);

    virtual ~QtGuess() {}

  private slots:

  private:
    void paintEvent(QPaintEvent* event);

    ucs4string_t m_guess;

    std::unique_ptr<QFont> m_font;
};


#endif
