#include "AsciiRenderer.hpp"
#include "AsciiHangman.hpp"
#include "GameState.hpp"


//===========================================
// AsciiRenderer::AsciiRenderer
//===========================================
AsciiRenderer::AsciiRenderer()
  : m_display(40, 13) {}

//===========================================
// AsciiRenderer::draw
//===========================================
void AsciiRenderer::draw(const GameState& state) const {
  m_display.clear(' ');

  m_display.putChars("|--------------------------------------|", 0, 0);
  m_display.putChars("|              HANG MAN                |", 0, 1);
  m_display.putChars("|--------------------------------------|", 0, 2);
  m_display.putChars("|                                      |", 0, 3);
  m_display.putChars("|                                      |", 0, 4);
  m_display.putChars("|                                      |", 0, 5);
  m_display.putChars("|                                      |", 0, 6);
  m_display.putChars("|                                      |", 0, 7);
  m_display.putChars("|                                      |", 0, 8);
  m_display.putChars("|                                      |", 0, 9);
  m_display.putChars("|                                      |", 0, 10);
  m_display.putChars("|                                      |", 0, 11);
  m_display.putChars("|--------------------------------------|", 0, 12);

  m_display.putChars(state.message, 2, 11);

  for (int i = 0; i < state.phraseLen; ++i) {
    m_display.putChar(state.guess[i], 2 + i * 2, 10);
  }

  AsciiHangman hangman(state.hangman, 3, 3);
  hangman.draw(m_display);

  for (int c = 0; c < 26; ++c) {
    int x = 23;
    int y = 4;

    int i = x + ((c * 2) % 10);
    int j = y + c / 5;

    char l = 'a' + c;

    if (state.availableLetters.find(l) != state.availableLetters.end())
      m_display.putChar(l, i, j);
    else
      m_display.putChar(' ', i, j);
  }

  m_display.flush();
}
