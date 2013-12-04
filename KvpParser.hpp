#ifndef __KVP_PARSER_HPP__
#define __KVP_PARSER_HPP__


#include <map>
#include <vector>
#include "Strings.hpp"


// Parses a text file of key-value pairs.
class KvpParser {
  typedef std::map<utf8string_t, utf8string_t>::const_iterator iterator;

  public:
    void parseFile(const utf8string_t& file);
    utf8string_t getValue(const utf8string_t& key) const;

    inline iterator begin() const;
    inline iterator end() const;

    inline void clear();

  private:
    std::map<utf8string_t, utf8string_t> m_data;
    utf8string_t getLine(std::ifstream& fin) const;
};

inline KvpParser::iterator KvpParser::begin() const {
  return m_data.begin();
}

inline KvpParser::iterator KvpParser::end() const {
  return m_data.end();
}

inline void KvpParser::clear() {
  m_data.clear();
}


#endif
