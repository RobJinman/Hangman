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

#ifndef __STRINGS_HPP__
#define __STRINGS_HPP__


#include <string>


typedef std::basic_string<uint32_t> ucs4string_t;
typedef std::string utf8string_t;


utf8string_t ucs4ToUtf8(const ucs4string_t& ucs);
ucs4string_t utf8ToUcs4(const utf8string_t& utf);


#endif
