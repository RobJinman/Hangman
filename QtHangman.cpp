#include <stdexcept>
#include "QtHangman.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// QtHangman::QtHangman
//===========================================
QtHangman::QtHangman(QWidget* parent)
  : QWidget(parent) {

  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

  m_font = unique_ptr<QFont>(new QFont("Courier", 15, QFont::DemiBold));
}

//===========================================
// QtHangman::update
//===========================================
void QtHangman::update(const Hangman& hangman, const utf8string_t& message) {
  m_hangman = hangman;
  m_message = message;
}

//===========================================
// QtHangman::paintEvent
//===========================================
void QtHangman::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setFont(*m_font);

  switch (m_hangman.getState()) {
    case 0: drawState0(painter); break;
    case 1: drawState1(painter); break;
    case 2: drawState2(painter); break;
    case 3: drawState3(painter); break;
    case 4: drawState4(painter); break;
    case 5: drawState5(painter); break;
    case 6: drawState6(painter); break;
    case 7: drawState7(painter); break;
    case 8: drawState8(painter); break;
    case 9: drawState9(painter); break;
    case 10: drawState10(painter); break;
    case 11: drawState11(painter); break;
    default: ERROR("Error drawing graphic; Unrecognised state");
  }

  drawMessage(painter);
}

//===========================================
// QtHangman::drawMessage
//===========================================
void QtHangman::drawMessage(QPainter& painter) {
  painter.drawText(20, 80, m_message.data());
}

//===========================================
// QtHangman::drawState0...11

// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
void QtHangman::drawState0(QPainter& painter) {
  painter.drawText(20, 20, "X");
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
void QtHangman::drawState1(QPainter& painter) {
  drawState0(painter);

  painter.drawText(40, 20, "X");
}

// |                |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState2(QPainter& painter) {
  drawState1(painter);

  painter.drawText(60, 20, "X");
}

// |   ________     |
// |  |             |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState3(QPainter& painter) {
  drawState2(painter);

  painter.drawText(80, 20, "X");
}

// |   ________     |
// |  |/            |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState4(QPainter& painter) {
  drawState3(painter);

  painter.drawText(100, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |             |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState5(QPainter& painter) {
  drawState4(painter);

  painter.drawText(120, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |             |
// |  |             |
// | _|_            |
void QtHangman::drawState6(QPainter& painter) {
  drawState5(painter);

  painter.drawText(140, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |        |    |
// |  |             |
// | _|_            |
void QtHangman::drawState7(QPainter& painter) {
  drawState6(painter);

  painter.drawText(160, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|    |
// |  |             |
// | _|_            |
void QtHangman::drawState8(QPainter& painter) {
  drawState7(painter);

  painter.drawText(180, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |             |
// | _|_            |
void QtHangman::drawState9(QPainter& painter) {
  drawState8(painter);

  painter.drawText(200, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       /     |
// | _|_            |
void QtHangman::drawState10(QPainter& painter) {
  drawState9(painter);

  painter.drawText(220, 20, "X");
}

// |   ________     |
// |  |/       |    |
// |  |        O    |
// |  |       /|\   |
// |  |       / \   |
// | _|_            |
void QtHangman::drawState11(QPainter& painter) {
  drawState10(painter);

  painter.drawText(240, 20, "X");
}
//===========================================
