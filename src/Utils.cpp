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

#include <algorithm>
#include <QStandardPaths>
#include <QDir>
#include "Utils.hpp"


namespace utils {


#ifdef WIN32
utf8string_t sep() {
  return "\\";
}
#else
utf8string_t sep() {
  return "/";
}
#endif

utf8string_t dataPath() {
  QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

  for (QString location : locations) {
    utf8string_t loc = location.toUtf8().constData();
    utf8string_t path = utils::platformPath(loc + utf8string_t("/data"));

    QDir dir(path.c_str());
    if (dir.exists()) {
      return path;
    }
  }

  return "data";
}

utf8string_t platformPath(const utf8string_t& path) {
  utf8string_t newPath = path;

  std::replace(newPath.begin(), newPath.end(), '\\', '/');
  std::replace(newPath.begin(), newPath.end(), '/', sep()[0]);

  return newPath;
}


}
