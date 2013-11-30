#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include "KvpParser.hpp"


#define ERROR(msg) throw std::runtime_error(msg);


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
    ERROR(utf8string_t("Error opening file ") + file);

  string buf;
  stringstream formatStr;

  buf = getLine(fin);

  while (!fin.eof()) {
    if (buf.length() > 0) {
      char strKey[BUF_SIZE], strVal[BUF_SIZE];

      formatStr.str("");
      formatStr << "%" << BUF_SIZE - 1 << "[^=]=%" << BUF_SIZE - 1 << "[^\n]";

      if (sscanf(buf.data(), formatStr.str().data(), strKey, strVal) != 2)
        ERROR("Error parsing file");

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
