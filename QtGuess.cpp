#include <stdexcept>
#include <QPainter>
#include "QtGuess.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// QtGuess::QtGuess
//===========================================
QtGuess::QtGuess(QWidget* parent)
  : QWidget(parent) {

  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

  m_font = unique_ptr<QFont>(new QFont("Courier", 15, QFont::DemiBold));
  m_font->setLetterSpacing(QFont::AbsoluteSpacing, 2);
}

//===========================================
// QtGuess::update
//===========================================
void QtGuess::update(const ucs4string_t& guess) {
  m_guess = guess;
}

//===========================================
// QtGuess::paintEvent
//===========================================
void QtGuess::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setFont(*m_font);

  utf8string_t utf = ucs4ToUtf8(m_guess);

  painter.drawText(20, 20, utf.data());
}
