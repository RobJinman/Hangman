#ifndef __QT_LETTERS_HPP__
#define __QT_LETTERS_HPP__


#include <QWidget>
#include <QPushButton>
#include <vector>
#include "Strings.hpp"


class QGridLayout;

class QtLetters : public QWidget {
  Q_OBJECT

  public:
    QtLetters(const ucs4string_t& alphabet, QWidget* parent = 0);

    void remake(const ucs4string_t& alphabet);

    void enable();
    void disable();

    virtual ~QtLetters();

  private slots:
    void onLetterClick(int id);

  signals:
    void letterClicked(int id);

  private:
    void destroy();

    QGridLayout* m_grid;
    std::vector<QPushButton*> m_letters;
    QButtonGroup* m_grpLetters;
};


#endif
