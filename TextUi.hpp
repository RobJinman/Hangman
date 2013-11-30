#ifndef __TEXT_UI_HPP__
#define __TEXT_UI_HPP__


#include <memory>
#include "GameUi.hpp"
#include "TextDisplay.hpp"
#include "GameLogic.hpp"
#include "KvpParser.hpp"


class TextUi : public GameUi {
  public:
    TextUi(int argc, char** argv);

    virtual void start();

    virtual ~TextUi() {}

  private:
    void fetchCategories();
    void fetchWords(const utf8string_t& cat, ucs4string_t& alphabet, wordList_t& words) const;
    bool ioLoop();
    void draw() const;

    ucs4string_t m_alphabet;
    KvpParser m_categories;
    mutable TextDisplay m_display;
    GameSettings m_opts;
    std::unique_ptr<GameLogic> m_logic;
};


#endif
