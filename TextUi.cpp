#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include "TextUi.hpp"
#include "TextHangman.hpp"
#include "GameState.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


using namespace std;


//===========================================
// TextUi::TextUi
//===========================================
TextUi::TextUi(int argc, char** argv)
  : m_display(40, 13) {

  m_opts.language = "english";
  for (int i = 0; i < argc; ++i) {
    if (strncmp("-lang=", argv[i], 5) == 0) {
      m_opts.language = utf8string_t(&argv[i][6]);
    }
  }

  m_logic = std::unique_ptr<GameLogic>(new GameLogic(m_opts));
}

//===========================================
// TextUi::start
//===========================================
void TextUi::start() {
  const GameState& state = m_logic->getState();

  fetchCategories();

  m_display.clear(' ');

  m_display.putChars("|--------------------------------------|", 0, 0);
  m_display.putChars("|                                      |", 0, 1);
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

  utf8string_t title = state.strings.getValue("title");
  m_display.putChars(title, 2, 1);

  utf8string_t cat = state.strings.getValue("categorysub");
  m_display.putChars(cat, 2, 3);

  int i = 0;
  vector<utf8string_t> categories;
  for (auto c = m_categories.begin(); c != m_categories.end(); ++c) {
    stringstream ss;
    ss << i << ": " << c->first;

    m_display.putChars(ss.str(), 2, 5 + i);

    categories.push_back(c->first);

    ++i;
  }

  m_display.flush();

  unsigned int c = 255;
  while (1) {
    cin >> c;
    if (c < categories.size()) break;

    utf8string_t badcat = state.strings.getValue("badcategory");
    m_display.putChars(badcat, 2, 11);

    m_display.flush();
  }

  pWordList_t words(new wordList_t);
  fetchWords(categories[c], m_alphabet, *words);

  m_logic->start(m_alphabet, move(words));
  draw();

  ioLoop();
}

//===========================================
// TextUi::fetchWords
//===========================================
void TextUi::fetchWords(const utf8string_t& cat, ucs4string_t& alphabet, wordList_t& words) const {
  utf8string_t file = m_categories.getValue(cat);

  stringstream ss;
  ss << "./data/text/" << m_opts.language << "/wordlists/" << file;

  ifstream fin(ss.str());
  if (!fin.good()) {
    fin.close();
    ERROR("Error loading word list; File not found");
  }

  char buf[512];
  memset(buf, 0, 512);

  fin.getline(buf, 512);
  utf8string_t utfAlpha(buf);
  alphabet = utf8ToUcs4(utfAlpha);

  while (!fin.eof()) {
    fin.getline(buf, 512);
    words.push_back(utf8string_t(buf));
  }

  fin.close();
}

//===========================================
// TextUi::fetchCategories
//===========================================
void TextUi::fetchCategories() {
  stringstream ss;
  ss << "./data/text/" + m_opts.language + "/wordlists/index.txt";

  utf8string_t path(ss.str());

  m_categories.parseFile(path);
}

//===========================================
// TextUi::ioLoop
//===========================================
void TextUi::ioLoop() {
  bool done = false;

  while (!done) {
    char buf[64];
    memset(buf, 0, 64);

    cin.getline(buf, 64, '\n');

    utf8string_t str(buf);

    done = m_logic->processInput(str);

    draw();
  }
}

//===========================================
// TextUi::draw
//===========================================
void TextUi::draw() const {
  const GameState& state = m_logic->getState();

  m_display.clear(' ');

  m_display.putChars("|--------------------------------------|", 0, 0);
  m_display.putChars("|                                      |", 0, 1);
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

  utf8string_t title = state.strings.getValue("title");
  m_display.putChars(title, 2, 1);

  m_display.putChars(state.message, 2, 11);

  for (int i = 0; i < state.phraseLen; ++i) {
    m_display.putChar(state.guess[i], 2 + i * 2, 10);
  }

  TextHangman hangman(state.hangman, 3, 3);
  hangman.draw(m_display);

  for (unsigned int c = 0; c < m_alphabet.length(); ++c) {
    int x = 23;
    int y = 4;

    int i = x + ((c * 2) % 10);
    int j = y + c / 5;

    uint32_t l = m_alphabet[c];

    if (state.availableLetters.find(l) != state.availableLetters.end()) {
      ucs4string_t ucs(&l, 1);
      utf8string_t utf = ucs4ToUtf8(ucs);

      m_display.putChars(utf, i, j);
    }
    else
      m_display.putChar(' ', i, j);
  }

  m_display.flush();
}
