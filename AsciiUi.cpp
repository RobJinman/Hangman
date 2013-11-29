#include <iostream>
#include "AsciiUi.hpp"
#include "AsciiHangman.hpp"
#include "GameState.hpp"


using namespace std;


//===========================================
// AsciiUi::AsciiUi
//===========================================
AsciiUi::AsciiUi()
  : m_display(40, 13) {}

//===========================================
// AsciiUi::start
//===========================================
void AsciiUi::start() {
  m_display.clear(' ');

  m_display.putChars("|--------------------------------------|", 0, 0);
  m_display.putChars("|              HANG MAN                |", 0, 1);
  m_display.putChars("|--------------------------------------|", 0, 2);
  m_display.putChars("|          Select a category           |", 0, 3);
  m_display.putChars("|                                      |", 0, 4);
  m_display.putChars("|       0: Default                     |", 0, 5);
  m_display.putChars("|       1: Animals                     |", 0, 6);
  m_display.putChars("|       2: Movies                      |", 0, 7);
  m_display.putChars("|                                      |", 0, 8);
  m_display.putChars("|                                      |", 0, 9);
  m_display.putChars("|                                      |", 0, 10);
  m_display.putChars("|                                      |", 0, 11);
  m_display.putChars("|--------------------------------------|", 0, 12);

  m_display.flush();

  char c;
  cin >> c;

  pWordList_t words(new wordList_t);
  words->push_back("Susan Boyle");
  words->push_back("dinosaur");
  words->push_back("frenchman");
  words->push_back("pineapple");
  words->push_back("lemon pie");

  m_logic.start(move(words));
  draw();

  ioLoop();
}

//===========================================
// AsciiUi::ioLoop
//===========================================
void AsciiUi::ioLoop() {
  bool done = false;

  while (!done) {
    char c;
    cin >> c;

    done = m_logic.processInput(c);

    draw();
  }
}

//===========================================
// AsciiUi::draw
//===========================================
void AsciiUi::draw() const {
  const GameState& state = m_logic.getState();

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
