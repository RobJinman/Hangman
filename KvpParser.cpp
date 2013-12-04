// This file is part of Hangmuž.
//
// Copyright Rob Jinman 2013 <admin@robjinman.com>
//
// Hangmuž is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hangmuž is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hangmuž.  If not, see <http://www.gnu.org/licenses/>.

#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include "KvpParser.hpp"
#include "FileException.hpp"


using namespace std;


static const unsigned int BUF_SIZE = 256;


//===========================================
// KvpParser::getValue
//
// Retrieve value by key.
//===========================================
utf8string_t KvpParser::getValue(const utf8string_t& key) const {
  map<utf8string_t, utf8string_t>::const_iterator it = m_data.find(key);
  if (it == m_data.end()) return utf8string_t("");

  return it->second;
}

//===========================================
// KvpParser::getLine
//===========================================
utf8string_t KvpParser::getLine(ifstream& fin) const {
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);

  fin.getline(buf, BUF_SIZE);
  for (unsigned int i = 0; i < BUF_SIZE; i++)
    if (buf[i] == '#') buf[i] = '\0';

  utf8string_t str(buf);
  while (str[0] == ' ' || str[0] == '\t') str.erase(0, 1);

  return str;
}

//===========================================
// KvpParser::parseFile
//===========================================
void KvpParser::parseFile(const utf8string_t& file) {
  ifstream fin(file.data());
  if (!fin.good())
    FILE_EXCEPTION("Error opening file", file);

  string buf;
  stringstream formatStr;

  buf = getLine(fin);

  while (!fin.eof()) {
    if (buf.length() > 0) {
      char strKey[BUF_SIZE], strVal[BUF_SIZE];

      formatStr.str("");
      formatStr << "%" << BUF_SIZE - 1 << "[^=]=%" << BUF_SIZE - 1 << "[^\n]";

      if (sscanf(buf.data(), formatStr.str().data(), strKey, strVal) != 2)
        FILE_EXCEPTION("Error parsing file", file);

      utf8string_t key(strKey);
      utf8string_t val(strVal);

      while (key.back() == ' ' || key.back() == '\t') key.erase(key.size() - 1);
      while (val.front() == ' ' || val.front() == '\t') val.erase(0, 1);

      m_data[key] = val;
    }
    buf = getLine(fin);
  }

  fin.close();
}
