// This file is part of Hangman.
//
// Copyright Rob Jinman 2013 <jinmanr@gmail.com>
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

#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__


#include <stdexcept>
#include <sstream>
#include "Strings.hpp"


#define EXCEPTION(x) { \
  std::stringstream ss; \
  ss << x; \
  throw Exception(x, __FILE__, __LINE__); \
}


class Exception : public std::runtime_error {
  public:
    Exception(const utf8string_t& msg)
      : std::runtime_error(msg) {}

    Exception(const utf8string_t& msg, const char* file, int line)
      : std::runtime_error(msg), m_msg(msg), m_file(file), m_line(line) {}

    virtual const char* what() const throw() {
      static utf8string_t msg;
      std::stringstream ss;

      ss << m_msg << " (FILE: " << m_file << ", LINE: " << m_line << ")";
      msg = ss.str();

      return msg.data();
    }

    void append(const utf8string_t& text) throw() {
      m_msg.append(text);
    }

    void prepend(const utf8string_t& text) throw() {
      m_msg.insert(0, text);
    }

    virtual ~Exception() throw() {}

  private:
    utf8string_t m_msg;
    utf8string_t m_file;
    int m_line;
};


#endif
