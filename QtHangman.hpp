#ifndef __QT_HANGMAN_HPP__
#define __QT_HANGMAN_HPP__


#include <QWidget>
#include <QPainter>
#include <memory>
#include "Hangman.hpp"
#include "Strings.hpp"


class QtHangman : public QWidget {
  Q_OBJECT

  public:
    QtHangman(QWidget* parent = 0);

    void update(const Hangman& hangman, const utf8string_t& message);

    virtual ~QtHangman() {}

  private slots:

  private:
    void paintEvent(QPaintEvent* event);
    void drawState0(QPainter& painter);
    void drawState1(QPainter& painter);
    void drawState2(QPainter& painter);
    void drawState3(QPainter& painter);
    void drawState4(QPainter& painter);
    void drawState5(QPainter& painter);
    void drawState6(QPainter& painter);
    void drawState7(QPainter& painter);
    void drawState8(QPainter& painter);
    void drawState9(QPainter& painter);
    void drawState10(QPainter& painter);
    void drawState11(QPainter& painter);
    void drawMessage(QPainter& painter);

    Hangman m_hangman;
    utf8string_t m_message;

    std::unique_ptr<QFont> m_font;
};


#endif
