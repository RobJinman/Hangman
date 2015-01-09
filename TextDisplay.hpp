// This file is part of Hangman.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangman is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangman is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangman.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __TEXT_DISPLAY_HPP__
#define __TEXT_DISPLAY_HPP__


#include "Strings.hpp"


class TextDisplay {
  public:
    TextDisplay(int w, int h);

    void putChar(uint32_t ucsChar, int x, int y);
    void putChars(const utf8string_t& str, int x, int y);
    void clear(uint32_t c);
    void flush();

  private:
    uint32_t** m_pixels;
    int m_w;
    int m_h;
};


#endif
