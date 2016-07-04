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

#include <iostream>
#include "Exception.hpp"
#include "Game.hpp"
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif


#ifdef __APPLE__
  void changeWorkingDir() {
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, reinterpret_cast<UInt8*>(path), PATH_MAX);
    CFRelease(resourcesURL);
    chdir(path);
  }
#endif


using namespace std;


//===========================================
// main
//===========================================
int main(int argc, char** argv) {
#ifdef __APPLE__
  changeWorkingDir();
#endif
  try {
    Game game;
    return game.launch(argc, argv);
  }
  catch (Exception& e) {
    cerr << "Encountered fatal error; " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch (...) {
    cerr << "Encountered fatal error; Cause unknown\n";
    return EXIT_FAILURE;
  }
}
