#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include "Strings.hpp"


using namespace std;


int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " file\n";
    return EXIT_SUCCESS;
  }

  ifstream fin(argv[1]);
  if (!fin.good()) {
    cerr << "Bad file\n";
    return EXIT_FAILURE;
  }

  set<uint32_t> chars;
  char buf[128];

  while (1) {
    if (fin.eof()) break;

    memset(buf, '\0', 128);
    fin.getline(buf, 128);

    utf8string_t utf(buf);
    ucs4string_t ucs = utf8ToUcs4(utf);

    for (unsigned int i = 0; i < ucs.length(); ++i) {
      if (ucs[i] != ' ' && ucs[i] != '\t' && ucs[i] != '\n')
        chars.insert(ucs[i]);
    }
  }

  fin.close();

  utf8string_t alphabet;

  for (auto i = chars.begin(); i != chars.end(); ++i) {
    ucs4string_t ucs(1, *i);
    utf8string_t utf = ucs4ToUtf8(ucs);

    alphabet.append(utf);
  }

  cout << alphabet << "\n";

  return EXIT_SUCCESS;
}
