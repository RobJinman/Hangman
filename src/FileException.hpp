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

#ifndef __FILE_EXCEPTION_HPP__
#define __FILE_EXCEPTION_HPP__


#include "Exception.hpp"


#define FILE_EXCEPTION(x, file) { \
  stringstream ss; \
  ss << x; \
  throw FileException(ss.str(), file, __FILE__, __LINE__); \
}


class FileException : public Exception {
  public:
    FileException(const utf8string_t& msg)
      : Exception(msg) {}

    FileException(const utf8string_t& msg, const char* file, int line)
      : Exception(msg, file, line) {}

    FileException(const utf8string_t& msg, const utf8string_t& path, const char* file, int line)
      : Exception(msg, file, line), m_file(path) {

      append(" (path: ");
      append(path);
      append(")");
    }

    utf8string_t getFilePath() const throw() {
      return m_file;
    }

    virtual ~FileException() throw() {}

  private:
    utf8string_t m_file;
};


#endif
