#ifndef __HANG_MAN_HPP__
#define __HANG_MAN_HPP__


class Hangman {
  public:
    Hangman();

    void advance();
    void reset();
    bool isComplete() const;

    inline int getState() const;
    inline int lastState() const;

  private:
    int m_state;
    int m_lastState;
};

inline int Hangman::getState() const {
  return m_state;
}

inline int Hangman::lastState() const {
  return m_lastState;
}


#endif
